#!/usr/bin/env python3
#
# Version 1.0.2 - Build 43
#############################################################################
# Change log:
#  7 May  2019, ondratu   , Initial
# 13 June 2019, 3d-gussner, Fix length false positives
# 14 Sep. 2019, 3d-gussner, Prepare adding new language
# 18 Sep. 2020, 3d-gussner, Fix execution of lang-check.py
#  2 Apr. 2021, 3d-gussner, Fix and improve text warp
# 22 Apr. 2021, DRracer   , add English source to output
# 23 Apr. 2021, wavexx    , improve
# 24 Apr. 2021, wavexx    , improve
# 26 Apr. 2021, wavexx    , add character ruler
# 21 Dec. 2021, 3d-gussner, Prepare more community languages
#                             Swedish
#                             Danish
#                             Slovanian
#                             Hungarian
#                             Luxembourgian
#                             Croatian
#  3 Jan. 2022, 3d-gussner, Prepare Lithuanian
#  7 Jan. 2022, 3d-gussner, Check for Syntax errors and exit with error
#                         , add Build number 'git rev-list --count HEAD lang-check.py'
# 30 Jan. 2022, 3d-gussner, Add arguments. Requested by @AttilaSVK
#                             --information == output all source and translated messages
#                             --import-check == used by `lang-import.sh`to verify
#                                               newly import `lang_en_??.txt` files
# 14 Mar. 2022, 3d-gussner, Check if translation isn't equal to origin
#############################################################################

"""Check PO files for formatting errors."""
from argparse import ArgumentParser
from traceback import print_exc
from sys import stdout, stderr, exit
import polib
import textwrap
import re
import os

from lib import charset as cs

def color_maybe(color_attr, text):
    if stdout.isatty():
        return '\033[0;' + str(color_attr) + 'm' + text + '\033[0m'
    else:
        return text

red = lambda text: color_maybe(31, text)
green = lambda text: color_maybe(32, text)
yellow = lambda text: color_maybe(33, text)
cyan = lambda text: color_maybe(36, text)


def print_wrapped(wrapped_text, rows, cols):
    if type(wrapped_text) == str:
        wrapped_text = [wrapped_text]
    for r, line in enumerate(wrapped_text):
        r_ = str(r + 1).rjust(3)
        if r >= rows:
            r_ = red(r_)
        print((' {} |{:' + str(cols) + 's}|').format(r_, line))

def print_truncated(text, cols):
    if len(text) <= cols:
        prefix = text.ljust(cols)
        suffix = ''
    else:
        prefix = text[0:cols]
        suffix = red(text[cols:])
    print('   |' + prefix + '|' + suffix)

def print_ruler(spc, cols):
    print(' ' * spc + cyan(('₀₁₂₃₄₅₆₇₈₉'*4)[:cols]))

def print_source_translation(source, translation, wrapped_source, wrapped_translation, rows, cols):
    if rows == 1:
        print(' source text:')
        print_ruler(4, cols);
        print_truncated(source, cols)
        print(' translated text:')
        print_ruler(4, cols);
        print_truncated(translation, cols)
    else:
        print(' source text:')
        print_ruler(6, cols);
        print_wrapped(wrapped_source, rows, cols)
        print(' translated text:')
        print_ruler(6, cols);
        print_wrapped(wrapped_translation, rows, cols)
    print()

def highlight_trailing_white(text):
    if type(text) == str:
        return re.sub(r' $', '·', text)
    else:
        ret = text[:]
        ret[-1] = highlight_trailing_white(ret[-1])
        return ret

def wrap_text(text, cols):
    ret = []
    for line in text.split('\n'):
        # wrap each input line in text individually
        tmp = list(textwrap.TextWrapper(width=cols).wrap(line))
        if len(ret):
            # add back trailing whitespace
            tmp[-1] += ' ' * (len(text) - len(text.rstrip()))
        ret.extend(tmp)
    return ret

def ign_char_first(c):
    return c.isalnum() or c in {'%', '?'}

def ign_char_last(c):
    return c.isalnum() or c in {'.', "'"}

def check_translation(entry, is_pot, no_warning, warn_empty, information):
    """Check strings to display definition."""

    # fetch/decode entry for easy access
    meta = entry.tcomment.split('\n', 1)[0]
    source = entry.msgid
    translation = entry.msgstr
    line = entry.linenum

    # Check comment syntax should start with `MSG`
    if len(meta) == 0:
        print(red("[E]: Translation doesn't contain any comment metadata on line %d" % line))
        return
    if not meta.startswith('MSG'):
        print(red("[E]: Critical syntax error: comment doesn't start with MSG on line %d" % line))
        print(red(" comment: " + meta))
        return

    # Check if columns and rows are defined
    tokens = meta.split(' ')
    cols = None
    rows = None
    for item in tokens[1:]:
        try:
            key, val = item.split('=')
            if key == 'c':
                cols = int(val)
            elif key == 'r':
                rows = int(val)
            else:
                raise ValueError
        except ValueError:
            print(red("[E]: Invalid display definition on line %d" % line))
            print(red(" definition: " + meta))
            return

    if cols is None and rows is None:
        if not no_warning:
            print(yellow("[W]: No usable display definition on line %d" % line))
        # probably fullscreen, guess from the message length to continue checking
        cols = len(source)
    if rows is None:
        rows = 1
    elif rows > 1 and cols != 20:
        print(yellow("[W]: Multiple rows with odd number of columns on line %d" % line))

    # Check if translation contains unsupported characters
    invalid_char = cs.translation_check(cs.unicode_to_source(translation))
    if invalid_char is not None:
        print(red('[E]: Critical syntax: Unhandled char %s found on line %d' % (repr(invalid_char), line)))
        print(red(' translation: ' + translation))
        return

    wrapped_source = wrap_text(source, cols)
    rows_count_source = len(wrapped_source)
    wrapped_translation = wrap_text(translation, cols)
    rows_count_translation = len(wrapped_translation)

    # Incorrect number of rows/cols on the definition
    if rows == 1 and (len(source) > cols or rows_count_source > rows):
        print(yellow('[W]: Source text longer than %d cols as defined on line %d:' % (cols, line)))
        print_ruler(4, cols);
        print_truncated(source, cols)
        print()
    elif rows_count_source > rows:
        print(yellow('[W]: Wrapped source text longer than %d rows as defined on line %d:' % (rows, line)))
        print_ruler(6, cols);
        print_wrapped(wrapped_source, rows, cols)
        print()

    # All further checks are against the translation
    if is_pot:
        return

    # Missing translation
    if len(translation) == 0 and (warn_empty or rows > 1):
        if rows == 1:
            print(yellow("[W]: Empty translation for \"%s\" on line %d" % (source, line)))
        else:
            print(yellow("[W]: Empty translation on line %d" % line))
            print_ruler(6, cols);
            print_wrapped(wrapped_source, rows, cols)
            print()


    # Check for translation lenght
    if (rows_count_translation > rows) or (rows == 1 and len(translation) > cols):
        print(red('[E]: Text is longer than definition on line %d: cols=%d rows=%d (rows diff=%d)'
                % (line, cols, rows, rows_count_translation-rows)))
        print_source_translation(source, translation,
                                wrapped_source, wrapped_translation,
                                rows, cols)

    # Different count of % sequences
    if source.count('%') != translation.count('%') and len(translation) > 0:
        print(red('[E]: Unequal count of %% escapes on line %d:' % (line)))
        print_source_translation(source, translation,
                                wrapped_source, wrapped_translation,
                                rows, cols)

    # Different first/last character
    if not no_warning and len(source) > 0 and len(translation) > 0:
        source_end = source.rstrip()[-1]
        translation_end = translation.rstrip()[-1]
        start_diff = not (ign_char_first(source[0]) and ign_char_first(translation[0])) and source[0] != translation[0]
        end_diff = not (ign_char_last(source_end) and ign_char_last(translation_end)) and source_end != translation_end
        if start_diff or end_diff:
            if start_diff:
                print(yellow('[W]: Differing first punctuation character (%s => %s) on line %d:' % (source[0], translation[0], line)))
            if end_diff:
                print(yellow('[W]: Differing last punctuation character (%s => %s) on line %d:' % (source[-1], translation[-1], line)))
            print_source_translation(source, translation,
                                    wrapped_source, wrapped_translation,
                                    rows, cols)
    if not no_warning and source == translation:
        print(yellow('[W]: Translation same as origin on line %d:' %line))
        print_source_translation(source, translation,
                                wrapped_source, wrapped_translation,
                                rows, cols)
    #elif information:
    #    print(green('[I]: %s' % (meta)))
    #    print_source_translation(source, translation,
    #                            wrapped_source, wrapped_translation,
    #                            rows, cols)


    # Short translation
    if not no_warning and len(source) > 0 and len(translation) > 0:
        if len(translation.rstrip()) < len(source.rstrip()) / 2:
            print(yellow('[W]: Short translation on line %d:' % (line)))
            print_source_translation(source, translation,
                                    wrapped_source, wrapped_translation,
                                    rows, cols)
    #elif information:
    #    print(green('[I]: %s' % (meta)))
    #    print_source_translation(source, translation,
    #                            wrapped_source, wrapped_translation,
    #                            rows, cols)

    # Incorrect trailing whitespace in translation
    if not no_warning and len(translation) > 0 and \
     (source.rstrip() == source or (rows == 1 and len(source) == cols)) and \
     translation.rstrip() != translation and \
     (rows > 1 or len(translation) != len(source)):
        print(yellow('[W]: Incorrect trailing whitespace for translation on line %d:' % (line)))
        source = highlight_trailing_white(source)
        translation = highlight_trailing_white(translation)
        wrapped_translation = highlight_trailing_white(wrapped_translation)
        print_source_translation(source, translation,
                                wrapped_source, wrapped_translation,
                                rows, cols)
    elif information:
        print(green('[I]: %s' % (meta)))
        print_source_translation(source, translation,
                                wrapped_source, wrapped_translation,
                                rows, cols)


def main():
    """Main function."""
    parser = ArgumentParser(description=__doc__)
    parser.add_argument("po", help="PO file to check")
    parser.add_argument(
        "--no-warning", action="store_true",
        help="Disable warnings")
    parser.add_argument(
        "--pot", action="store_true",
        help="Do not check translations")
    parser.add_argument(
        "--warn-empty", action="store_true",
        help="Warn about empty translations")
    parser.add_argument(
        "--information", action="store_true",
        help="Output all translations")

    args = parser.parse_args()
    if not os.path.isfile(args.po):
        print("{}: file does not exist or is not a regular file".format(args.po), file=stderr)
        return 1

    for translation in polib.pofile(args.po):
        check_translation(translation, args.pot, args.no_warning, args.warn_empty, args.information)
    return 0

if __name__ == "__main__":
    exit(main())

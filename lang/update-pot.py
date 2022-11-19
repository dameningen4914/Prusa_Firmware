#!/usr/bin/env python3

"""
Script updates the Firmware.pot file.

The script does the following:
1. Current Firmware.pot is backed up with a copy, Firmware.pot.bak
2. Runs lang-extract.py with all the correct arguments.
"""

import sys
import os
from pathlib import Path, PurePath
import shutil
import subprocess
from subprocess import CalledProcessError

import polib
from polib import POFile

BASE_DIR: Path = Path.cwd().resolve()
PROJECT_DIR: Path = BASE_DIR.parent
PO_DIR: Path = BASE_DIR / "po"
PO_FILE_LIST: list[Path] = []
POT_REFERENCE: POFile = polib.pofile(PO_DIR / "Firmware.pot")

SEARCH_REGEX = "[a-zA-Z]*.[ch]*"
SEARCH_PATHS = ["./Firmware", "./Firmware/mmu2"]

def main():

    # Start by creating a back-up of the current Firmware.pot
    shutil.copy(PO_DIR / "Firmware.pot", PO_DIR / "Firmware.pot.bak")

    # Get the relative prepend of Project directory relative to ./po directory
    # This should be something like '../../'
    # Note: Pathlib's relative_to() doesn't handle this case yet, so let's use os module
    rel_path = os.path.relpath(PROJECT_DIR, PO_DIR)

    # We want to search for the C/C++ files relative to the .po/ directory
    # Lets append to the search path an absolute path.
    for index, search_path in enumerate(SEARCH_PATHS[:]):
        try:
            # Example: Converts ./Firmware to ../../Firmware
            SEARCH_PATHS[index] = PurePath(rel_path).joinpath(search_path)

            # Example: Convert ../../Firmware to ../../Firmware/[a-zA-Z]*.[ch]*
            SEARCH_PATHS[index] = PurePath(SEARCH_PATHS[index]).joinpath(SEARCH_REGEX)
        except ValueError as error:
            print(error)

    # Run the lang-extract.py script
    try:
        subprocess.check_output(
            [
                "python",
                "lang-extract.py",
                "--no-missing",
                "-s",
                "-o",
                "./Firmware.pot",
                SEARCH_PATHS[0],
                SEARCH_PATHS[1],
            ]
        )
    except CalledProcessError as error:
        print(error)


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        sys.exit(-1)

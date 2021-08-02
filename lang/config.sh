#!/bin/sh
#
# Version 1.0.1 Build 7
#
# config.sh - multi-language support configuration script
#  Definition of absolute paths etc.
#  This file is 'included' in all scripts.
#
#############################################################################
# Change log:
# 31 May 2018,  XPila,     Initial
#  9 June 2020, 3d-gussner, Added version and Change log
#  9 June 2020, 3d-gussner, colored output
#  2 Apr. 2021, 3d-gussner, Use `git rev-list --count HEAD config.sh`
#                           to get Build Nr
# 15 July 2021, 3d-gussner, Check if variables are set by other scripts
#                           and use these. More flexible for different build
#                           scripts
#                           Check correctly if files or dirs exist
#############################################################################
#
# Arduino main folder:
if [ -z "$ARDUINO" ]; then
    export ARDUINO=~/arduino-1.8.5
fi
#
# Arduino builder:
if [ -z "$BUILDER" ]; then
    export BUILDER=$ARDUINO/arduino-builder
fi
#
# AVR gcc tools:
if [ -z "$OBJCOPY" ]; then
    export OBJCOPY=$ARDUINO/hardware/tools/avr/bin/avr-objcopy
fi
if [ -z "$OBJDUMP" ]; then
    export OBJDUMP=$ARDUINO/hardware/tools/avr/bin/avr-objdump
fi
#
# Output folder:
if [ -z "$OUTDIR" ]; then
    export OUTDIR="../../Prusa-Firmware-build"
fi
#
# Objects folder:
if [ -z "$OBJDIR" ]; then
    export OBJDIR="$OUTDIR/sketch"
fi
#
# Generated elf file:
if [ -z "$INOELF" ]; then
    export INOELF="$OUTDIR/Firmware.ino.elf"
fi
#
# Generated hex file:
if [ -z "$INOHEX" ]; then
    export INOHEX="$OUTDIR/Firmware.ino.hex"
fi

echo "$(tput setaf 2)config.sh started$(tput sgr0)" >&2

_err=0

echo -n " Arduino main folder: " >&2
if [ -d "$ARDUINO" ]; then echo "$(tput setaf 2)OK$(tput sgr0)" >&2; else echo "$(tput setaf 1)NG!$(tput sgr0)" >&2; _err=1; fi

echo -n " Arduino builder: " >&2
if [ -e $BUILDER ]; then echo "$(tput setaf 2)OK$(tput sgr0)" >&2; else echo "$(tput setaf 1)NG!$(tput sgr0)" >&2; _err=2; fi

echo " AVR gcc tools:" >&2
echo -n "   objcopy " >&2
if [ -e $OBJCOPY ]; then echo "$(tput setaf 2)OK$(tput sgr0)" >&2; else echo "$(tput setaf 1)NG!$(tput sgr0)" >&2; _err=3; fi
echo -n "   objdump " >&2
if [ -e $OBJDUMP ]; then echo "$(tput setaf 2)OK$(tput sgr0)" >&2; else echo "$(tput setaf 1)NG!$(tput sgr0)" >&2; _err=4; fi

echo -n " Output folder: " >&2
if [ -d $OUTDIR ]; then echo "$(tput setaf 2)OK$(tput sgr0)" >&2; else echo "$(tput setaf 1)NG!$(tput sgr0)" >&2; _err=5; fi

echo -n " Objects folder: " >&2
if [ -d $OBJDIR ]; then echo "$(tput setaf 2)OK$(tput sgr0)" >&2; else echo "$(tput setaf 1)NG!$(tput sgr0)" >&2; _err=6; fi

echo -n " Generated elf file: " >&2
if [ -e $INOELF ]; then echo "$(tput setaf 2)OK$(tput sgr0)" >&2; else echo "$(tput setaf 1)NG!$(tput sgr0)" >&2; _err=7; fi

echo -n " Generated hex file: " >&2
if [ -e $INOHEX ]; then echo "$(tput setaf 2)OK$(tput sgr0)" >&2; else echo "$(tput setaf 1)NG!$(tput sgr0)" >&2; _err=8; fi

if [ $_err -eq 0 ]; then
 echo "$(tput setaf 2)config.sh finished with success$(tput sgr0)" >&2
 export CONFIG_OK=1
else
 echo "$(tput setaf 1)config.sh finished with errors!$(tput sgr0)" >&2
 export CONFIG_OK=0
fi

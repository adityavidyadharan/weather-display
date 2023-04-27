#!/bin/bash

# Scalar vector icons to Adafruit GFX format script for esp32-weather-epd.
# Copyright (C) 2022-2023  Luke Marzen
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

mkdir -p icons
mkdir -p png


PNG_PATH="./png"
PNG_FILES="${PNG_PATH}/resized/*.png"
HEADER_PATH="../icons/headers"
HEADER="../icons/icons.h"

echo "Cleaning old files..."
if [ -e "$HEADER_PATH" ];then rm -rf "$HEADER_PATH" ; fi
mkdir $HEADER_PATH
if [ -e "$HEADER" ];then rm "$HEADER" ; fi

for f in $PNG_FILES
do
  echo "Generating header for $f..."
  out="${HEADER_PATH}/$(basename $f .png).h"
  python3 convert.py $f $out
done

echo "Generating include statements..."
echo "#ifndef __ICONS_H__" > $HEADER
echo "#define __ICONS_H__" >> $HEADER
for f in ${HEADER_PATH}/*.h
do
    echo "#include \"headers/$(basename $f)\"" >> $HEADER
done
echo "#endif" >> $HEADER

echo "Done."

#!/bin/bash

# get the path to the desktop directory
desktop=$(xdg-user-dir DESKTOP)

# loop through all html files in the current directory
for file in *.html; do
# check if the file contains <a> and </a> tag using grep
if grep -q "<a>.*</a>" "$file"; then
# copy the file to the desktop directory using cp
cp "$file" "$desktop"
fi
done

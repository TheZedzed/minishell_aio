#!/bin/bash

#delete "_bonus" in all files from directories and sub-directories (hidden files exclude)
#find . -not -path './.*' -execdir sed -i '' 's/_bonus//g' {} \;

#rename files without $DEL
DEL="_bonus"
FILES=$(find . -not -path './.*')
for elem in $FILES; do
	if [[ $elem =~ $DEL ]]; then
		mv $elem ${elem/$DEL/""}
	fi
done

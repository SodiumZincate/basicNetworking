#!/bin/bash

if [ -z "$1" ]; then
	echo "Usage: $0 <directory>"
	echo "Usage: $0 <file>"
	exit 1
fi

# set the directory
item="$1"

# initialize the url
url="http://localhost:8080/upload"

# initialize the command
cmd="curl -X POST"

# loop through files
if [ -f "$item" ]; then
	cmd+=" -F \"files=@$item\""
elif [ -d "$item" ]; then
	for file in "$item"/*; do
		if [ -f "$file" ]; then
			cmd+=" -F \"files=@$file\""
		elif [ -d "$file" ]; then
			echo "Skipping $file/"
		else
			echo "Skipping $item"
		fi
	done
fi

# add url to curl command
cmd+=" $url"

#execute cmd
eval $cmd
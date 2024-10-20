#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <path>"
    exit 1
fi

path=$1

if [ ! -d "$path" ]; then
    echo "Error: $path is not a directory."
    exit 1
fi

# Count directories and files
dir_count=$(find "$path" -type d | wc -l | xargs)
file_count=$(find "$path" -type f | wc -l | xargs)

# Adjust for the current directory being counted
if [ "$dir_count" -gt 0 ]; then
    dir_count=$((dir_count - 1))
fi

echo "There were $dir_count directories."
echo "There were $file_count regular files."

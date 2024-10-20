#!/bin/bash

{
    # Disable exit on error
    set +e

    if [ $# -ne 1 ]; then
        echo "Usage: $0 <path>"
        exit 1
    fi

    # Check if the given path is a directory
    if [ ! -d "$1" ]; then
        echo "Error: $1 is not a valid directory."
        exit 1
    fi

    # Get directory count, suppress errors, and set output to variables
    dir_count=$(find "$1" -type d 2>/dev/null | wc -l | xargs || true)

    # Get file count, suppress errors
    file_count=$(find "$1" -type f 2>/dev/null | wc -l | xargs || true)

    # Subtract 1 from directory count for the root
    dir_count=$((dir_count - 1))

    # Print results
    echo "There were $dir_count directories."
    echo "There were $file_count regular files."

    # Exit with status 0 within the subshell
    exit 0

} 2>/dev/null # Suppress all error outputs

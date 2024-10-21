#!/usr/bin/env bats

setup() {
    BATS_TMPDIR=$(mktemp --directory)
}

teardown() {
    rm -rf "$BATS_TMPDIR"
}

# Tests for file_disemvowel in the main directory
@test "file_disemvowel exists in main directory" {
    [ -f "./file_disemvowel" ]
}

@test "file_disemvowel is executable in main directory" {
    [ -x "./file_disemvowel" ]
}

@test "file_disemvowel runs successfully in main directory" {
    run ./file_disemvowel_dir/file_disemvowel < ./file_disemvowel_dir/tests/small_input > "$BATS_TMPDIR/small_output"
    [ "$status" -eq 0 ]
}

@test "file_disemvowel works with standard input and output in main directory" {
    ./file_disemvowel_dir/file_disemvowel < ./file_disemvowel_dir/tests/small_input > "$BATS_TMPDIR/small_output"
    run diff -wbB ./file_disemvowel_dir/tests/small_output "$BATS_TMPDIR/small_output"
    [ "$status" -eq 0 ]
}

@test "file_disemvowel works with large files in main directory" {
    ./file_disemvowel_dir/file_disemvowel < ./file_disemvowel_dir/tests/as_you_like_it.txt > "$BATS_TMPDIR/as_you_like_it.output"
    run diff -wbB ./file_disemvowel_dir/tests/as_you_like_it_disemvowelled.txt "$BATS_TMPDIR/as_you_like_it.output"
    [ "$status" -eq 0 ]
}

@test "file_disemvowel works with specified input in main directory" {
    ./file_disemvowel_dir/file_disemvowel ./file_disemvowel_dir/tests/small_input > "$BATS_TMPDIR/small_output"
    run diff -wbB ./file_disemvowel_dir/tests/small_output "$BATS_TMPDIR/small_output"
    [ "$status" -eq 0 ]
}

@test "file_disemvowel works with specified input and output files in main directory" {
    ./file_disemvowel_dir/file_disemvowel ./file_disemvowel_dir/tests/small_input "$BATS_TMPDIR/small_output"
    run diff -wbB ./file_disemvowel_dir/tests/small_output "$BATS_TMPDIR/small_output"
    [ "$status" -eq 0 ]
}

@test "file_disemvowel works with large specified files in main directory" {
    ./file_disemvowel_dir/file_disemvowel ./file_disemvowel_dir/tests/as_you_like_it.txt "$BATS_TMPDIR/as_you_like_it.output"
    run diff -wbB ./file_disemvowel_dir/tests/as_you_like_it_disemvowelled.txt "$BATS_TMPDIR/as_you_like_it.output"
    [ "$status" -eq 0 ]
}

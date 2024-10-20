#!/usr/bin/env bats

setup() {
    BATS_TMPDIR=$(mktemp --directory)
}

teardown() {
    rm -rf "$BATS_TMPDIR"
}

@test "file_disemvowel exists" {
    [ -f "./file_disemvowel" ]
}

@test "file_disemvowel is executable" {
    [ -x "./file_disemvowel" ]
}

@test "file_disemvowel runs successfully" {
    run ./file_disemvowel < file_disemvowel_dir/tests/small_input > "$BATS_TMPDIR"/small_output
    [ "$status" -eq 0 ]
}

@test "file_disemvowel works with standard input and standard output" {
    ./file_disemvowel < file_disemvowel_dir/tests/small_input > "$BATS_TMPDIR"/small_output
    run diff -wbB file_disemvowel_dir/tests/small_output "$BATS_TMPDIR"/small_output
    [ "$status" -eq 0 ]
}

@test "file_disemvowel works with large files stdin/stdout" {
    ./file_disemvowel < file_disemvowel_dir/tests/as_you_like_it.txt > "$BATS_TMPDIR"/as_you_like_it.output
    run diff -wbB file_disemvowel_dir/tests/as_you_like_it_disemvowelled.txt "$BATS_TMPDIR"/as_you_like_it.output
    [ "$status" -eq 0 ]
}

@test "file_disemvowel works with specified input and standard output" {
    ./file_disemvowel file_disemvowel_dir/tests/small_input > "$BATS_TMPDIR"/small_output
    run diff -wbB file_disemvowel_dir/tests/small_output "$BATS_TMPDIR"/small_output
    [ "$status" -eq 0 ]
}

@test "file_disemvowel works with specified input and output files" {
    rm -f "$BATS_TMPDIR"/small_output
    ./file_disemvowel file_disemvowel_dir/tests/small_input "$BATS_TMPDIR"/small_output
    run diff -wbB file_disemvowel_dir/tests/small_output "$BATS_TMPDIR"/small_output
    [ "$status" -eq 0 ]
}

@test "file_disemvowel works with large specified files" {
    ./file_disemvowel file_disemvowel_dir/tests/as_you_like_it.txt "$BATS_TMPDIR"/as_you_like_it.output
    run diff -wbB file_disemvowel_dir/tests/as_you_like_it_disemvowelled.txt "$BATS_TMPDIR"/as_you_like_it.output
    [ "$status" -eq 0 ]
}

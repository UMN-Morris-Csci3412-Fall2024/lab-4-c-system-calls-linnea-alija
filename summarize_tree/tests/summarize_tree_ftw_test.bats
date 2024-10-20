#!/usr/bin/env bats

setup() {
    BATS_TMPDIR=$(mktemp --directory)
}

teardown() {
    rm -rf "$BATS_TMPDIR"
}

@test "summarize_tree exists" {
    [ -f "summarize_tree" ]
}

@test "summarize_tree is executable" {
    [ -x "summarize_tree" ]
}

@test "summarize_tree runs successfully" {
    run ./summarize_tree test_data/fewer_files
    [ "$status" -eq 0 ]
}

@test "summarize_tree_ftw exists" {
    [ -f "summarize_tree_ftw" ]
}

@test "summarize_tree_ftw is executable" {
    [ -x "summarize_tree_ftw" ]
}

@test "summarize_tree_ftw runs successfully" {
    run ./summarize_tree_ftw test_data/fewer_files
    [ "$status" -eq 0 ]
}

@test "summarize_tree_ftw works with large directory structure" {
    run ./summarize_tree_ftw test_data/loads_o_files
    [ "$status" -eq 0 ]
    [[ "$output" == *"There were 1111 directories."* ]]
    [[ "$output" == *"There were 10001 regular files."* ]]
}

@test "summarize_tree.sh exists" {
    [ -f "summarize_tree.sh" ]
}

@test "summarize_tree.sh is executable" {
    [ -x "summarize_tree.sh" ]
}

@test "summarize_tree.sh runs successfully" {
    run ./summarize_tree.sh test_data/fewer_files
    [ "$status" -eq 0 ]
}

@test "summarize_tree.sh works with small directory structure" {
    run ./summarize_tree.sh test_data/fewer_files
    [ "$status" -eq 0 ]
    [[ "$output" == *"There were 10 directories."* ]]
    [[ "$output" == *"There were 100 regular files."* ]]
}

@test "summarize_tree.sh works with large directory structure" {
    run ./summarize_tree.sh test_data/loads_o_files
    [ "$status" -eq 0 ]
    [[ "$output" == *"There were 1111 directories."* ]]
    [[ "$output" == *"There were 10001 regular files."* ]]
}

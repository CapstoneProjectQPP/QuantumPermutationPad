#!/bin/bash

TEST_DIR=$(cd -P -- "$(dirname -- "$0")" && pwd -P)
DEFAULT_DIR="$TEST_DIR"/..

cd "$TEST_DIR" || exit 1
sudo "$DEFAULT_DIR"/C++/bin/unit_test.exe --reporter JUnit::out=catch_result.xml

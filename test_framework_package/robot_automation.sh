#!/bin/bash

TEST_DIR="$(dirname "$0")"

export PYTHONPATH=$TEST_DIR

cd "$TEST_DIR" || exit 1
robot "$TEST_DIR"/automation/*

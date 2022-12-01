#!/bin/bash

# Reset
COLOR_RESET='\033[0m' # Text Reset

# Regular Colors
CYAN='\033[0;36m' # Cyan

# Background
ON_RED='\033[41m'    # Red
ON_GREEN='\033[42m'  # Green
ON_YELLOW='\033[43m' # Yellow

set -e

echo "${ON_YELLOW} INFO ${COLOR_RESET} ${CYAN} Building all targets (bazel build //...) ... ${COLOR_RESET}"

BAZEL_BUILD=$(bazel build //...)

if ${BAZEL_BUILD}; then
    echo "${ON_GREEN} SUCCESS ${COLOR_RESET} ${CYAN} All targets tested successfully. ${COLOR_RESET}"
else
    echo "${ON_RED} ERROR ${COLOR_RESET} ${CYAN} Testing failed. ${COLOR_RESET}"
    exit 1
fi

#!/bin/bash

# TODO migrate to having bazel target for running clang-format on all files
fd --extension cc --extension h --exec clang-format -style=Google

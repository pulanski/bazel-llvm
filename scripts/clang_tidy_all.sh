#!/bin/bash

# Loop over all .cc, .h files in the mandelbrot directory and kaleidoscope directory and run clang-tidy on them.

# find all .cc and .h files in the mandelbrot directory and then execute clang-tidy on them

while IFS= read -r -d '' file; do
    echo "Running clang-tidy on $file"
    clang-tidy -p build "$file" -- -std=c++17
done < <(find mandelbrot \( -name "*.cc" -or -name "*.h" \) -print0)

while IFS= read -r -d '' file; do
    echo "Running clang-tidy on $file"
    clang-tidy -p build "$file" -- -std=c++17
done < <(find kaleidoscope \( -name "*.cc" -or -name "*.h" \) -print0)

#! /bin/bash

find . -iname '*.h' -exec clang-format -i {} \;
find . -iname '*.c' -exec clang-format -i {} \;

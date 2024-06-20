#!/bin/bash

#cpplint --filter=-legal/copyright task*.c | grep "Total errors found"

cpplint --filter=-legal/copyright *.c 
clang-tidy-12 -header-filter='.*'  -checks='-*,cppcoreguidelines*' *.c --
#clang-tidy-12 -header-filter='.*'  -checks='*,-llvmlibc-restrict-system-libc-headers,-clang-analyzer-security*' *.c --
#clang-tidy-12 -header-filter='.*'  -checks='*,-llvmlibc-restrict-system-libc-headers' *.c -- | grep warning:

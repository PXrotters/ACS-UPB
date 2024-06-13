#!/bin/bash
# SPDX-License-Identifier: BSD-3-Clause

# (Re)Create tests/ directory with saved information.
rm -fr ../tests/
cp -r "$CHECKER_DATA_DIRECTORY"/../tests ..

# Checking and grading happens in the tests/ directory.
pushd ../tests > /dev/null || exit 1
./grade.sh
popd > /dev/null || exit 1

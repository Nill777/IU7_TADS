#!/bin/bash

echo Result testing build_debug:
sh ./build_debug.sh
sh ./func_tests/scripts/func_tests.sh
sh ./clean.sh
echo ""

echo Result testing build_release:
sh ./build_release.sh
sh ./func_tests/scripts/func_tests.sh
sh ./clean.sh
echo ""

echo Result testing build_debug_asan:
sh ./build_debug_asan.sh
sh ./func_tests/scripts/func_tests.sh
sh ./clean.sh
echo ""

echo Result testing build_debug_msan:
sh ./build_debug_msan.sh
sh ./func_tests/scripts/func_tests.sh
sh ./clean.sh
echo ""

echo Result testing build_debug_ubsan:
sh ./build_debug_ubsan.sh
sh ./func_tests/scripts/func_tests.sh
sh ./clean.sh
echo ""

echo Result gcov:
sh ./build_gcov.sh
sh ./func_tests/scripts/func_tests.sh
sh ./collect_coverage.sh
sh ./clean.sh
echo ""
echo Temporary files removed
echo ""
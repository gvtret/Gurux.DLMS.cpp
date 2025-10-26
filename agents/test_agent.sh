#!/bin/bash
# ----------------------------------------------------------
# TestAgent — Runs all unit tests via CTest/GoogleTest.
# ----------------------------------------------------------
set -e
echo "[TestAgent] Running GuruxDLMS tests..."
cd build
ctest --output-on-failure
echo "[TestAgent] All tests passed successfully."

#!/bin/bash
# ----------------------------------------------------------
# LintAgent — Verifies formatting and runs static analysis.
# ----------------------------------------------------------
set -e
echo "[LintAgent] Checking formatting..."
clang-format --dry-run --Werror $(find development/include development/src tests -name '*.cpp' -or -name '*.h')
echo "[LintAgent] Running clang-tidy..."
clang-tidy $(find development/src -name '*.cpp') -- -Idevelopment/include -std=c++11
echo "[LintAgent] Linting completed successfully."

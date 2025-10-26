#!/bin/bash
# ----------------------------------------------------------
# DocAgent — Generates API documentation using Doxygen.
# ----------------------------------------------------------
set -e
echo "[DocAgent] Generating documentation..."
if ! command -v doxygen >/dev/null; then
  echo "Error: Doxygen not installed. Install with 'sudo apt install doxygen graphviz'."
  exit 1
fi
cd build
doxygen Doxyfile
echo "[DocAgent] Documentation generated at build/docs/html"

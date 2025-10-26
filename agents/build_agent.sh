#!/bin/bash
# ----------------------------------------------------------
# BuildAgent — Configures and builds the GuruxDLMS project.
# ----------------------------------------------------------
set -e
echo "[BuildAgent] Configuring and building GuruxDLMS..."
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel $(nproc)
echo "[BuildAgent] Build completed successfully."

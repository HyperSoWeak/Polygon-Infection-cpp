#!/usr/bin/env bash
set -euo pipefail

project_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
prefix="${ALLEGRO_PREFIX:-$project_root/.allegro}"
build_dir="${BUILD_DIR:-$project_root/build}"

export PKG_CONFIG_PATH="$prefix/lib/pkgconfig:$prefix/lib64/pkgconfig:${PKG_CONFIG_PATH:-}"

if ! pkg-config --exists allegro-5; then
  echo "Allegro not found via pkg-config. Running installer..."
  "$project_root/scripts/install_deps.sh"
  if ! pkg-config --exists allegro-5; then
    echo "Allegro still not found. Please check install output."
    exit 1
  fi
fi

cmake -S "$project_root" -B "$build_dir"
cmake --build "$build_dir"

echo "Build complete. Binary: $build_dir/polygon-infection"

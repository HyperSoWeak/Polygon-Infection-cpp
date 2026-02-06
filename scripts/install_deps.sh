#!/usr/bin/env bash
set -euo pipefail

if [[ ${EUID:-0} -eq 0 ]]; then
  echo "Please run as a normal user (not root)."
  exit 1
fi

need_cmd() {
  command -v "$1" >/dev/null 2>&1
}

project_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
prefix="${ALLEGRO_PREFIX:-$project_root/.allegro}"
build_dir="${ALLEGRO_BUILD_DIR:-$project_root/.allegro-build}"
allegro_version="${ALLEGRO_VERSION:-5.2.9.0}"
allegro_tgz="allegro-${allegro_version}.tar.gz"
allegro_url="${ALLEGRO_URL:-https://github.com/liballeg/allegro5/releases/download/${allegro_version}/${allegro_tgz}}"
use_system="${USE_SYSTEM:-0}"

os=""
if [[ -f /etc/os-release ]]; then
  . /etc/os-release
  os=${ID:-}
fi

install_system_allegro() {
  case "$os" in
    ubuntu|debian|linuxmint)
      sudo apt-get update
      sudo apt-get install -y liballegro5-dev pkg-config
      ;;
    fedora)
      sudo dnf install -y allegro5-devel pkgconf-pkg-config
      ;;
    arch|manjaro)
      sudo pacman -S --needed allegro pkgconf
      ;;
    opensuse*|suse)
      sudo zypper install -y allegro-devel pkg-config
      ;;
    *) 
      return 1
      ;;
  esac
}

echo "Detected OS: ${os:-unknown}"
echo "Install prefix: ${prefix}"

install_local_allegro() {
  if ! need_cmd cmake; then
    echo "cmake not found. Please install cmake and re-run."
    exit 1
  fi
  if ! need_cmd make; then
    echo "make not found. Please install build tools and re-run."
    exit 1
  fi
  if ! need_cmd gcc && ! need_cmd g++; then
    echo "C/C++ compiler not found. Please install gcc/g++ (or clang) and re-run."
    exit 1
  fi
  if ! need_cmd curl && ! need_cmd wget; then
    echo "curl or wget required to download Allegro source."
    exit 1
  fi

  rm -rf "$build_dir"
  mkdir -p "$build_dir"
  echo "Downloading Allegro ${allegro_version}..."
  if need_cmd curl; then
    curl -L "$allegro_url" -o "$build_dir/$allegro_tgz"
  else
    wget -O "$build_dir/$allegro_tgz" "$allegro_url"
  fi
  tar -C "$build_dir" -xf "$build_dir/$allegro_tgz"

  src_dir="$build_dir/allegro-${allegro_version}"
  if [[ ! -d "$src_dir" ]]; then
    echo "Allegro source directory not found at $src_dir"
    exit 1
  fi

  cmake -S "$src_dir" -B "$build_dir/build" -DCMAKE_INSTALL_PREFIX="$prefix" -DCMAKE_POLICY_VERSION_MINIMUM=3.5
  cmake --build "$build_dir/build"
  cmake --install "$build_dir/build"
}

if [[ "$use_system" == "1" ]]; then
  if install_system_allegro; then
    echo "Allegro 5 dev packages installed (system)."
  else
    echo "Unsupported or unknown distro."
    echo "Please install Allegro 5 development packages and pkg-config manually."
    echo "Examples:"
    echo "  Debian/Ubuntu: sudo apt-get install liballegro5-dev pkg-config"
    echo "  Fedora: sudo dnf install allegro5-devel pkgconf-pkg-config"
    echo "  Arch: sudo pacman -S allegro pkgconf"
    echo "  openSUSE: sudo zypper install allegro-devel pkg-config"
    exit 1
  fi
else
  install_local_allegro
  echo "Allegro 5 installed locally at: $prefix"
  echo "Export PKG_CONFIG_PATH so build can find it:"
  echo "  export PKG_CONFIG_PATH=\"$prefix/lib/pkgconfig:$prefix/lib64/pkgconfig:\$PKG_CONFIG_PATH\""
fi

if need_cmd pkg-config; then
  echo "pkg-config is available."
else
  echo "pkg-config not found. Please install it and re-run."
  exit 1
fi

if pkg-config --exists allegro-5; then
  echo "Allegro pkg-config files detected."
else
  echo "Allegro pkg-config files NOT found."
  echo "If Allegro is installed in a non-standard prefix, set PKG_CONFIG_PATH."
  exit 1
fi

echo "All set. You can now build with CMake:"
echo "  cmake -S . -B build"
echo "  cmake --build build"

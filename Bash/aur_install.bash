#!/bin/bash

# Simple bash script for installing packages from AUR. (Arch User Repository)

# Argument check
if [ $# != 1 ]
then

  echo "aur_install: missing file operand"
  exit 1

fi

name="$1"
type=".tar.gz"

# Download archive
curl -O "https://aur.archlinux.org/cgit/aur.git/snapshot/$name$type"

# Unpacking archive
tar -xf "$name$type"

# Package build
cd "$name" && makepkg -si PKGBUILD

# Remove archive
cd ../ && rm -r "$name" "$name$type"
#!/usr/bin/env bash
set -e

PREFIX="${HOME}/.local"
BIN_DIR="${PREFIX}/bin"

echo "Building backpack..."
mkdir -p "$BIN_DIR"
BUILD_DIR="$(pwd)/build"
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"
cmake .. -DCMAKE_INSTALL_PREFIX="$PREFIX"
cmake --build . --target install
cd ..

read -p "Create symlink 'bp' to 'backpack'? (y/N) " CREATE_SYMLINK
if [[ "$CREATE_SYMLINK" =~ ^[Yy]$ ]]; then
    ln -sf "$BIN_DIR/backpack" "$BIN_DIR/bp"
    echo "Symlink 'bp' created in $BIN_DIR."
fi


echo "Backpack installed to $BIN_DIR."
echo "Make sure $BIN_DIR is in your PATH, e.g.:"
echo '  export PATH="$HOME/.local/bin:$PATH"'

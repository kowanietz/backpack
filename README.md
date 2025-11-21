# backpack

__backpack__ is a CLI-tool that lets you quickly store files and directories into a "backpack" - a lightweight personal
clipboard for your filesystem.

## Usage

`bp ls` __lists__ all items in your backpack

`bp rm <item>` __removes__ an item from your backpack

`bp add <file>` __adds__ an item to your backpack

`bp cut <file>` __moves__ an item to your backpack

`bp paste <item>` __pastes__ an item from your backpack to the current path

`bp pop <item>` __moves__ an item from your backpack to the current path

## Installation (MacOS only)

```bash
bash ./scripts/install.sh
```

_symlink highly recommended_

### Rebuild & Reinstall (development)

```bash
cd build \
  && cmake .. -DCMAKE_INSTALL_PREFIX=$HOME/.local \
  && cmake --build . \
  && cmake --install .

```
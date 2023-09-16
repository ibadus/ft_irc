# FT_IRC

## Description

42 project: IRC server.

## Usage

compile with:

```bash
$> make
```

run with:

```bash
$> ./irc <port>
```

### Notes

port `0` = random port.

## Code architecture (WIP)

- `./server` is the folder that contains all the server code (`.cpp` files only).

- `./include` is the folder that contains all the includes (`.hpp`, `.tpp`) needed by the `.cpp` files in the `./server` folder.

- Yes the `./include` folder contains nested folders, be cautious in the makefile to specify the right one (ONLY folders).

- In each `.cpp` files it's necessary to include the relative path from the file to the header file.

### Warning

Always include necessary includes in all files, i.e. if `A.cpp` needs `<string>` include it inside `A.cpp` and also in `A.hpp` if `A.hpp` needs it too.

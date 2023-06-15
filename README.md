# Sparkly-FX
A module for TF2 that adds awesome effects and works alongside HLAE. Also very simple to use!

## Building

1. Open your build directory
```sh
mkdir build
cd build
```
2. Configure CMake to use MSVC *(for inline assembly)* and compile *32-bit* code
```sh
cmake <sparklyfx path> -A Win32
```
3. Build
```sh
cmake --build .
```
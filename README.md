# Xdelta

Xdelta version 3 is a C library and command-line tool for delta
compression using VCDIFF/RFC 3284 streams.

# License

This repository contains branches of Xdelta 3.x that were
re-licensed by the original author under the [Apache Public
License version 2.0](http://www.apache.org/licenses/LICENSE-2.0),
namely:

- __release3_0_apl__ Change to APL based on 3.0.11 sources
- __release3_1_apl__ Merges release3_0_apl with 3.1.0 sources

The original GPL licensed Xdelta lives at http://github.com/jmacd/xdelta-gpl.

# Documentation

See the [command-line usage](https://github.com/jmacd/xdelta/blob/wiki/CommandLineSyntax.md).  See [wiki directory](https://github.com/jmacd/xdelta/tree/wiki).


# How to build
- Clone repo
- cd into repo folder
- mkdir build
- cd build
- cmake -DCMAKE_BUILD_TYPE=Release ..
- If on linux, run make
- If on Windows, open the generated solution file with Visual Studio e build.

The basic command cmake -DCMAKE_BUILD_TYPE=Release .. will build xdelta3 as a static library, with no secondary compression support and only the decoder code. So the bare minimum. Here is an example building with all features included:

cmake -DXD3_ENABLE_SECONDARY_COMPRESSION=ON -DXD3_ENABLE_ENCODER=ON -DXD3_ENABLE_VCDIFF_TOOLS=ON -DXD3_ENABLE_LZMA=on -DCMAKE_BUILD_TYPE=Release ..

You can additionally specify -DXD3_BUILD_AS_EXE=ON to build an executable instead of a static libray.

Note: for lzma support, liblzma dev package must be installed in your system.


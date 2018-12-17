# ElVisX

> A fork of [ElVis](http://www.sci.utah.edu/software/elvis.html)

## What's Different with ElVis

* New BOOST library(1.69.0): Compatible with VS 2017
* New QT API(WebView): Use QT5WebView to use newer version of QT
* Fix bugs in new compiler 

## Usage

1. Use `CMake` to build up the source.
2. build `ALL_BUILD`(default) solution.
3. build `INSTALL` solution.
4. main GUI program is  `BUILD_DIR/dist/bin/ElVis.exe`.

## Known Issues

* We recommend you use Visual Studio 2015, cause `nvcc` cannot load VS 2017 config properly.

## Tested Device

* Windows 10(17763.194) x64 + CUDA 9.0 + VS 2017(`nvcc` with VS 2015) + QT 5.12.0
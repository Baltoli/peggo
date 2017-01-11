# peggo: A PEG Parser Generator

[![Build Status](https://travis-ci.org/Baltoli/peggo.svg?branch=master)](https://travis-ci.org/Baltoli/peggo)

This project implements a PEG parser generator written in C11.

## Building

To build the project:

```
git clone https://github.com/baltoli/peggo
cd peggo
mkdir Build
cd Build
cmake ..
make
```

The available options that can be passed to CMake are:

* `BUILD_DOCUMENTATION`: if this option is true, then Doxygen can be used to
  build generated documentation for the project with `make doc`.

### Tests

Currently, tests for the project are implemented using
[CMocka](http://www.cmocka.org), which must be installed in order to build the
test suite. If CMocka is installed, then the tests will be built automatically
(however, this is optional; if CMocka is not installed, then the project can
still be built without tests). The test suite can be run with `test/unit_tests`.

## Usage

The current interface presented by peggo is a C library that provides an
interface to construct PEG grammars, and to parse strings according to these
grammars.

Currently, automatic installation using CMake is not supported, but this will be
added in a future version. To use the project as it is now, build according to
the instructions above, then copy `Build/src/peggo/libpeggo.a` and all header
files in `src/peggo` to their appropriate locations. A project can then include
the peggo header files and link using `-lpeggo`.

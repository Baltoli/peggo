# peggo: A PEG Parser Generator

[![Build Status](https://travis-ci.org/Baltoli/peggo.svg?branch=master)](https://travis-ci.org/Baltoli/peggo)

This project implements a PEG parser generator written in C11. Documentation for
the latest version can be found [here](https://baltoli.github.io/peggo-docs/index.html).

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
[CMocka](https://cmocka.org), which must be installed in order to build the
test suite. If CMocka is installed, then the tests will be built automatically
(however, this is optional; if CMocka is not installed, then the project can
still be built without tests). The test suite can be run with `test/unit_tests`.

## Usage

The current interface presented by peggo is a C library that provides an
interface to construct PEG grammars, and to parse strings according to these
grammars.

The library can be installed with `make install` (the installation prefix is
customisable as usual with CMake). Then include `<peggo/peggo.h>` and link with
`-lpeggo` to use the parsing API as described in the documentation.

# libfcpp - Frexx C preprocessor library

This is a `build2` package for the [`fcpp`](https://github.com/bagder/fcpp)
C library. It provides a C preprocessor. The C preprocessor is now (mostly?)
ANSI C compliant, and some tweaks have been applied to also make it fairly
usable to process other data files, such as HTML for simple web sites.

The package adds the `FPPTAG_DEPENDS` tag (a function called with the name of
each opened `#include` file) and the `FPPTAG_SHOWVERSION` name for tag 19. It
also fixes the following upstream issues: `fppPreProcess()` closing `stdout`
when an output function is set, a number on the left-hand side of `##`
leaking an internal delimiter into the output, and a crash on diagnostics at
the end of the input.

This package tracks upstream commit `8625dc0` (2025-11-03) as version `1.5.1`,
the version that upstream's sources still report.


## Usage

To start using `libfcpp` in your project, add the following `depends`
value to your `manifest`, adjusting the version constraint as appropriate:

```
depends: libfcpp ^1.5.1
```

Then import the library in your `buildfile`:

```
import libs = libfcpp%lib{fpp}
```


## Importable targets

This package provides the following importable targets:

```
lib{fpp}
```

The preprocessor library. The target name matches upstream's `libfpp`.


## Configuration variables

This package provides the following configuration variables:

```
[uint64] config.libfcpp.nbuff ?= 4096
[uint64] config.libfcpp.nwork ?= 2048
[uint64] config.libfcpp.ninclude ?= 20
```

- `config.libfcpp.nbuff` defines `NBUFF`, the input line buffer size.
- `config.libfcpp.nwork` defines `NWORK`, the work buffer size (the longest
  macro definition or expansion).
- `config.libfcpp.ninclude` defines `NINCLUDE`, the maximum number of include
  directories.

The defaults are upstream's.

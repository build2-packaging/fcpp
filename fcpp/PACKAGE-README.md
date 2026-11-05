# fcpp - Frexx C preprocessor executable

This is a `build2` package for the [`fcpp`](https://github.com/bagder/fcpp)
executable. It is a C preprocessor. The C preprocessor is now (mostly?) ANSI
C compliant, and some tweaks have been applied to also make it fairly usable
to process other data files, such as HTML for simple web sites.

This package tracks upstream commit `8625dc0` (2025-11-03) as version `1.5.1`,
the version that upstream's sources still report.


## Usage

To start using `fcpp` in your project, add the following build-time
`depends` value to your `manifest`, adjusting the version constraint as
appropriate:

```
depends: * fcpp ^1.5.1
```

Then import the executable in your `buildfile`:

```
import fcpp = fcpp%exe{fcpp}
```


## Importable targets

This package provides the following importable targets:

```
exe{fcpp}
```

The preprocessor executable, upstream's `usecpp.c` linked against `libfcpp`.
Usage is `fcpp [options] [infile [outfile]]` and it reads `stdin` and writes
`stdout` by default. Run `fcpp -h` for the options.


## Configuration variables

This package has no configuration variables.

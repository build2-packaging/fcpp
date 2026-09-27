# fcpp - Frexx C preprocessor library and executable

This is a `build2` package repository for [`fcpp`](https://github.com/bagder/fcpp),
the Frexx C preprocessor library and executable.

This file contains setup instructions and other details that are more
appropriate for development rather than consumption. If you want to use
these packages in your `build2`-based project, then instead see the
accompanying `PACKAGE-README.md` files:

- [`libfcpp`](libfcpp/PACKAGE-README.md)
- [`fcpp`](fcpp/PACKAGE-README.md)

The development setup for `fcpp` uses the standard `bdep`-based workflow.
For example:

```
git clone --recurse-submodules https://github.com/build2-packaging/fcpp.git
cd fcpp

bdep init -C @gcc cc config.cxx=g++
bdep update
bdep test
```

The package version is `1.5.1`, the version that upstream's sources still
report, and the `upstream` submodule tracks a later commit. Changes to upstream
source are kept as `.orig`/`.patch` pairs next to the modified files.

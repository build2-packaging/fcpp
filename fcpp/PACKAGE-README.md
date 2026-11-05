# fcpp - An executable

This is a `build2` package for the [`<UPSTREAM-NAME>`](https://<UPSTREAM-URL>)
executable. It is a <SUMMARY-OF-FUNCTIONALITY>.

Note that the `fcpp` executable in this package provides `build2` metadata.


## Usage

To start using `fcpp` in your project, add the following build-time
`depends` value to your `manifest`, adjusting the version constraint as
appropriate:

```
depends: * fcpp ^<VERSION>
```

Then import the executable in your `buildfile`:

```
import! [metadata] <TARGET> = fcpp%exe{<TARGET>}
```


## Importable targets

This package provides the following importable targets:

```
exe{<TARGET>}
```

<DESCRIPTION-OF-IMPORTABLE-TARGETS>


## Configuration variables

This package provides the following configuration variables:

```
[bool] config.fcpp.<VARIABLE> ?= false
```

<DESCRIPTION-OF-CONFIG-VARIABLES>

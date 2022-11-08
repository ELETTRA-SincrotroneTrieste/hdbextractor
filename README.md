# INSTALLATION INSTRUCTIONS FOR the Hdbextractor++ library

## Dependencies

1. mysql and mysql development files
2. meson / ninja build system
3. https://github.com/ELETTRA-SincrotroneTrieste/elettra.eu.libsqldb

## Building and installing the library

Clone the repository https://github.com/ELETTRA-SincrotroneTrieste/hdbextractor:

> git clone https://github.com/ELETTRA-SincrotroneTrieste/hdbextractor

> cd hdbextractor

Adjust PKG_CONFIG_PATH so that it contains the *lib/pkgconfig* directory under the
*elettra.eu.libsqldb* installation, for example:

> export PKG_CONFIG_PATH=/usr/local/elettra.eu.libsqldb/lib/pkgconfig:$PKG_CONFIG_PATH

Generate the *meson build directory*

> meson builddir

Cd into builddir

> cd builddir

Build the *cpp* library. You may want to set the installation prefix and the "lib" 
directory name

> meson configure -Dprefix=/usr/local/hdbextractor

> meson configure -Dlibdir=lib

If you don't specify the *libdir*, please check its value, as well as other configuration
options, issuing the following:

> meson configure

You may want to enable debugging:

> meson configure -Dbuildtype=debug

Once configured, build the library and install it

> ninja && ninja install

This will install the shared library, the include files (under the *include/hdbextractor* folder
if not specified otherwise) and the *pkgconfig* file for third party libraries or programs 
(under *lib/pkgconfig*)

#### LD_LIBRARY_PATH adjustment

Please make sure that the *LD_LIBRARY_PATH* environment variable contains both
*/usr/local/hdbextractor/lib* and */usr/local/elettra.eu.libsqldb/lib* (for example)
before attempting to use the library

## Building the hdbxtest example (simple command line client)

A simple command line client for testing purposes is available under the *hdbxtest* subdirectory
of the project.
You may prefer to use the much more versatile *cumbia read* command line utility instead.
Please refer to the [cumbia-libs](https://github.com/ELETTRA-SincrotroneTrieste/cumbia-libs)
and the [cumbia-historicaldb](https://github.com/ELETTRA-SincrotroneTrieste/cumbia-historicaldb)
project pages.

Change into the *hdbxtest* directory:

> cd hdbextractor/hdbxtest

Make sure that the 

- *elettra.eu.libsqldb* *{prefix}/lib/pkgconfig* and
- *hdbextractor* *{prefix}/lib/pkgconfig*

are both listed in the *PKG_CONFIG_PATH* environment variable:

> export PKG_CONFIG_PATH=/usr/local/elettra.eu.libsqldb/lib/pkgconfig:/usr/local/hdbextractor/lib/pkgconfig:$PKG_CONFIG_PATH

Configure the *meson build directory*:

> meson builddir

> cd builddir

> ninja 

Optionally, the hdb test command line client can be installed:

> meson configure -Dprefix=/usr/local/hdbextractor

> ninja install

The output will show something like this, according to your choices:

```
Installing hdbxtest to /usr/local/hdbextractor/bin
```

Before running the test example, make sure that *LD_LIBRARY_PATH* contains the *lib* directories
of both the *elettra.eu.libsqldb* and *hdbextractor* installation paths:

> export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/hdbextractor/lib:/usr/local/elettra.eu/libsqldb/lib

## Building the Python extension (wrapper)

### Prerequisites

- *swig* 
- *hdbextractor* (installed following the steps above)

### Building and installation

> cd hdbextractor/pyext

You shall add the *{hdbextractor_prefix}/lib/pkgconfig* directory to the PKG_CONFIG_PATH:

> export PKG_CONFIG_PATH=*{hdbextractor_prefix}/lib/pkgconfig*:$PKG_CONFIG_PATH

> meson builddir

If the prerequisites are installed and the command fails, check the PKG_CONFIG_PATH over again.

> cd builddir

Set a proper prefix, according to the prefix specified in the *hdbextractor* configuration phase:

For example:

> meson configure -Dprefix=/usr/local/hdbextractor/python

Build and install

> ninja && ninja install

The output from the command above shows something like  this:

```
Installing _hdbextractor.so to /usr/local/hdbextractor/python/lib
Installing hdbextractor.py to /usr/local/hdbextractor/python/lib
```

To use the python module, you shall add the directory */usr/local/hdbextractor/python/lib*
to PYTHONPATH:

> export PYTHONPATH=/usr/local/hdbextractor/python/lib:$PYTHONPATH

Please make sure that the *LD_LIBRARY_PATH* environment variable contains both
*/usr/local/hdbextractor/lib* and */usr/local/elettra.eu.libsqldb/lib* (for example)
before attempting to use the library or the python module.

Execute the python console

> python3

```
>>> import hdbextractor as h
>>> dir(h)
['BoolVector', 'ConfigurationParser', 'Connection', 'DataSiever', 'DataSieverProgressListener', 'DateTimeUtils', 'DbSettings', 'DoubleVector', 'HdbExtractorListener', 'Hdbextractor', 'IntVector', 'LongIntVector', 'MAXERRORLEN', 'MAXTIMESTAMPLEN', 'MySqlConnection', 'Result', 'ResultListener', 'SRCLEN', 'StringStringMap', 'StringVector', 'SwigPyIterator', 'TIMESTAMPLEN', 'TimeInterval', 'ULongIntVector', 'XVariant', 'XVariantDataInfo', 'XVariantList', 'XVariantPrinter', 'XVariantVector', '_SwigNonDynamicMeta', '__builtin__', '__builtins__', '__cached__', '__doc__', '__file__', '__loader__', '__name__', '__package__', '__spec__', '_hdbextractor', '_swig_add_metaclass', '_swig_python_version_info', '_swig_repr', '_swig_setattr_nondynamic_class_variable', '_swig_setattr_nondynamic_instance_variable', 'weakref']
```


## See also

- The [cumbia-libs](https://github.com/ELETTRA-SincrotroneTrieste/cumbia-libs)
- The [cumbia-historicaldb](https://github.com/ELETTRA-SincrotroneTrieste/cumbia-historicaldb) 

We suggest using *cumbia read* as a command line tool to get data from the historical database.
A *Qt* module and extension are available under [cumbia-historicaldb](https://github.com/ELETTRA-SincrotroneTrieste/cumbia-historicaldb).


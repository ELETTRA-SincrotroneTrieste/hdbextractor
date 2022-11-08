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

### LD_LIBRARY_PATH adjustment

Please make sure that the *LD_LIBRARY_PATH* environment variable contains both
*/usr/local/hdbextractor/lib* and */usr/local/elettra.eu.libsqldb/lib* (for example)
before attempting to use the library

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



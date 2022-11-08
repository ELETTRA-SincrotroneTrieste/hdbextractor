project('hdbextractor', 'cpp', version : '2.0.0',
    default_options : ['c_std=c17', 'cpp_std=c++17'])

project_description = 'extract data from hdb and hdb++ historical databases'

cu_version = meson.project_version() # set in project() below
ver_arr = cu_version.split('.')

cu_major_version = ver_arr[0]
cu_minor_version = ver_arr[1]
cu_micro_version = ver_arr[2]

conf = configuration_data()
# Surround the version in quotes to make it a C string
conf.set_quoted('VERSION', cu_version)
configure_file(output : 'config.h',
               configuration : conf)


headers = [
'src/hdbextractor.h',
'src/hdbextractorlistener.h',
'src/hdbpp/mysqlhdbppschema.h',
'src/hdb/mysqlhdbschema.h',
'src/hdbextractorprivate.h',
'src/utils/datasieverprogresslistener.h',
'src/utils/datasiever.h',
'src/utils/private/datasieverprivate.h',
]

install_headers(headers, subdir : 'hdbextractor') # -> include/hdbextractor/

sources = [
'src/hdbextractor.cpp',
'src/hdbpp/mysqlhdbppschema.cpp',
'src/hdb/mysqlhdbschema.cpp',
'src/utils/datasieverprogresslistener.cpp',
'src/utils/private/datasieverprivate.cpp',
'src/utils/datasiever.cpp'
]

includedirs = include_directories('src/hdb', 'src/hdbpp', 'src/utils', 'src/utils/private')

cpp_arguments = '-DELETTRA_EU_LIBSQLDB_PRINTINFO=1'

# cpp_arguments = []

deps = [ dependency('libsqldb') ]

hdbextractorlib = shared_library('hdbextractor++', sources,
        version : meson.project_version(),
        include_directories : includedirs,
        cpp_args : cpp_arguments,
        dependencies : deps ,
        install : true)

### ====================================== pkg config   ============================
pkgconfig = find_program('pkg-config', required: false)
if not pkgconfig.found()
  error('MESON_SKIP_TEST: pkg-config not found')
endif

pkgg = import('pkgconfig')

h = ['hdbextractor']  # subdirectories of ${prefix}/${includedir} to add to header path
pkgg.generate(
    libraries : hdbextractorlib,
    subdirs : h,
    version : meson.project_version(),
    name : 'libhdbextractor++',
    filebase : 'hdbextractor++',
    description : project_description )


### ====================================== documentation ===========================
doxygen = find_program('doxygen', required : false)
if not doxygen.found()
  error('MESON_SKIP_TEST doxygen not found.')
endif
  doxydata = configuration_data()
  doxydata.set('VERSION', meson.project_version())


if find_program('dot', required : false).found()
  # In the real world this would set the variable
  # to YES. However we set it to NO so that the
  # list of generated files is always the same
  # so tests always pass.
  doxydata.set('HAVE_DOT', 'YES')
else
  doxydata.set('HAVE_DOT', 'NO')
endif

# subdir('doc')


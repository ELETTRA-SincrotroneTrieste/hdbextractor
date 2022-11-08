project('hdbextractor-swig', 'cpp', version : '2.0.0',
    default_options : ['c_std=c17', 'cpp_std=c++17'])

project_description = 'extract data from hdb and hdb++ historical databases - swig wrapper'

cu_version = meson.project_version() # set in project() below
ver_arr = cu_version.split('.')

cu_major_version = ver_arr[0]
cu_minor_version = ver_arr[1]
cu_micro_version = ver_arr[2]


# Python has two pkg-config files, one or extensions, one for embedding:
# > pkg-config --libs python3
# > pkg-config --libs python3-embed
# -lpython3.8
# If you build an extension you should use python3 which doesn't link.

pydep = dependency('python3-embed')

d1 = dependency('libsqldb')
d2 = dependency('hdbextractor++')


swig = find_program('swig')
swig_gen = generator(
    swig,
    output: ['@BASENAME@.cxx'],
    arguments: ['-c++', '-python', '-py3',
                '-outdir', '.',
                '-I' + d1.get_variable(pkgconfig: 'includedir') + '/libsqldb',
                '-I' + d2.get_variable(pkgconfig: 'includedir') + '/hdbextractor',
                '-MMD',
                '-o', './@OUTPUT@', '@INPUT@'],
    depfile: '@BASENAME@.d',
)

swig_source =  'hdbextractor_global.i'

    cpp_source = swig_gen.process(swig_source)
lib = shared_library(
       '_hdbextractor',
       cpp_source,
       dependencies : [ d1, d2, pydep ],
       install: true,
       name_prefix : '',
    )

pymod_tgt = custom_target('pythonmod', install:true, command : [ 'touch', 'dummy.txt' ], output : 'hdbextractor.py',
 install_dir : get_option('libdir'))

# doesn't work
# install_data('hdbextractor.py')

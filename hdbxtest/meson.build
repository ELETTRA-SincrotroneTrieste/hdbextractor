project('hdbxtest', 'cpp',
  version : '1.0',
  default_options : ['warning_level=3', 'cpp_std=c++17'])

deps = [ dependency('hdbextractor++'), dependency('libsqldb')  ]

cpp_argus = []

headers = [ 'myhdbextractorimpl.h' ]

executable('hdbxtest',
           'main.cpp',
           'myhdbextractorimpl.cpp',
           dependencies : deps ,
           cpp_args : cpp_argus,
           install : true)

# install_data('usage.txt', install_dir : get_option('datadir') )

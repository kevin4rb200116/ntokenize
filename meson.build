project('ntokenize', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3',
                     'cpp_std=c++14'])

incdir = include_directories('src/include')

lib = library('ntokenize', 'src/tokenize.cc',
  include_directories: incdir)

bin = executable('ntokenize', 'src/main.cc', link_with: lib,
  include_directories: incdir,
  install : true)

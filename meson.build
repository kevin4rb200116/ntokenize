project('ntokenize', 'cpp',
  version : '0.4',
  default_options : ['cpp_std=c++17'])

incdir = include_directories('src/include')

install_headers(
  'src/include/ntokenize/common.hh',
  'src/include/ntokenize/main.hh',
  'src/include/ntokenize/token.hh',
  'src/include/ntokenize/lex.hh',
  install_dir: 'include/ntokenize')

lib = library('ntokenize',
  'src/lib/main.cc',
  'src/lib/token.cc',
  'src/lib/lex.cc',
  'src/lib/tokens.cc',
  'src/lib/special.cc',
  'src/lib/number.cc',
  'src/lib/string.cc',
  include_directories: incdir,
  version: '0.4', # same as project obviously
  install : true)

bin = executable('ntokenize', 'src/main.cc',
  link_with: lib,
  include_directories: incdir,
  install : true)

ntokenize_dep = declare_dependency(include_directories : incdir,
  link_with : lib)
project('ntokenize', 'cpp',
  version : '0.2',
  default_options : ['cpp_std=c++17'])

incdir = include_directories('src/include')

install_headers(
  'src/include/ntokenize/common.hh',
  'src/include/ntokenize/lex.hh',
  'src/include/ntokenize/tokenize.hh',
  install_dir: 'include/ntokenize')

lib = library('ntokenize',
  'src/tokenize.cc',
  'src/tokens.cc',
  'src/symbols.cc',
  'src/strings.cc',
  'src/numbers.cc',
  'src/lex.cc',
  include_directories: incdir,
  version: '0.2', # same as project obviously
  install : true)

bin = executable('ntokenize', 'src/main.cc',
  link_with: lib,
  include_directories: incdir,
  install : true)

ntokenize_dep = declare_dependency(include_directories : incdir,
  link_with : lib)

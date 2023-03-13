# ntokenize

a simple little tokenizer, based on the python lib2to3
library tokenizer

## Installing from Source

You will need [Meson](https://mesonbuild.com/) and a C++ compiler
like [clang](https://clang.llvm.org/) or [GCC](https://www.gnu.org/software/gcc/)

Open a terminal in the source root directory and run the following commands:

_Building (Debug):_
```sh
meson --buildtype debug ./debug
ninja -C debug
```

_Building (Release):_
```sh
meson --buildtype release ./release
ninja -C release
```

_Running (from Source):_
```sh
# after build
./<build or release>/ntokenize
```

_Installing:_
```sh
ninja -C release install
```

_Installing (Local):_
```sh
# on building
meson --buildtype release --prefix </path/to/installdir> ./release
ninja -C release
ninja -C release install
```
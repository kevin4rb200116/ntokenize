
PROJECT_NAME = tokenize

STATIC_LIB  = lib$(PROJECT_NAME).a
DYNAMIC_LIB  = lib$(PROJECT_NAME).so

SOURCES := $(shell find -name "*.cc" -not -name "test*" -type f)
OBJECTS := $(addsuffix .o, $(SOURCES))

TEST_SOURCES := test.cc
TEST_OBJECTS := test.cc.o

COMPILER       = c++
COMPILERFLAGS = -fPIC -O2

LINKER         = c++
LINKERFLAGS    = 

ARCHIVER = ar
ARCHIVERFLAGS = 

PROGRAM = main

all: $(STATIC_LIB) $(DYNAMIC_LIB)

%.cc.o: %.cc
	@echo "  COMPILE $^ -> $@"
	@$(COMPILER) $(COMPILERFLAGS) -c -o $@ $^

$(STATIC_LIB): $(OBJECTS)
	@echo "  LINK $^ -> $@"
	@$(ARCHIVER) $(ARCHIVERFLAGS) mcs $@ $^

$(DYNAMIC_LIB): $(OBJECTS)
	@echo "  LINK $^ -> $@"
	@$(LINKER) $(LINKERFLAGS) -shared -o $@ $^

$(PROJECT_NAME)_test.elf: $(TEST_OBJECTS) $(STATIC_LIB)
	@echo "  LINK $^ -> $@"
	@$(LINKER) $(LINKERFLAGS) -o $@ $^

clean:
	@rm -fv *.o

distclean: clean
	@rm -fv *.so *.a *.elf
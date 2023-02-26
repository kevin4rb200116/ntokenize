
PROJECT_NAME = ntokenize

STATIC_LIB  = lib$(PROJECT_NAME).a
DYNAMIC_LIB  = lib$(PROJECT_NAME).so

HEADERS := $(shell find -name "*.hh" -type f)
SOURCES := $(shell find -name "*.cc" -type f)
OBJECTS := $(addsuffix .o, $(SOURCES))

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

$(STATIC_LIB): tokenize.cc.o $(HEADERS)
	@echo "  LINK $^ -> $@"
	@$(ARCHIVER) $(ARCHIVERFLAGS) mcs $@ $<

$(DYNAMIC_LIB): tokenize.cc.o $(HEADERS)
	@echo "  LINK $^ -> $@"
	@$(LINKER) $(LINKERFLAGS) -shared -o $@ $<

$(PROJECT_NAME).elf: main.cc.o $(STATIC_LIB)
	@echo "  LINK $^ -> $@"
	@$(LINKER) $(LINKERFLAGS) -o $@ $^

test: $(PROJECT_NAME).elf
	@./$(PROJECT_NAME).elf

clean:
	@rm -fv *.o

distclean: clean
	@rm -fv *.so *.a *.elf
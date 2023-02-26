
PROJECT_NAME = ntokenize

STATIC_LIB  = lib$(PROJECT_NAME).a
DYNAMIC_LIB  = lib$(PROJECT_NAME).so

HEADERS := $(shell find -name "*.hh" -type f)
SOURCES := $(shell find -name "*.cc" -type f)
OBJECTS := $(addsuffix .o, $(SOURCES))

CXXFLAGS := -pipe -O2 -fPIC

PROGRAM = main

all: $(STATIC_LIB) $(DYNAMIC_LIB)

%.cc.o: %.cc
	@echo "  COMPILE $^ -> $@"
	@$(CXX) -c $(CXXFLAGS) -o $@ $^

$(STATIC_LIB): tokenize.cc.o $(HEADERS)
	@echo "  LINK $^ -> $@"
	@$(AR) mcs $@ $<

$(DYNAMIC_LIB): tokenize.cc.o $(HEADERS)
	@echo "  LINK $^ -> $@"
	@$(CXX) $(CXXFLAGS) -shared -o $@ $<

$(PROJECT_NAME).elf: main.cc.o $(STATIC_LIB)
	@echo "  LINK $^ -> $@"
	@$(CXX) $(CXXFLAGS) -o $@ $^

test: $(PROJECT_NAME).elf
	@./$(PROJECT_NAME).elf

clean:
	@rm -fv *.o

distclean: clean
	@rm -fv *.so *.a *.elf
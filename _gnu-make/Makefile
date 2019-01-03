.PHONY: build clean

# directories
ifeq ($(realpath .),)
  $(error your version of Make doesn't support $$(realpath names...) - please use GNU Make 3.81 or later)
endif

ifeq ($(platform),)
  __uname_s := $(shell sh -c 'uname -s 2>/dev/null | tr [A-Z] [a-z] || echo unknown-platform')
  __uname_m := $(shell sh -c 'uname -m 2>/dev/null | tr [A-Z] [a-z] || echo unknown-architecture')

  ifeq ($(__uname_s),linux)
    override platform := linux
    override architecture := $(__uname_m)
  endif
  ifeq ($(__uname_s),darwin)
    override platform := mac
    override architecture := $(__uname_m)
  endif
  ifeq ($(findstring mingw,$(__uname_s)),mingw)
    override platform := windows
    override architecture := $(if $(findstring MINGW32,$(MSYSTEM)),i686,$(if $(findstring MINGW64,$(MSYSTEM)),x86_64,))
    ifeq ($(CC),cc)
      override CC := gcc
    endif
  endif
  ifeq ($(__uname_s),freebsd)
    override platform := freebsd
    override architecture := $(__uname_m)
  endif
	ifeq ($(findstring cygwin,$(__uname_s)),cygwin)
		override platform := cygwin
		override architecture := $(__uname_m)
	endif
endif
ifeq ($(architecture),)
  override architecture := unknown-architecture
endif

prefix := $(realpath ..)
srcdir := $(realpath ../src)
exampledir := $(realpath ../example)
testdir := $(realpath ../test)
buildir := $(realpath .)/build
binsubdir := $(platform)-$(architecture)
bindir := $(prefix)/bin/$(binsubdir)

CFLAGS := -O2 -g -Wall -Wshadow -pedantic -Werror -std=c99
CXXFLAGS := -O2 -g -Wall -Wshadow -pedantic -Werror -std=c++11

ifeq ($(platform),android)
CFLAGS += -fpie -pie
CXXFLAGS += -fpie -pie
endif

build: $(bindir)/uuid4gen $(bindir)/uuid4gen++
ifneq ($(platform), $(findstring $(platform), android ios))
  build: $(bindir)/uuid4_practrand_test
endif
ifeq ($(shell printf "int main(int argc, char* argv[]) { return 0; }\n" | $(CC) -x c -ltestu01 -o /dev/null - 2> /dev/null && echo 'ok'),ok)
  build: $(bindir)/uuid4_testu01_test
endif

$(bindir)/uuid4gen: $(srcdir)/uuid4.c $(srcdir)/uuid4.h $(exampledir)/uuid4gen.c $(lastword $(MAKEFILE_LIST))
	mkdir -p $(@D)
	$(CC) -I $(srcdir) $(CPPFLAGS) $(CFLAGS) $(filter-out %Makefile,$(filter-out %.h,$^)) -o $@
	$(if $(postbuild),$(postbuild) $@)

$(bindir)/uuid4gen++: $(srcdir)/uuid4.c $(srcdir)/uuid4.h $(exampledir)/uuid4gen.cpp $(lastword $(MAKEFILE_LIST))
	mkdir -p $(@D)
	$(CXX) -x c++ -I $(srcdir) $(CPPFLAGS) $(CXXFLAGS) $(filter-out %Makefile,$(filter-out %.h,$^)) -o $@
	$(if $(postbuild),$(postbuild) $@)

$(bindir)/uuid4_practrand_test: $(srcdir)/uuid4.c $(srcdir)/uuid4.h $(lastword $(MAKEFILE_LIST))
	mkdir -p $(@D)
	$(CC) -I $(srcdir) -DUUID4_PRACTRAND_TEST $(CPPFLAGS) $(CFLAGS) $(filter-out %Makefile,$(filter-out %.h,$^)) -o $@
	$(if $(postbuild),$(postbuild) $@)

$(bindir)/uuid4_testu01_test: $(srcdir)/uuid4.c $(srcdir)/uuid4.h $(lastword $(MAKEFILE_LIST))
	mkdir -p $(@D)
	$(CC) -I $(srcdir) -DUUID4_TESTU01_TEST $(CPPFLAGS) $(CFLAGS) $(filter-out %Makefile,$(filter-out %.h,$^)) -ltestu01 -o $@
	$(if $(postbuild),$(postbuild) $@)

clean:
	rm -rf $(buildir)
	rm -rf $(bindir)

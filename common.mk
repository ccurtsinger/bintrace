INCLUDE_DIR = $(ROOT)/include
TESTS_DIR = $(ROOT)/tests
DIRS ?= 

SHLIB_SUFFIX = dylib

RECURSIVE_TARGETS ?= clean build

all: build

$(RECURSIVE_TARGETS)::
	@for dir in $(DIRS); do \
	  $(MAKE) -C $$dir $@; \
	done

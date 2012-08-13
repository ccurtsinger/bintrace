INCLUDE_DIR = $(ROOT)/include
TESTS_DIR = $(ROOT)/tests
DIRS ?= 

RECURSIVE_TARGETS = clean build

all: build

$(RECURSIVE_TARGETS)::
	for dir in $(DIRS); do \
	  $(MAKE) -C $$dir $@; \
	done
	
test::
	$(MAKE) -C $(TESTS_DIR) test

INCLUDE_PATHS += $(ROOT)/include $(ROOT)/gtest/include
TESTS_DIR = $(ROOT)/tests
DIRS ?= 

GTEST_VERSION=1.8.0
GTEST_SOURCE=https://github.com/google/googletest/archive/release-$(GTEST_VERSION).zip
GTEST_DIR=$(ROOT)/googletest-release-$(GTEST_VERSION)/googletest
GTEST_LIB=$(GTEST_DIR)/libgtest.a
GTEST_FLAGS=$(GTEST_LIB) -I$(GTEST_DIR)/include

INCLUDE_FLAGS = $(addprefix -I,$(INCLUDE_PATHS))
INCLUDE_FILES = $(ROOT)/include/bintrace.h $(wildcard $(ROOT)/include/bintrace/*.hpp)

SHLIB_SUFFIX = dylib

RECURSIVE_TARGETS ?= clean build

all: build

$(RECURSIVE_TARGETS)::
	@for dir in $(DIRS); do \
	  $(MAKE) -C $$dir $@; \
	done

$(ROOT)/release-$(GTEST_VERSION).zip:
	cd $(ROOT); wget $(GTEST_SOURCE)

$(GTEST_DIR): $(ROOT)/release-$(GTEST_VERSION).zip
	cd $(ROOT); unzip release-$(GTEST_VERSION).zip

$(GTEST_LIB): $(GTEST_DIR)
	cd $(GTEST_DIR); $(CXX) -Iinclude -I. -c src/gtest-all.cc; ar -rv libgtest.a gtest-all.o

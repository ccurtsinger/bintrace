ROOT = ../..
include $(ROOT)/common.mk

test: runner
	@./runner --gtest_output=xml

runner: runner.cpp $(INCLUDE_DIR)/bintrace/Driver.hpp
	@clang++ --std=c++0x -I$(INCLUDE_DIR) -o runner runner.cpp -ludis86 -lgtest -lpthread

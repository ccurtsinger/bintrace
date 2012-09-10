ROOT = ../..
include $(ROOT)/common.mk

test: runner
	@./runner --gtest_output=xml

runner: runner.cpp $(INCLUDE_DIR)/bintrace/TrieMap.hpp
	@clang++ -I$(INCLUDE_DIR) -o runner runner.cpp -lgtest -lpthread

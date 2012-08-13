ROOT = ../..
include $(ROOT)/common.mk

test: runner
	@./runner --gtest_output=xml

runner: runner.cpp
	@clang++ -I$(INCLUDE_DIR) -o runner runner.cpp -lgtest -lpthread

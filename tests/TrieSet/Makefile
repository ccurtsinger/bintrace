
test: runner
	@./runner --gtest_output=xml

runner: runner.cpp
	@clang++ -o runner runner.cpp -lgtest -lpthread

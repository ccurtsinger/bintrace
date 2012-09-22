#include <stdio.h>
#include <cstdlib>
#include <gtest/gtest.h>

#include "bintrace.h"

using namespace bintrace;

int foo() {
	int x = 10;
	for(int i=0; i<10; i++) {
		x++;
	}
	printf("Hello World %d\n", x);
	x--;
	return x;
}

TEST(DriverTest, Real) {
    Driver<ControlFlowTracer> d;
	d.execute(foo);
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

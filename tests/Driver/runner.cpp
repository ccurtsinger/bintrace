#include <stdio.h>
#include <cstdlib>
#include <signal.h>
#include <gtest/gtest.h>

#include "bintrace.h"

using namespace bintrace;

int x = 0;

class Incrementor {
public:
	void run(Interval<Incrementor>* i) {
		for(int j=0; j<10; j++) {
			i->next();
		}
		i->end();
		x++;
	}
};

TEST(DriverTest, Basic) {
	Driver<Incrementor> d;

	// Fill some memory with one-byte opcodes (int 3)
	uint8_t* bytes = new uint8_t[100];
	for(int i=0; i<100; i++) {
		bytes[i] = 0xCC;
	}

	d.run((intptr_t)&bytes[90]);
	EXPECT_EQ(1, x);

	d.run((intptr_t)&bytes[50]);
	EXPECT_EQ(2, x);

	d.run((intptr_t)&bytes[60]);
	EXPECT_EQ(3, x);

	d.run((intptr_t)&bytes[55]);
	EXPECT_EQ(3, x);

	d.run((intptr_t)&bytes[30]);
	EXPECT_EQ(4, x);

	d.run((intptr_t)&bytes[35]);
	EXPECT_EQ(4, x);
	
	d.run((intptr_t)&bytes[40]);
	EXPECT_EQ(5, x);

	delete bytes;
}

enum {
	End = 0,
	A = 1,
	B = 2,
	C = 4,
	D = 8,
	E = 16,
	F = 32,
	G = 64,
	H = 128
};

int fakeCFG[] = {
	B,		// A
	D | E,	// B
	G,		// C
	End,	// D
	A | F,	// E
	H,		// F
	End,	// G
	G 		// H
};

int visits[] = {0, 0, 0, 0, 0, 0, 0, 0};

class FakeCFGTracer {
public:
	void run(Interval<FakeCFGTracer>* interval) {
		int position = interval->position();
		visits[position]++;

		// Increment the current position without disassembling it
		interval->skip();

		int successors = fakeCFG[position];

		if(successors & A)
			interval->fork(0);

		if(successors & B)
			interval->fork(1);

		if(successors & C)
			interval->fork(2);

		if(successors & D)
			interval->fork(3);

		if(successors & E)
			interval->fork(4);

		if(successors & F)
			interval->fork(5);

		if(successors & G)
			interval->fork(6);

		if(successors & H)
			interval->fork(7);

		interval->end();
	}
};

TEST(DriverTest, FakeCFG) {
	// Run the driver over a fake CFG encoded in the fakeCFG array (adjacency list)
	Driver<FakeCFGTracer> d;
	d.run(0);

	EXPECT_EQ(1, visits[0]);
	EXPECT_EQ(1, visits[1]);
	EXPECT_EQ(0, visits[2]);
	EXPECT_EQ(1, visits[3]);
	EXPECT_EQ(1, visits[4]);
	EXPECT_EQ(1, visits[5]);
	EXPECT_EQ(1, visits[6]);
	EXPECT_EQ(1, visits[7]);
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	
	return 0;
}

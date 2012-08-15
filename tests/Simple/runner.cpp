#include <stdio.h>
#include <udis86.h>
#include <bintrace.h>

#include <gtest/gtest.h>

using namespace bintrace;

void foo(int x) {
	int y = x/3;
	int z = y*10;
	printf("Hello call instruction\n");
}

struct CallMatcher {
	static bool reachedCall;
	
	static bool match(ud_t* ud) {
		return ud->mnemonic == UD_Icall;
	}
	
	static void onMatch(SequenceControl* seq, ud_t* ud) {
		reachedCall = true;
	}
};

bool CallMatcher::reachedCall = false;

TEST(SimpleTest, ReachedCallInst) {
	EXPECT_TRUE(CallMatcher::reachedCall);
}

int main(int argc, char** argv) {
	auto s = new Sequence<CallMatcher>((void*)foo);
	s->disassemble();
	
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	
	return 0;
}

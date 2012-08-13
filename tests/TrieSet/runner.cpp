#include <cstdlib>
#include "TrieSet.hpp"

#include <gtest/gtest.h>

using namespace std;

enum { Items = 10000 };

class TrieSetTest : public testing::Test {
protected:
	TrieSet<int> set;
	int contents[Items];
	
	virtual void SetUp() {
		// Add random elements to the TrieSet and an array
		for(size_t i=0; i<Items; i++) {
			int x = rand();
			set.add(x);
			contents[i] = x;
		}
	}
};

// Make sure everything in the array is also in the set
TEST_F(TrieSetTest, ContainsTest) {
	for(size_t i=0; i<Items; i++) {
		EXPECT_TRUE(set.lookup(contents[i]));
	}
}

// Make sure things that aren't in the array are also not in the set
TEST_F(TrieSetTest, NotContainsTest) {
	size_t count = 0;
	while(count < Items) {
		int x = rand();
		bool found = false;
		for(size_t i=0; i<Items && !found; i++) {
			if(contents[i] == x) {
				found = true;
			}
		}
		
		if(!found) {
			EXPECT_FALSE(set.lookup(x));
			count++;
		}
	}
}

// Make sure the next method always returns the next-largest entry
TEST_F(TrieSetTest, NextTest) {
	for(size_t i=0; i<Items; i++) {
		int x = rand();
		
		int min_next = 0;
		for(size_t j=0; j<Items; j++) {
			if(contents[j] >= x && (contents[j] < min_next || min_next == 0)) {
				min_next = contents[j];
			}
		}
		
		EXPECT_EQ(set.next(x), min_next);
	}
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	
	return 0;
}

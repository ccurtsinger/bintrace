#include <cstdlib>
#include <gtest/gtest.h>

#include "bintrace.h"

using namespace bintrace;

enum { Items = 10000 };

class Element {
public:
	bool value;
	Element(bool value) {
		this->value = value;
	}
};

class TrieMapTest : public testing::Test {
protected:
	TrieMap<int, Element> set;
	int contents[Items];
	
	virtual void SetUp() {
		// Add random elements to the TrieMap and an array
		for(size_t i=0; i<Items; i++) {
			int x = rand();
			set.add(x, new Element(true));
			contents[i] = x;
		}
	}
};

// Make sure everything in the array is also in the set
TEST_F(TrieMapTest, ContainsTest) {
	for(size_t i=0; i<Items; i++) {
		EXPECT_TRUE(set.lookup(contents[i])->value);
	}
}

// Make sure things that aren't in the array are also not in the set
TEST_F(TrieMapTest, NotContainsTest) {
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
			EXPECT_EQ(NULL, set.lookup(x));
			count++;
		}
	}
}

int main(int argc, char** argv) {
	srand(time(NULL));
	
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	
	return 0;
}

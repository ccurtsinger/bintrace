#include <gtest/gtest.h>

class HelloTest : public testing::Test {
protected:
	virtual void SetUp() {
		
	}
	
	virtual void TearDown() {
		
	}	
};

TEST_F(HelloTest, TestA) {
	EXPECT_TRUE(true);
}

TEST_F(HelloTest, TestB) {
	EXPECT_TRUE(false);
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	
	return 0;
}

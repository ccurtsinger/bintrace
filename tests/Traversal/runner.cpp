#include <map>
#include <gtest/gtest.h>
#include <bintrace.h>

using namespace std;
using namespace bintrace;

TEST(TraversalTest, Simple) {
    int visits[100];

    for(int i=0; i<100; i++) {
        visits[i] = 0;
    }
    
    Traversal<Interval> t(10);

    while(!t.done()) {
        auto i = t.next();
        
        while(i != NULL && !i->done()) {
            uintptr_t x = i->next();
            visits[x]++;
            
            switch(x) {
                case 6:
                    i->fork(42);
                    break;
                case 15:
                    i->fork(5);
                    break;
                case 19:
                    i->end();
                    break;
                case 50:
                    i->fork(80);
                    break;
                case 60:
                    i->end();
                    break;
                case 90:
                    i->end();
                    break;
                default:
                    break;
            }
        }
    }

    for(int i=0; i<5; i++) {
        EXPECT_EQ(visits[i], 0);
    }

    for(int i=5; i<20; i++) {
        EXPECT_EQ(visits[i], 1);
    }

    for(int i=20; i<42; i++) {
        EXPECT_EQ(visits[i], 0);
    }

    for(int i=42; i<61; i++) {
        EXPECT_EQ(visits[i], 1);
    }

    for(int i=61; i<80; i++) {
        EXPECT_EQ(visits[i], 0);
    }

    for(int i=80; i<91; i++) {
        EXPECT_EQ(visits[i], 1);
    }

    for(int i=91; i<100; i++) {
        EXPECT_EQ(visits[i], 0);
    }
}

int main(int argc, char** argv) {
    srand(time(NULL));
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#include <iostream>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/XmlOutputter.h>

using namespace std;
using namespace CPPUNIT_NS;

class HelloTest : public TestFixture {
	CPPUNIT_TEST_SUITE(HelloTest);
	CPPUNIT_TEST(testA);
	CPPUNIT_TEST(testB);
	CPPUNIT_TEST_SUITE_END ();

public:
	void setUp() {
		
	}
	
	void tearDown() {
		
	}
	
	void testA() {
		CPPUNIT_ASSERT(true);
	}
	
	void testB() {
		CPPUNIT_ASSERT(false);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(HelloTest);

int main(int argc, char** argv) {
	TestResult result;
	
	TestResultCollector collector;
	result.addListener(&collector);
	
	BriefTestProgressListener progress;
	result.addListener(&progress);
	
	TestRunner runner;
	runner.addTest(TestFactoryRegistry::getRegistry().makeTest());
	runner.run(result);
	
	ofstream outfile("results.xml");
	XmlOutputter output(&collector, outfile);
	output.write();
	outfile.close();
	
	//CompilerOutputter output(&collector, cerr);
	//output.write();
	
	return 0;
}

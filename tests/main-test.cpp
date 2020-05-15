#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/XmlOutputter.h>


#include "main-test.h"

using namespace std;

static void ensureResultsDirectory();

const string RESULTS_DIR = "./cppunit-result";

/**
 * This main can be used to run all sorts of tests. We can link this in multiple ways.
 *
 * Link with just one or a few other .o files, and you get a binary that tests just those classes.
 *
 * Link it with a bunch, and you get a binary that handles suites of testing.
 *
 * It's magic.
 */
int main( int argc, char **argv)
{
    //==================================================
    // Prepare things.
    //==================================================
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
    runner.addTest( registry.makeTest() );

    //==================================================
    // If there are any args, then we're going to
    // just assume we're being asked to dump to xml.
    //==================================================
    if (argc == 1) {
        runner.run();
    }

    else {
        CppUnit::TestResult testResult;
        CppUnit::TestResultCollector resultCollector;
        CppUnit::BriefTestProgressListener progressListener;

        testResult.addListener(&resultCollector);
        testResult.addListener(&progressListener);

        runner.run(testResult);

        ensureResultsDirectory();
        ofstream xmlFileOut(RESULTS_DIR + "/" + TEST_NAME + ".xml");
        CppUnit::XmlOutputter xmlOut(&resultCollector, xmlFileOut);
        xmlOut.write();

        return resultCollector.testFailures() == 0 ? 0 : 1;
    }
}

void ensureResultsDirectory() {
    struct stat info;
    if (stat(RESULTS_DIR.c_str(), &info) != 0) {
        // Does not exist.
        mkdir(RESULTS_DIR.c_str(), 0755);
    }
}

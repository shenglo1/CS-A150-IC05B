/**
 *  @author Stephen Gilbert
 *  @file main.cpp
 *  @version CS 150 In-class exercise
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
using namespace std;

#include "cs150check.h"
#include "fliplines.h"

vector<string> runTest(const string& fname, ostream& out)
{
    ostringstream strOut;
    toggleOut(strOut, out);
    flipLines(fname);
    toggleOut(strOut, out);
    return strToVector(strOut.str());
}
/**
 * Run your program's tests
 */
void runTests()
{
    
    ///////////// Begin a set of tests
    beginTests(); // test heading

    /////// Tests for //////////////////////
    beginFunctionTest("flipLines(\"easy.txt\")");
    vector<string> result = runTest("easy.txt", cout);
    if (result.size() < 1) failMsg("Checking line #1. Missing");
    else assertEqualsMsg("Checking line #1", "second line - should now be first", result.at(0));
    
    if (result.size() < 2) failMsg("Checking line #2. Missing");
    else assertEqualsMsg("Checking line #2", "first line - should now be second", result.at(1));
    
    endFunctionTest();

    beginFunctionTest("flipLines(\"nolo.txt\")");
    result = runTest("nolo.txt", cerr);
    if (result.size() < 1) failMsg("Checking error message. Missing");
    else assertEqualsMsg("Checking error message", "Cannot open nolo.txt", result.at(0));
    
    endFunctionTest();
    
    beginFunctionTest("flipLines(\"jabberwock.txt\")");
    result = runTest("jabberwock.txt", cout);
    if (result.size() != 9) 
        failMsg("Wrong number of lines in output");
    else
    {
        assertEqualsMsg("Checking line #1", "did gyre and gimble in the wabe.", result.at(0));
        assertEqualsMsg("Checking line #2", "Twas brillig and the slithy toves", result.at(1));
        assertEqualsMsg("Checking line #5", "\"Beware the Jabberwock, my son,", result.at(4));
        assertEqualsMsg("Checking line #6", "", result.at(5));
        assertEqualsMsg("Checking line #8", "the jaws that bite, the claws that catch,", result.at(7));
        assertEqualsMsg("Checking line #9", "the frumious bandersnatch.\"", result.at(8));
        
    }
    
    endFunctionTest();
    
    endTests();
}


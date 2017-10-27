
/**
 * Basic unit tests for CS 150
 * @author Steve G.
 * @version Spring 2015. (No encoded result code)
 * This is the implementation file.
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

#include "cs150check.h"

/**
 * Global variables for scoring points.
 */
int possible = 0;
int fail = 0;
static const string UNDERLINE(70,'-');

static int allPossible = 0;
static int allFail = 0;

void _failReportDifference(const string& msg, double expected, double tolerance, double diff)
{
	ios::fmtflags f(cerr.flags());
	cerr.setf(ios::fixed);
	cerr.precision(4);
	cerr << "   X " << msg << ": expected [" << expected;;
	cerr.setf(ios::scientific);
	cerr << "] within tolerance [" << tolerance;
	cerr << "] but answer off by [" << diff;
	cerr << "]" << endl;
	cerr.flags(f);
	fail++;
}

void _successReport(const string& msg)
{
    cerr << "   + " << msg << endl;
}

void _failReport(const string& msg)
{
	cerr << "   X " << msg << endl;
	fail++;
}

void failMsg(const string& msg)
{
    possible++;
    _failReport(msg);
}

void passMsg(const string& msg) {
    possible++;
    _successReport(msg);
}

//////////// OVERLOADED VERSION OF ASSERT_EQUALS ///////////////////////
void _assertEquals(const string& msg, const string& expected, const string& actual)
{
    possible++;
    if (expected != actual)
    {
    	_failReportEquals(msg, expected, actual);
    }
    else
    	_successReport(msg + "->" + actual);
}

void _assertEquals(const string& msg, int expected, int actual)
{
    possible++;
    if (expected != actual)
    {
    	_failReportEquals(msg, expected, actual);
    }
    else
    	_successReport(msg);
}

void _assertEquals(const string&, double, double)
{
	cerr << "XXX DO NOT USE assertEquals(double, double)" << endl;
	cerr << "      USE assertDoubleEquals(double expect, double actual, double tolerance) instead." << endl;
}
void _assertEquals(const string& msg, double expected, double actual, double tolerance)
{
	_assertEquals("", msg, expected, actual, tolerance);
}

void _assertEquals(const string& xmsg, const string& msg, double expected, double actual, double tolerance)
{
    possible++;
    double diff = abs(actual - expected);
    if (diff <= tolerance)
    {
    	_successReport(xmsg + "; " + msg);
    }
    else
    {
    	_failReportDifference(xmsg + ", " + msg, expected, tolerance, diff);
    }
}

void _assertTrue(bool cond, const string& msg)
{
    possible++;
    if (!cond)
    {
    	_failReport(msg + " should be true, but is false.");
    }
    else
    	_successReport(msg);
}

void _assertFalse(bool cond, const string& msg)
{
    possible++;
    if (cond)
    {
    	_failReport(msg + " should be false, but is true.");
    }
    else
    	_successReport(msg);
}

void beginTests()
{
    cerr << "TESTING " << ASSIGNMENT << "--" << STUDENT << endl;
    cerr << UNDERLINE << endl;
    allPossible = allFail = 0;
}

void beginFunctionTest(const string& functionName)
{
	possible = fail = 0;
    cerr << "Checking function: " << functionName << " -------------------" << endl;
}

void endFunctionTest()
{
    cerr << UNDERLINE << endl << "  Tests passing "
        << (possible - fail) << "/" << possible
        << " ("
        << fixed << setprecision(0)
        << (static_cast<double>(possible - fail) / possible) * 100.0
        << "%)." << endl << endl;

    allPossible += possible;
    allFail += fail;
}


void endTests()
{
	double percent = (static_cast<double>(allPossible - allFail) / allPossible) * 100.0;
    cerr << UNDERLINE << endl << ASSIGNMENT << ":" << STUDENT << ":ALL TESTS -- PASS "
        << (allPossible - allFail) << "/" << allPossible
        << " ("
        << fixed << setprecision(0)
        << percent
        << "%)." << endl << UNDERLINE << endl;
}

//// Code from cs150io.hxx
void replaceAll(string& str, const std::string& from, const std::string& to)
{
    if(from.empty()) return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

int runIOTests(const string& testFile)
{
    beginTests();
    ifstream in;
    in.open(testFile.c_str());
    if (! in)
    {
        cerr << "Cannot find \"" << testFile << "\" with your input and output." << endl;
        return -1;
    }

    int result = 0;
    string line;
    while (getline(in, line))
    {
        string::size_type mid = line.find('|');
        if (mid == string::npos)
        {
            cerr << "Test file is not properly formed. No tests run." << endl;
            return -1;
        }
        string input = line.substr(0, mid);
        replaceAll(input, "\\n", "\n");
        string expected = line.substr(mid + 1);
        replaceAll(expected, "\\n", "\n");

        ostringstream sout;
        istringstream sin(input);

        try
        {
        	streambuf* oldIn = cin.rdbuf();
        	streambuf* oldOut = cout.rdbuf();
        	cin.rdbuf(sin.rdbuf());
        	cout.rdbuf(sout.rdbuf());
            result = run();
            cin.rdbuf(oldIn);
            cout.rdbuf(oldOut);
        }
        catch (exception& e)
        {
            cerr << " X CRASH for input " << input << ": " << e.what() << endl;
            possible++;
            fail++;
            continue;
        }

        string actual = sout.str();
        string::size_type beg = actual.find('[');
        string::size_type end = actual.find(']');

        if (beg == string::npos || end == string::npos || beg >= end)
        {
            cerr << "Test not properly formed on line: " << line << "; Tests cancelled." << endl;
            return -1;
        }
        else
        {
            actual = actual.substr(beg + 1, end - beg - 1);
        }

        assertEqualsMsg("Input of " + input, expected, actual);
    }
    allPossible = possible;
    allFail = fail;

    endTests();

    return result;
}

int ARGC = 0;
char ** ARGV = 0;

/**
 * Main file for all testing and regular running.
 * @param argc
 * @param argv
 * @return
 */
int main(int, char **)
{
	runTests();
	return 0;
}

int run()
{
    // Add your code here

    return 0;
}

string fileToString(const string& fname)
{
    ifstream in(fname.c_str());
    ostringstream out;
    char ch;
    while (in.get(ch)) out.put(ch);
    return out.str();
}

vector<string> strToVector(const string& str)
{
    istringstream in(str);
    vector<string> result;
    string line;
    while (getline(in, line)) result.push_back(line);
    return result;
}

void toggleOut(ostringstream& out, ostream& sysout)
{
    static streambuf * oldOut = nullptr;
    if (oldOut)
    {
        sysout.rdbuf(oldOut);
        oldOut = nullptr;
    }
    else
    {
        oldOut = sysout.rdbuf();
        sysout.rdbuf(out.rdbuf());
    }
}


string TESTFILE = "";
string ASSIGNMENT = "IC05B-A";

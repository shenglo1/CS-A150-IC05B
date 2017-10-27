#include <iostream>
#include <fstream>
#include <string>

using namespace std;
string STUDENT = "loginID"; // Add your id as usual.

#include "fliplines.h"

void flipLines(const string& fname)
{
    ifstream in(fname);
    if (in.fail())
    {
        cerr << "Cannot open " << fname << endl;
        return;
    }
    
    string first, second;
    while (getline(in, first))
    {
        if (getline(in, second))
        {
            cout << second << endl;
            cout << first << endl;
        }
        else
        {
            cout << first << endl;
        }
    }
}

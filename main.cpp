#include <iostream>
#include "Scan.h"
#include "Source.h"

using namespace std;

int main(int argc, char* argv[])
{
    Source *source = new Source("/home/szymon/Desktop/CPP/2018-04-18-04/inputFiles/main.txt");
    Scan scan(*source);

    SymType sym = mainsy;

    while(sym != 37)
    {
        sym = scan.NextSymbol();
        switch(sym)
        {
            case mainsy:        cout << "mainsy"       << endl; break; // 0
            case functionsy:    cout << "functionsy"   << endl; break; // 1
            case varsy:         cout << "varsy"        << endl; break; // 2
            case currencyconst: cout << "currencyconst"<< endl; break; // 3
            case returnsy:      cout << "returnsy"     << endl; break; // 4
            case whilesy:       cout << "whilesy"      << endl; break; // 5
            case breaksy:       cout << "breaksy"      << endl; break; // 6
            case continuesy:    cout << "continuesy"   << endl; break; // 7
            case ifsy:          cout << "ifsy"         << endl; break; // 8
            case elsesy:        cout << "elsesy"       << endl; break; // 9
            case publicsy:      cout << "publicsy"     << endl; break; // 10
            case privatesy:     cout << "privatesy"    << endl; break; // 11
            case ident:         cout << "idensy"       << endl; break; // 12
            case varconst:      cout << "varconst"     << endl; break; // 13
            case times:         cout << "times"        << endl; break; // 14
            case divop:         cout << "divop"        << endl; break; // 15
            case plusop:        cout << "plusop"       << endl; break; // 16
            case minusop:       cout << "minusop"      << endl; break; // 17
            case ltop:          cout << "ltop"         << endl; break; // 18
            case leop:          cout << "leop"         << endl; break; // 19
            case gtop:          cout << "gtop"         << endl; break; // 20
            case geop:          cout << "geop"         << endl; break; // 21
            case neop:          cout << "neop"         << endl; break; // 22
            case eqop:          cout << "eqop"         << endl; break; // 23
            case lparent:       cout << "lparent"      << endl; break; // 24
            case rparent:       cout << "rparetn"      << endl; break; // 25
            case lbracket:      cout << "lbracket"     << endl; break; // 26
            case rbracket:      cout << "rbracket"     << endl; break; // 27
            case semicolon:     cout << "semicolon"    << endl; break; // 28
            case colon:         cout << "colon"        << endl; break; // 29
            case becomes:       cout << "becomes"      << endl; break; // 30
            case notop:         cout << "notop"        << endl; break; // 31
            case andop:         cout << "andop"        << endl; break; // 32
            case orop:          cout << "orop"         << endl; break; // 33
            case raccessop:     cout << "raccessop"    << endl; break; // 34
            case laccessop:     cout << "laccessop"    << endl; break; // 35
            case comma:         cout << "comma"        << endl; break; // 36
            case others:        cout << "others"       << endl; return 0; break; // 37
        }
    }
    scan.ScanError(1);
    return 0;
}

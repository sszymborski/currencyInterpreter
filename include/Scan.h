#ifndef SCAN_H
#define SCAN_H

#include <stdio.h>
#include <cstring>
#include <iostream>
#include <iomanip>
#include "Source.h"

#define MAXIDLEN 50
#define INT_MAX 1000000

enum SymType // Atomy leksykalne Mini Pascal'a
{
    mainsy, // 0
    functionsy, // 1
    varsy, // 2
    returnsy, // 3
    whilesy,  // 4
    breaksy,  // 5
    continuesy,  // 6
    ifsy, // 7
    elsesy, // 8
    publicsy, // 9
    privatesy, //10 // Keywords
    NKEYS, //
    MAXKEY=privatesy, //
    ident, // 11
    currencyconst, // 12
    varconst, //13
    times, // 14
    divop, // 15
    plusop, // 16
    minusop, // 17
    ltop, // 18
    leop, // 19
    gtop, // 20
    geop, // 21
    neop, // 22
    eqop, // 23
    lparent, // 24
    rparent, // 25
    lbracket, // 26
    rbracket, // 27
    semicolon, // 28
    colon, // 29
    becomes, // 30
    notop, // 31
    andop, // 32
    orop, // 33
    raccessop, // 34
    laccessop, // 35
    comma, // 36
    others, // 37
    MAXSYM=others+1 // 38
};

enum ScanErrors { INTCONST2BIG=1, IDENTIFIER2LONG};

class Scan
{
    enum { FirstLexErr = 0 };
    struct KeyRec   // Deskryptor slowa kluczowego;
    {
        const char *kw; // Slowo kluczowe
        SymType atom; // Odpowiadajacy mu atom
    };
    static KeyRec KT[NKEYS];// Keyword Table
    Source& src; // Strumien znaków
    int c; // Aktualny znak z src
    TextPos atompos; // Pozycja atomu w tekscie
    double varconstant; // Ostatnia stala
    double currencyconstant;
    char spell[MAXIDLEN+1];// Ostatni ident, przeliterowany
    void Nextc()
    {
        c=src.NextChar();
    }
    static unsigned hash(char *s, unsigned int len);
    // Funkcja mieszajaca dla KT
public:
    Scan(Source &s):src(s)
    {
        Nextc();
    }
    SymType NextSymbol();// Nastepny atom
    void ScanError(int ecode, const char *mtxt=0, const char *atxt=0);
    double VarConst()
    {
        return varconstant;
    }
    double CurrencyConst()
    {
        return currencyconstant;
    }
    const char* Spell()
    {
        return spell;
    }
};


#endif // SCAN_H

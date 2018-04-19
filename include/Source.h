#ifndef SOURCE_H
#define SOURCE_H

#include <stdio.h>
#include <cstring>
#include <iostream>
#include <iomanip>

#define MAXLIN 100

using namespace std;

extern int options;
struct TextPos
{
    int ln, cn; // Numer wiersza, znaku (od 1)
    TextPos(int l=0, int c=0): ln(l), cn(c) {}
};
class Source
{
    char *fn; // Nazwa pliku
    FILE *fp;
    TextPos tpos; // Biezaca pozycja w pliku
    int etotal, einline; // Liczniki bledów:
    char Line[MAXLIN+1]; // Bufor biezacego wiersza
    void PrntLine(); // Druk biezacego wiersza
    int NextLine(); // Nastepny wiersz do bufora
public:
    Source(const char *file);
    ~Source();
    void Error(int ec, const TextPos &tp, const char *mt, const char *at);
    int NextChar();
    const TextPos & GetPos() const
    {
        return tpos;
    }
    int getNumerOfErrors()
    {
        return etotal;
    }
};

#endif // SOURCE_H

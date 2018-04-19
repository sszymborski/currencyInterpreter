#include "Source.h"

Source::Source(const char *file)
{
    strcpy(fn = new char[strlen(file)+1], file);
    fp = fopen(fn, "r");
    if(!fp)
    {
        cout << "Waluty: BLAD FATALNY - nie mozna otworzyc pliku \"" << fn << "\"\n";
        exit(1);
    }
    cout << "\n Waluty, v.1.0, (c) 2018 (PW)\n";
    cout << "Raport kompilacji dla pliku: \"" << fn << "\"\n\n";
    etotal = einline = 0;
}

Source::~Source()
{
    cout << "\nWaluty: koniec raportu. \nWykrytych bledow: " << etotal << '\n';
    fclose(fp);
    delete [] fn;
}

void Source::Error(int ec, const TextPos &tp, const char *mt = "", const char *at = "") // error code, textpos, message (dwie - obie opcjonalne, domyslnie puste)
{
    etotal++;
    cout << setw(5) << "Blad w wierszu " << tpos.ln << " :" << Line;
    cout << setw(tpos.cn) << "^" << endl;
    einline = 1;
    cout << "Kod bledu:" << setw(2) << ec << "*** ";
    cout << setw(tp.cn) << setfill('-') << setfill(' ') << mt << at << '\n';
}

int Source::NextChar()
{
    int r = 1;
    if(tpos.ln == 0)          // jesli zadna linia nie byla brana z pliku to wez nowa linie (piersza)
        r = NextLine();
    else if(!Line[tpos.cn]) // jesli to byl ostatni znak z linni to wez nowa liniê
        r = NextLine();
    if(r)                   // jesli r = 0 tzn. nie ma juz nowych linii,  wez nastepny znak z tej linii
        return Line[tpos.cn++];
    else
        return EOF;
}

int Source::NextLine()
{
    if(!fgets(Line, MAXLIN, fp))    // jesli ostatnia brana linia to zwroc 0 (nie ma juz lini)
        return 0; // EOF
    tpos.ln++; // Nastepny wiersz,
    tpos.cn = 0; // Ustaw pozycje na przed pierwszym znakiem (jeszcze go nie pobrano)
    while(Line[tpos.cn] == ' ')       // jesli jest jakas spacja to dodaj pozycje
        tpos.cn++;
    //if((options&NOLIST)==0 )    // wypisz wiersz, jesli jest zaznaczona odpowiednia opcja kompilatora
    //PrntLine();
    einline = 0; // 0 bledow w nowym wierszu
    return 1;
}

#include "Scan.h"

typedef // Implementacja klasy Scan.
const char *AT[MAXSYM + 1];

Scan::KeyRec Scan::KT[NKEYS]=
{
    // Keyword Atom hash(keyword)
    //-------------------------------------------
    { "main", mainsy }, // 0
    { "func", functionsy }, // 1
    { "var", varsy }, // 2
    { "return", returnsy }, // 3
    { "while", whilesy }, // 4
    { "break", breaksy }, // 5
    { "continue", continuesy }, // 6
    { "if", ifsy }, // 7
    { "else", elsesy }, // 8
    { "public", publicsy }, // 9
    { "private", privatesy }, // 10

};

unsigned Scan::hash(char *s, unsigned int len)
{
    //
    // Funkcja okreslona eksperymentalnie: dla tabeli
    // NKEYS==18 elementowej jest 1 kolizja:
    // hash("not") == hash("else") == 17; brak kodu 0
    // Kolizje usunieto eksplicite.
    //
    unsigned h;
    if(strcmp(s, "main")==0)
        return 0;
    if(strcmp(s, "func")==0)
        return 1;
    if(strcmp(s, "var")==0)
        return 2;
    if(strcmp(s, "return")==0)
        return 3;
    if(strcmp(s, "while")==0)
        return 4;
    if(strcmp(s, "break")==0)
        return 5;
    if(strcmp(s, "continue")==0)
        return 6;
    if(strcmp(s, "if")==0)
        return 7;
    if(strcmp(s, "else")==0)
        return 8;
    if(strcmp(s, "public")==0)
        return 9;
    if(strcmp(s, "private")==0)
        return 10;

    h = (s[0]>>1) * s[1] * 1241;
    if(len>=3)
        h += s[len-1];
    return h % NKEYS;
}

SymType Scan::NextSymbol()  // Glowna usluga scanera
{
    do
    {
        while(isspace(c)) Nextc();// Pomin znaki biale
        if(c==EOF) return others;
        if(c=='#')  // komentarz w stylu #...#
        {
            do Nextc();
            while(c!='#');
            Nextc();
        }
        else if(c=='/')       // komentarz w stylu //
        {
            Nextc();
            if(c!='/') return divop;
            else do Nextc();
                while(c!='\n');
        }
    }
    while(isspace(c) || c=='#' || c=='/');

    atompos=src.GetPos();
    //---IDENTYFIKATOR LUB SlOWO KLUCZOWE
    if(isalpha(c))
    {
        unsigned int len=0, h;
        do   // pobieramy identyfikarot do tabeli spell
        {
            if(len<MAXIDLEN) spell[len++]=c;
            else ScanError(IDENTIFIER2LONG, "Error : Przekroczono maksymalna dlugosc identyfikatora");
            Nextc();
        }
        while(isalnum(c));
        spell[len]='\0';    // konczymy znakiem /0
        h = hash(spell,len);    // sprawdzamy czy jest to ident czy cos innego
        if(strcmp(KT[h].kw, spell) == 0)
            return KT[h].atom; // jesli jest to keyword to zwrcc to jakie
        else
            return ident;      // wpp jest to identyfikator
    }
    else      //---STALA CALKOWITA
    {
        if (isdigit(c))
        {
            bool big = false;
            bool current = true;
            long l = 0;
            do           // obliczamy jaka to liczba
            {
                l = l * 10 + (c - '0');
                if(l > INT_MAX || l < 0)
                {
                    big = true;
                    break;
                }
                Nextc();
            }
            while (isdigit(c));
            if(c == '.')
            {
                Nextc();
                double d = 0.0;
                int iter = 1;
                do           // obliczamy jaka to liczba
                {
                    d = d + (c - '0') / (10^iter);
                    if(iter>2)
                    {
                        current = false;
                    }
                    if(iter>8)
                    {
                        big = true;
                        break;
                    }
                    Nextc();
                    ++iter;
                }
                while (isdigit(c));
                d = d + l;
                if(current)
                    currencyconstant = d;
                else
                    varconstant = d;
                if (big == true)
                    ScanError(INTCONST2BIG, "Error : Przekroczono zakres var!");
                if(current)
                    return currencyconst;
                return varconst;
            }
            else
            {
                currencyconstant = (double) l;
                if (big == true)
                    ScanError(INTCONST2BIG, "Error : Przekroczono zakres var!");
                return currencyconst;
            }
        }
        else
        {
            // cd3 NextSymbol() ---Pozostale atomy
            switch (c)
            {
            //----Operatory 2 i 1 znakowe
            case ':':
                Nextc();
                if (c == '=')
                {
                    Nextc();
                    return becomes;
                }
                else return colon;
            case '<':
                Nextc();
                if (c == '=')
                {
                    Nextc();
                    return leop;
                }
                else return ltop;
            case '>':
                Nextc();
                if (c == '=')
                {
                    Nextc();
                    return geop;
                }
                else return gtop;
            case '!':
                Nextc();
                if (c == '=')
                {
                    Nextc();
                    return neop;
                }
                else return notop;                    //----Operatory 1 znakowe
            case '+':
                Nextc();
                return plusop;
            case '-':
                Nextc();
                return minusop;
            case '*':
                Nextc();
                return times;
            case '=':
                Nextc();
                return eqop;
            case '/':
                Nextc();
                return divop;
            case '(':
                Nextc();
                return lparent;
            case ')':
                Nextc();
                return rparent;
            case '{':
                Nextc();
                return lbracket;
            case '}':
                Nextc();
                return raccessop;
            case '[':
                Nextc();
                return laccessop;
            case ']':
                Nextc();
                return rbracket;
            case ',':
                Nextc();
                return comma;
            case ';':
                Nextc();
                return semicolon;
            case '&':
                Nextc();
                return andop;
            case '|':
                Nextc();
                return orop;
            default :
                Nextc();
                return others;
            }
        }
    }
}
void Scan::ScanError(int ecode, const char *mt, const char *at)
{
    src.Error(ecode, atompos, mt, at);
}

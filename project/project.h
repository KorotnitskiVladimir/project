#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <Windows.h>
using namespace std;

const char eng[] = "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ";
const char ru[] = "аАбБвВгГдДеЕёЁжЖзЗиИйЙкКлЛмМнНоОпПрРсСтТуУфФхХцЦчЧшШщЩъЪыЫьЬэЭюЮяЯ";
const char dig[] = "0123456789";
const char sign[] = "!,.;-?:";
bool setEng = false;
bool setRu = false;
bool setDig = false;
bool setSing = false;
int* engInd = nullptr;
char* engChars = nullptr;
int* ruInd = nullptr;
char* ruChars = nullptr;
int* digInd = nullptr;
char* digs = nullptr;
int* signInd = nullptr;
char* signs = nullptr;

void getStr(char** s)
{
    char buff[255];
    cout << "enter text" << endl;
    gets_s(buff);
    *s = new char[strlen(buff)+1];
    strcpy_s(*s, strlen(buff)+1, buff);
}

//функция подсчитывает места входа нужного фильтира в строку и запоминает в массивы индексы входа и значения фильтра
void countChars(char** s, const char* a, int** arr, char** b)
{
    if (*s!=nullptr)
    {
        int c = 0;
        for (int i=0; i<strlen(*s); i++)
            for (int j=0; j<strlen(a); j++)
                if ((*s)[i]==a[j])
                    c++;
        *arr = new int[c];
        *b = new char[c];
        int k = 0;
        for (int i=0; i<strlen(*s); i++)
            for (int j=0; j<strlen(a); j++)
                if ((*s)[i]==a[j])
                {
                    (*arr)[k] = i;
                    (*b)[k] = (*s)[i];
                    k++;
                }
    }
}
//установка фильтра
void setFilter(char** s, const char* a, bool &b)
{
    if (*s!=nullptr)
    {
        char* t = new char[strlen(*s)+1];
        for (int i=0; i<strlen(*s); i++)
        {
            int c = 0;
            for (int j=0; j<strlen(a); j++)
                if ((*s)[i]!=a[j])
                    c++;
            if (c==strlen(a))
                t[i] = (*s)[i];
            else
                t[i] = ' ';
        }
        t[strlen(*s)] = '\0';
        delete *s;
        *s = t;
        b = true;
    }
}
//возврат значений без фильтра, используя массивы, полученные благодаря функции CountChars()
void removeFilter(char** s, int** arr, char** a, bool &b)
{
    if (*s!=nullptr)
    {
        char* t = new char[strlen(*s)+1];
        int i=0, j=0;
        while (i<strlen(*s))
        {
            if (i==(*arr)[j])
            {
                t[i] = (*a)[j];
                i++;
                j++;
            }
            else
            {
                t[i] = (*s)[i];
                i++;
            }
        }
        t[strlen(*s)] = '\0';
        delete *s;
        *s = t;
        b = false;
    }
}
//освобождение памяти
void removeTrash(int** e, char** en, int** r, char** rus, int** d, char** di, int** s, char** si)
{
    if (*e!=nullptr)
        delete [] *e;
    if (*en!=nullptr)
        delete [] *en;
    if (*r!=nullptr)
        delete [] *r;
    if (*rus!=nullptr)
        delete [] *rus;
    if (*d!=nullptr)
        delete [] *d;
    if (*di!=nullptr)
        delete [] *di;
    if (*s!=nullptr)
        delete [] *s;
    if (*si!=nullptr)
        delete [] *si;
}

void filter()
{
    char* s = nullptr;
    getStr(&s);
    countChars(&s, eng, &engInd, &engChars);
    countChars(&s, ru, &ruInd, &ruChars);
    countChars(&s, dig, &digInd, &digs);
    countChars(&s, sign, &signInd, &signs);
    int c=0;
    while (c!=9)
    {
        cout << "Welcome to text filter programm. It allows to place filters on text input. Second use of same filter"
                " will remove it. Press: " << endl << "1 - hide latinic alphabet signs;" << endl << "2 - hide cyrillic"
                " alphabet signs;" << endl << "3 - hide digits;" << endl << "4 - hide punctuation signs;" << endl <<
                "5 - show filtered text in console;" << endl << "9 - exit programm;" << endl;
        cin >> c;
        switch (c)
        {
        case 1:
            if (setEng==false)
                setFilter(&s, eng, setEng);
            else
                removeFilter(&s, &engInd, &engChars, setEng);
            break;
        case 2:
            if (setRu==false)
                setFilter(&s, ru, setRu);
            else
                removeFilter(&s, &ruInd, &ruChars, setRu);
            break;
        case 3:
            if (setDig==false)
                setFilter(&s, dig, setDig);
            else
                removeFilter(&s, &digInd, &digs, setDig);
            break;
        case 4:
            if (setSing==false)
                setFilter(&s, sign, setSing);
            else
                removeFilter(&s, &signInd, &signs, setSing);
            break;
        case 5:
            puts(s);
            break;
        case 9:
            cout << "Thank you for using this programm. Have a nice day" << endl;
            break;
        default:
            cout << "wrong input" << endl;
        }
    }
    removeTrash(&engInd, &engChars, &ruInd, &ruChars, &digInd, &digs, &signInd, &signs);
    delete[] s;
}


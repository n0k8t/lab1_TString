#include "TString.h"

//dctor
TString::~TString()
{
    delete[] Data;
}

//ctor
TString::TString()
{
    Data = new char[1];
    Data[0] = '\0';
}

// copy ctor
TString::TString(const TString& rhs)
{
    int len = 0;
    while(rhs.Data[len]!= '\0') len++;

    Data = new char[len+1];
    for (int i = 0; i <= len; i++) Data[i] = rhs.Data[i];
}

//user ctor
TString::TString(const char * data)
{
    int len = 0;
    while(data[len]!= '\0') len++;

    Data = new char[len+1];
    for (int i = 0; i <len; i++) Data[i] = data[i];
}

TString& TString::operator =(const TString& rhs)
{
    if (Data == rhs.Data) return *this;

    int len = 0;
    while (rhs.Data[len] != '\0') len++;

    delete[] Data;
    Data = new char[len + 1];
    for (int i = 0; i < len; i++) Data[i] = rhs.Data[i];
    Data[len+1] = '\0';

    return *this;
}

TString& TString::operator +=(const TString& rhs)
{
    int len1 = 0, len2 = 0;
    while(Data[len1] != '\0') len1++;
    while(rhs.Data[len2] != '\0') len2++;

    int len_m = len1 + len2;

    char *str = new char[len1];
    for (int i = 0; i < len1 + 1; i++) str[i] = Data[i];

    delete[] Data;
    Data = new char[len_m + 1];

    int j = 0;
    for (int i = 0; i < len_m; i++)
    {
        if (i < len1)
            Data[i] = str[i];
        else
        {
            Data[i] = rhs.Data[j];
            j++;
        }
    }
    Data[len_m + 1] = '\0';

    return *this;
}

bool TString::operator ==(const TString& rhs) const
{
    if (Data[0] == '\0' && rhs.Data[0] != '\0') return false;

    int len1 = 0, len2 = 0;
    while (Data[len1] != '\0') len1++;
    while (rhs.Data[len2] != '\0') len2++;

    if (len1 != len2) return false;

    for (int i = 0; i < len1; i++)
    {
        if (Data[i] != rhs.Data[i]) return false;
    }

    return true;
}

bool TString::operator <(const TString& rhs) const
{
    int len1 = 0, len2 = 0;
    while (Data[len1] != '\0') len1++;
    while (rhs.Data[len2] != '\0') len2++;

    for (int i = 0; i < len1 + 1 && i < len2 + 1; i++)
    {
        if (Data[i] > rhs.Data[i])
        {
            return false;
        }
    }
    return true;
}

size_t TString::Find(const TString& substr) const
{
    int len1 = 0, len2 = 0;
    while (Data[len1] != '\0') len1++;
    while (substr.Data[len2] != '\0') len2++;

    if (len1 < len2) return (size_t)-1;

    int j = 0;
    for (int i = 0; i < len1; i++)
    {
        for (int k = 0; k < len2; k++)
        {
            if (Data[i + k] == substr.Data[k]) j++;
            else break;
        }
        if (j == len2) return (size_t) i;
    }

    return (size_t)-1;
}

size_t TString::Find(const char* substr) const
{
    int len1 = 0, len2 = 0;
    while (Data[len1] != '\0') len1++;
    while (substr[len2] != '\0') len2++;

    if (len1 < len2) return (size_t)-1;

    int j = 0;
    for (int i = 0; i < len1; i++)
    {
        for (int k = 0; k < len2; k++)
        {
            if(Data[i+k] == substr[k])
            {
                j++;
                if(j == len2) return (size_t)i;
            }
            else
                j = 0;
        }

    }

    return (size_t)-1;
}

void TString::Replace(char oldSymbol, char newSymbol)
{
    size_t len = 0;
    while (Data[len] != '\0') len++;

    for (int i = 0; i < len; i++)
    {
        if (Data[i] == oldSymbol) Data[i] = newSymbol;
    }
}

size_t TString::Size() const
{
    size_t len = 0;
    while (Data[len] != '\0') len++;
    return len;
}

bool TString::Empty() const
{
    return  Data[0] == '\0';
}

char TString::operator[](size_t index) const
{
    return Data[index];
}

char& TString::operator[](size_t index)
{
    return Data[index];
}

void TString::RTrim(char symbol)
{
    //длинна "Data"
    int len = 0;
    while (Data[len] != '\0') len++;

    //количество символов на удаление
    int k = 0;
    for (int i = len; i >=0; i--)
    {
        if(Data[i] == symbol) k++;
        else break;
    }
    if (k == 0) return;

    //создание нового массива в который пихаем элементы ДО удаленных
    TString newData = new char[len + 1 - k];
    for (int i = 0; i < len - k ; i++)
    {
        newData[i] = Data[i];
    }

    // создаем исправленный "Data"
    delete[] Data;
    Data = new char[len + 1 - k];
    for (int i = 0; i < len - k; i++)
    {
        Data[i] = newData[i];
    }
    Data[len + 1 - k] = '\0';
}

void TString::LTrim(char symbol)
{
    //длинна "Data"
    int len = 0;
    while (Data[len] != '\0') len++;

    //количество символов на удаление
    int k = 0;
    for (int i = 0; i < len; i++)
    {
        if(Data[i] == symbol) k++;
        else break;
    }
    if (k == 0) return;

    //создание нового массива в который пихаем элементы ПОСЛЕ удаленных
    TString newData = new char[len + 1 - k];
    for (int i = 0; i < len; i++)
    {
        newData[i] = Data[i + k];
    }

    // создаем исправленный "Data"
    delete[] Data;
    Data = new char[len + 1 - k];
    for (int i = 0; i <= len - k; i++)
    {
        Data[i] = newData[i];
    }
}

TString operator+(const TString & a, const TString & b)
{
    TString res;
    res = a;
    res += b;
    return res;
}

bool operator!=(const TString & a, const TString & b)
{
    return !(a == b);
}

bool operator>(const TString & a, const TString & b)
{
    return (!(a == b) && !(a < b));
}

std::ostream & operator<<(std::ostream &out, const TString &str)
{
    out << str.Data;
    return out;
}
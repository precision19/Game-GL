#include "stdafx.h"
#include "Helper.h"

string Helper::StringConvert(char* a)
{
    string str = "";
    for (int i = 0; i < 255; i++) 
    {
        str += a[i];
        if (a[i] == '\0')
            return str;
    }
    return str;
}

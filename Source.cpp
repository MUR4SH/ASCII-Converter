#using <system.drawing.dll>
#include <iostream>
#include <Windows.h>

using namespace System;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;

int main()
{
    Image^ img = Image::FromFile("sample.png"); //Открываем
    char *asc_img = new char[img->Width*img->Height]; //Массив одномерный с x*y элементами
    
    return 0;
}
#include <iostream>
using namespace std;

wstring tetmino[7];

int rotate(int px, int py, int r);

int main()
{
    std::cout << "Hello World!\n";
    //create assets
    tetmino[0].append(L"..X.");
    tetmino[0].append(L"..X.");
    tetmino[0].append(L"..X.");
    tetmino[0].append(L"..X.");

    tetmino[1].append(L"..X.");
    tetmino[1].append(L".XX.");
    tetmino[1].append(L".X..");
    tetmino[1].append(L"....");

    tetmino[2].append(L".X..");
    tetmino[2].append(L".XX.");
    tetmino[2].append(L"..X.");
    tetmino[2].append(L"....");

    tetmino[3].append(L"....");
    tetmino[3].append(L".XX.");
    tetmino[3].append(L".XX.");
    tetmino[3].append(L"....");

    tetmino[4].append(L"..X.");
    tetmino[4].append(L".XX.");
    tetmino[4].append(L"..X.");
    tetmino[4].append(L"....");

    tetmino[5].append(L"....");
    tetmino[5].append(L".XX.");
    tetmino[5].append(L"..X.");
    tetmino[5].append(L"..X.");

    tetmino[6].append(L"....");
    tetmino[6].append(L".XX.");
    tetmino[6].append(L".X..");
    tetmino[6].append(L".X..");


}

int rotate(int px, int py, int r)
{
    switch (r % 4)
    {
    case 0: return py * 4 + px; //0 degrees
    case 1: return 12 + py - (px*4); //90 degrees
    case 2: return 15 - (py * 4) - px; //180 degrees
    case 3: return 3 - py + (px * 4); //270 degrees
    }
    return 0;
}


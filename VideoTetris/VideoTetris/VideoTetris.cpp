#include <iostream>
using namespace std;

wstring tetmino[7];

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



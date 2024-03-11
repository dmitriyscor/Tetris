#include <iostream>
#include <windows.h>
#include <thread>
#include <stdio.h>
#include <vector>

using namespace std;

wstring tetmino[7];

int nFieldWidth = 12;
int nFieldHeight = 18;
unsigned char* pField = nullptr;

int nScreenWidth = 80;
int nScreenHeight = 30;

int rotate(int px, int py, int r);
bool doesPieceFit(int nTetromino, int nRotation, int nPosX, int nPosY);

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

    pField = new unsigned char[nFieldWidth * nFieldHeight]; // Create play field buffer
    for (int x = 0; x < nFieldWidth; x++) // Board Boundary
        for (int y = 0; y < nFieldHeight; y++)
            pField[y * nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? 9 : 0;

    wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
    for (int i = 0; i < nScreenWidth * nScreenHeight; i++) screen[i] = L' ';
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;

    //game logic and stuff
    bool bGameOver = false;

    int nCurrentPiece = 1;
    int nCurrentRotation = 0;
    int nCurrentX = nFieldWidth / 2, nCurrentY = 0; 

    bool bKey[4];
    bool bRotateHold = 0;

    int nSpeed = 20;
    int nSpeedCounter = 0;
    bool bForceDown = 0;
    int nPieceCount = 0;
    int nScore = 0;

    vector<int> vLines;

    while (!bGameOver)
    {
        //GAME TIMING =========================================
        this_thread::sleep_for(50ms);
        nSpeedCounter++;
        bForceDown = (nSpeedCounter == nSpeed);

        //INPUT ===============================================
        for (int k = 0; k < 4; k++) 
            bKey[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x28R"[k]))) != 0;
            //x27 = right arrow
            //x25 = left key
            //x28 = down jey
            //Z = z key
        
        // GAME LOGIC =========================================
        nCurrentX += (bKey[0] && doesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX + 1, nCurrentY)) ? 1 : 0; //left arrow was pressed 
        nCurrentX -= (bKey[1] && doesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX - 1, nCurrentY)) ? 1 : 0; //right arrow was pressed 
        nCurrentY += (bKey[2] && doesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1)) ? 1 : 0; //down arrow was pressed 

        if(bKey[3])
        {
            nCurrentRotation += (!bRotateHold && doesPieceFit(nCurrentPiece, nCurrentRotation + 1, nCurrentX, nCurrentY)) ? 1 : 0;
            bRotateHold = 1;
        }
        else
        {
            bRotateHold = 0;
        }

        if (bForceDown)
        {
            // Update difficulty every 50 pieces
            nSpeedCounter = 0;
            nPieceCount++;
            if (nPieceCount % 50 == 0)
                if (nSpeed >= 10) nSpeed--;

            // Test if piece can be moved down
            if (doesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1))
                nCurrentY++; // It can, so do it!
            else
            {
                // It can't! Lock the piece in place
                for (int px = 0; px < 4; px++)
                    for (int py = 0; py < 4; py++)
                        if (tetmino[nCurrentPiece][rotate(px, py, nCurrentRotation)] != L'.')
                            pField[(nCurrentY + py) * nFieldWidth + (nCurrentX + px)] = nCurrentPiece + 1;

                // Check for lines
                for (int py = 0; py < 4; py++)
                    if (nCurrentY + py < nFieldHeight - 1)
                    {
                        bool bLine = true;
                        for (int px = 1; px < nFieldWidth - 1; px++)
                            bLine &= (pField[(nCurrentY + py) * nFieldWidth + px]) != 0;

                        if (bLine)
                        {
                            // Remove Line, set to =
                            for (int px = 1; px < nFieldWidth - 1; px++)
                                pField[(nCurrentY + py) * nFieldWidth + px] = 8;
                            vLines.push_back(nCurrentY + py);
                        }
                    }

                nScore += 25;
                if (!vLines.empty())	nScore += (1 << vLines.size()) * 100;

                // Pick New Piece
                nCurrentX = nFieldWidth / 2;
                nCurrentY = 0;
                nCurrentRotation = 0;
                nCurrentPiece = rand() % 7;

                // If piece does not fit straight away, game over!
                bGameOver = !doesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY);
            }
        }

        // RENDER OUTPUT ======================================


        //draw the filed
        for (int x = 0; x < nFieldWidth; x++)
        {
            for (int y = 0; y < nFieldHeight; y++)
            {
                screen[(y+2) * nScreenWidth + (x + 2)] = L" ABCDEFG=#"[pField[y*nFieldWidth + x]];
            }
        }

        //draw current piece
        for (int px = 0; px < 4; px++)
        {
            for (int py = 0; py < 4; py++)
            {
                if (tetmino[nCurrentPiece][rotate(px, py, nCurrentRotation)] != L'.')
                    screen[(nCurrentY + py + 2) * nScreenWidth + (nCurrentX + px + 2)] = nCurrentPiece + 65;
            }
        }

        // Draw Score
        swprintf_s(&screen[2 * nScreenWidth + nFieldWidth + 6], 16, L"SCORE: %8d", nScore);

        if (!vLines.empty())
        {
            WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, {0, 0}, &dwBytesWritten);
            this_thread::sleep_for(400ms); // Delay a bit

            for (auto& v : vLines)
                for (int px = 1; px < nFieldWidth - 1; px++)
                {
                    for (int py = v; py > 0; py--)
                        pField[py * nFieldWidth + px] = pField[(py - 1) * nFieldWidth + px];
                    pField[px] = 0;
                }

            vLines.clear();
        }


        //display frame
        WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0, 0 }, &dwBytesWritten);
    }


    //death screen
    CloseHandle(hConsole);
    cout << "Game over, score: " << nScore << endl;
    system("pause");



   
    
    return 0;
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

bool doesPieceFit(int nTetromino, int nRotation, int nPosX, int nPosY)
{
    for (int px = 0; px < 4; px++)
    {
        for (int py = 0; py < 4; py++)
        {
            int pi = rotate(px, py, nRotation);

            int fi = (nPosY + py) * nFieldWidth + (nPosX + px);

            if (nPosX + px >= 0 && nPosX + px < nFieldWidth)
            {
                if (nPosY + py >= 0 && nPosY + py < nFieldHeight)
                {
                    // In Bounds so do collision check
                    if (tetmino[nTetromino][pi] != L'.' && pField[fi] != 0)
                        return false; // fail on first hit
                }
            }
        }
    }


    return true;
}

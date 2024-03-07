#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
bool GameOver;
int const height = 20;
int const width = 20;
int x, y, fructx, fructy, scor;
int coadax[100], coaday[100], ncoada;
enum Directie {STOP,SUS,JOS,STANGA,DREAPTA};
Directie dir;
void Setup() {
    GameOver = false;
    dir =STOP;
    x = width / 2;
    y = height / 2;
    fructx = rand() % width;
    fructy = rand() % height;

}
void Draw() {
    system("CLS");
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "O";
            else if (i == fructy && j == fructx)
                cout << "F";
            else {
                bool print = false;
                for (int k = 0; k < ncoada; k++) {
                    if (coadax[k] == j && coaday[k] == i) {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    cout << "Scorul tau este: " << scor << endl;
}

void Logic() {
    int prevX = coadax[0];
    int prevY = coaday[0];
    int prev2X, prev2Y;
    coadax[0] = x;
    coaday[0] = y;
    for (int i = 1; i < ncoada; i++) {
        prev2X = coadax[i];
        prev2Y = coaday[i];
        coadax[i] = prevX;
        coaday[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir) {
    case SUS:
        y--;
        break;
    case JOS:
        y++;
        break;
    case STANGA:
        x--;
        break;
    case DREAPTA:
        x++;
        break;
    default:
        break;
    }
  
    if (x >= width || x < 0 || y >= height || y < 0) {
        GameOver = true;
    }

    for (int i = 0; i < ncoada; i++) {
        if (x == coadax[i] && y == coaday[i]) {
            GameOver = true;
        }
    }
    if (x == fructx && y == fructy) {
        scor += 10;
        fructx = rand() % width;
        fructy = rand() % height;
        ncoada++; 
    }
}


void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'w':
            dir = SUS;
            break;
        case 'a':
            dir = STANGA;
            break;
        case 's':
            dir = JOS;
            break;
        case 'd':
            dir = DREAPTA;
            break;
        default:
            break;
        }
    }
}

int main()
{
    Setup();
    while (!GameOver) {
        Draw();
        Input();
        Logic();
        Sleep(40);
    }
    return 0;
}



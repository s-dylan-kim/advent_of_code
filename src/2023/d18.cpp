#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
using namespace std;

#define P2 true

int main(void)
{
    auto start = chrono::high_resolution_clock::now();


    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");

    char dir;
    long in;
    string colorCode;
    long sol = 0;

    long sub = 0; // sub for edge

    long curX = 0; long curY = 0;
    while (file >> dir >> in >> colorCode) {
        string strippedColorCode = colorCode.substr(2, colorCode.size() - 4);
        char p2Dir = colorCode[colorCode.size() - 2];

        long p2Dist = 0;
        for (int i = 0; i < strippedColorCode.size(); i++) {
            p2Dist *= 16;
            if (strippedColorCode[i] >= '0' && strippedColorCode[i] <= '9') {
                p2Dist += strippedColorCode[i] - '0';
            } else {
                p2Dist += strippedColorCode[i] - 'a' + 10;
            }
        }

        long oldX = curX;
        long oldY = curY;

        if (P2) {
            switch (p2Dir) {
                case '0':
                    dir = 'R';
                    break;
                case '1':
                    dir = 'D';
                    break;
                case '2':
                    dir = 'L';
                    break;
                case '3':
                    dir = 'U';
                    break;
            }
            in = p2Dist;
            cout << dir << ", " << in << endl;
        }

        switch (dir) {
            case 'U':
                curY -= in;
                break;
            case 'L':
                curX -= in;
                break;
            case 'R':
                curX += in;
                break;
            case 'D':
                curY += in;
                break;
        }

        cout << curX << ", " << curY << endl;

        sol += (oldY + curY) * (oldX - curX);
        sub += in;
    }

    sol = abs(sol);
    sol /= 2;
    sol += (sub/2);
    sol += 1;
    cout << sub << endl;
    cout << sol << endl;



    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "time in seconds " << duration.count() << endl;    
}
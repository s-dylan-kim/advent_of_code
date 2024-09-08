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


int main(void)
{
    auto start = chrono::high_resolution_clock::now();


    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");

    string in;
    int sol = 0;
    int line = 0;

    while (getline(file, in)) {
        stringstream s(in);

        string burn1;
        string burn2;
        s >> burn1 >> burn2;

        int count;
        int minRed = 0;
        int minBlue = 0;
        int minGreen = 0;
        string color;
        bool flag = true;
        line++;

        while (s >> count >> color) {
            if (color[color.size() - 1] == ',' || color[color.size() - 1] == ';') {
                color = color.substr(0, color.size() - 1);
            }
            if (color == "red" && count > minRed) {
                minRed = count;
            }
            if (color == "green" && count > minGreen) {
                minGreen = count;
            }
            if (color == "blue" && count > minBlue) {
                minBlue = count;
            }
        }
        cout << line << ": " << minRed * minGreen * minBlue << endl;
        sol += minRed * minGreen * minBlue;
    }

    cout << sol << endl;



    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "time in seconds " << duration.count() << endl;    
}
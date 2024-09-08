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

int gearX;
int gearY;
bool gearFound;


struct pairHash {
    inline size_t operator()(const pair<int,int> & v) const {
        return v.first*256+v.second;
    }
};

bool incrementGear(int x, int y, int val, unordered_map<pair<int, int>, int, pairHash> gears, unordered_map<pair<int, int>, int, pairHash>& gearsAdj, unordered_set<pair<int, int>,  pairHash> symbols) {
    if (gears.find(make_pair(x, y)) != gears.end()) {
        gearFound = true;
        gearX = x;
        gearY = y;
        gearsAdj[make_pair(x,y)] += 1;
    }
    return (symbols.find(make_pair(x, y)) != symbols.end());
}

int main(void)
{
    auto start = chrono::high_resolution_clock::now();


    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");

    string in;
    int sol = 0;
    int sol2 = 0;

    unordered_set<pair<int, int>,  pairHash> symbols;
    unordered_map<pair<int, int>, int, pairHash> gears;
    unordered_map<pair<int, int>, int, pairHash> gearsAdj;

    int y = 0;
    while (file >> in) {
        stringstream curLine(in);

        char curChar;
        
        int x = 0;
        while (curLine >> curChar) {
            if (!(curChar == '.' || (curChar >= '0' && curChar <= '9'))) {
                cout << "adding " << x << ", " << y << endl;
                symbols.insert(make_pair(x, y));
                if (curChar == '*') {
                    gears[make_pair(x,y)] = 1;
                    gearsAdj[make_pair(x,y)] = 0;
                    cout << "gear: " << x << ", " << y << endl;
                }
            }
            x++;
        }
        y++;
    }

    file.clear();                 // clear fail and eof bits
    file.seekg(0, ios::beg); // back to the start!

    y = 0;
    while (file >> in) {
        stringstream curLine(in);

        char curChar;

        bool inNum = false;
        bool isConnected = true;
        gearFound = false;
        int val = 0;

        int x = 0;
        while (curLine >> curChar) {
            // cout << curChar << endl;
            if (curChar >= '0' && curChar <= '9') {
                val *= 10;
                val += curChar - '0';
                if (!inNum) {
                    isConnected = (
                        incrementGear(x - 1, y, val, gears, gearsAdj, symbols) || 
                        incrementGear(x - 1, y - 1, val, gears, gearsAdj, symbols) ||
                        incrementGear(x - 1, y + 1, val, gears, gearsAdj, symbols)
                    );
                    // cout << isConnected << endl;
                    inNum = true;
                } 
                isConnected = isConnected || (
                    incrementGear(x, y - 1, val, gears, gearsAdj, symbols) || 
                    incrementGear(x, y + 1, val, gears, gearsAdj, symbols)
                );
                // cout << val << ": " << isConnected << endl;
            } else {
                if (inNum) {
                    isConnected = isConnected || (
                        incrementGear(x, y - 1, val, gears, gearsAdj, symbols) ||
                        incrementGear(x, y, val, gears, gearsAdj, symbols) || 
                        incrementGear(x, y + 1, val, gears, gearsAdj, symbols)
                    );
                    if (gearFound) {
                        gears[make_pair(gearX, gearY)] *= val;
                        // cout << gearX << ", " << gearY << " " << gears[make_pair(gearX, gearY)] << endl;
                    }
                    // cout << x << ", " << y << endl;
                    // if (val > 0) cout << val << ": " << isConnected << endl;  
                    sol += isConnected ? val : 0;
                    gearFound = false;
                }
                inNum = false;
                val = 0;
            }
            x++;
        }
        if (inNum) {
            isConnected = isConnected || (
                incrementGear(x, y - 1, val, gears, gearsAdj, symbols) ||
                incrementGear(x, y, val, gears, gearsAdj, symbols) || 
                incrementGear(x, y + 1, val, gears, gearsAdj, symbols)
            );
            if (gearFound) gears[make_pair(gearX, gearY)] *= val;
            
            // if (val > 0) cout << val << ": " << isConnected << endl;  
            sol += isConnected ? val : 0;
            gearFound = false;
        }
        y++;
    }

    for (auto it = gears.begin(); it != gears.end(); ++it) {
        cout << it->first.first << ", " << it->first.second << ": " << gearsAdj[it->first] << endl;
        if(gearsAdj[it->first] == 2) {
            sol2 += it->second;
        }
    }

    for (auto it = gearsAdj.begin(); it != gearsAdj.end(); ++it) {
        cout << it->first.first << ", " << it->first.second << ": " << it->second << endl;
    }

    cout << sol << endl;
    cout << sol2 << endl;



    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "time in seconds " << duration.count() << endl;    
}
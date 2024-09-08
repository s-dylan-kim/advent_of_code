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
    long sol = 0;

    vector<pair<int, int>> galaxies;
    vector<pair<long, long>> galaxies_modified;

    vector<vector<bool>> graph;

    vector<bool> galaxyCol;
    vector<bool> galaxyRow;

    int y = 0;
    int x = 0;
    while (getline(file, in)) {
        x = 0;
        stringstream line(in);
        vector<int> curLine;
        char curChar;
        while (line >> curChar) {
            if (curChar != 13) {
                curLine.push_back(curChar == '#');
                if (curChar == '#') {
                    galaxies.push_back(make_pair(y, x));

                    if (y >= galaxyRow.size()) {
                        galaxyRow.resize(y + 1, false);
                    }

                    if (x >= galaxyCol.size()) {
                        galaxyCol.resize(x + 1, false);
                    }

                    galaxyRow[y] = true;
                    galaxyCol[x] = true;
                }
            }
            x++;
        }
        galaxyCol.resize(x, false);

        y++;
    }
    galaxyRow.resize(y, false);


    vector<long> galaxyColMod(galaxyCol.size(), 0);
    vector<long> galaxyRowMod(galaxyRow.size(), 0);
    int curSum = 0;
    for (int i = 0; i < galaxyCol.size(); i++) {
        curSum += (!galaxyCol[i] ? 999999: 0);
        galaxyColMod[i] = curSum + i;
    }
    curSum = 0;
    for (int i = 0; i < galaxyRow.size(); i++) {
        curSum += (!galaxyRow[i] ? 999999: 0);
        galaxyRowMod[i] = curSum + i;
    }

    for (int i = 0; i < galaxies.size(); i++) {
        galaxies_modified.push_back(make_pair(galaxyRowMod[galaxies[i].first], galaxyColMod[galaxies[i].second]));
    }

    for (int i = 0; i < galaxies_modified.size(); i++) {
        for (int j = i + 1; j < galaxies_modified.size(); j++) {
            int temp = abs(galaxies_modified[i].first - galaxies_modified[j].first) + abs(galaxies_modified[i].second - galaxies_modified[j].second);
            sol += temp;
            // cout << "(" << galaxies[i].first << ", " << galaxies[i].second << "), (" << galaxies[j].first << ", " << galaxies[j].second << "): " << temp << endl;
            // cout << "(" << galaxies_modified[i].first << ", " << galaxies_modified[i].second << "), (" << galaxies_modified[j].first << ", " << galaxies_modified[j].second << "): " << temp << endl;
        }
    }

    cout << sol << endl;



    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "time in seconds " << duration.count() << endl;    
}
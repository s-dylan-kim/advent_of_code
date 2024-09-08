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

    vector<vector<pair<string, int>>> map;

    for (int i = 0; i < 256; i++) {
        map.push_back(vector<pair<string,int>>());
    }


    char in;
    int sol = 0;

    string curLoc = "";
    bool foundEquals = false;
    int focalLen = 0;

    int curSum = 0;
    bool extra = true;
    while (file >> in || extra) {
        if (file.eof()) extra = false;
        if (in == ',' || file.eof()) {
            if (foundEquals) {
                bool found = false;
                for (int i = 0; i < map[curSum].size(); i++) {
                    if (map[curSum][i].first == curLoc) {
                        found = true;
                        map[curSum][i] = make_pair(curLoc, focalLen);
                    }
                }
                if (!found) map[curSum].push_back(make_pair(curLoc, focalLen));
            } else {
                for (int i = 0; i < map[curSum].size(); i++) {
                    if (map[curSum][i].first == curLoc) {
                        map[curSum].erase(next(map[curSum].begin(), i));
                        break;
                    }
                }
            }
            // cout << curLoc  << " " << focalLen << " " << foundEquals << endl;
            // cout << curSum << endl;
            curLoc = "";
            foundEquals = false;

            sol += curSum;

            curSum = 0;
        } else {
            if (in == '=') {
                foundEquals = true;
            }
            else if (in == '-') {
            }
            else if (!foundEquals) {
                curLoc += in;
                curSum += in;
                curSum *= 17;
                curSum %= 256;
            }
            else{
                focalLen = in - '0';
            }
        }
    }

    int sol2 = 0;
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            int temp2;
            temp2 = (i + 1) * (j + 1) * map[i][j].second;
            sol2 += temp2;
            // cout << "box " << (i + 1) << " idx: " << (j + 1) << " focal: " << map[i][j].second << " val: " << temp2 << endl;
        }
    }

    sol += curSum;

    cout << sol << endl;
    cout << sol2 << endl;



    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "time in seconds " << duration.count() << endl;    
}
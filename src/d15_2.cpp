#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#define LINE 2000000
#define AREA 4000000
using namespace std;


int main(void)
{
    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");
    vector<vector<int>> input; 
    int sensorx, sensory, beaconx, beacony;
    while (file >> sensorx >> sensory >> beaconx >> beacony) {
        vector<int> temp{sensorx, sensory, beaconx, beacony};
        input.push_back(temp);
    }

    vector<vector<pair<int, int>>> ranges;

    for (int i = 0; i < AREA; i++) {
        vector<pair<int,int>> cur_row;
        ranges.push_back(cur_row);
    }

    for (int i = 0; i < input.size(); i++) {
        int dist = abs(input[i][0] - input[i][2]) + abs(input[i][1]-input[i][3]);
        for (int j = 0; j < AREA; j++) {
            int leftover = dist - abs(input[i][1] - j);
            if (leftover >= 0) {
                ranges[j].push_back(pair<int,int>(input[i][0] - leftover, input[i][0] + leftover));
            }
        }
        
    }

    for (int i = 0; i < AREA; i++) {
        sort(ranges[i].begin(), ranges[i].end());

        int max = ranges[i][0].second;
        for (int j = 1; j < ranges[i].size(); j++) {
            if (ranges[i][j].first > max + 1 && ranges[i][j].first >= 0 && ranges[i][j].first <= AREA) {
                return 0;
            }
            if (ranges[i][j].second > max) max = ranges[i][j].second;
        }
    }
}
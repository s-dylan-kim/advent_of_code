#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#define LINE 2000000
#define AREA 4000000
using namespace std;


int main(void)
{
    bool flag = false;


    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");
    vector<vector<int>> input; 
    int sensorx, sensory, beaconx, beacony;
    while (file >> sensorx >> sensory >> beaconx >> beacony) {
        vector<int> temp{sensorx, sensory, beaconx, beacony};
        input.push_back(temp);
    }

    int sol = 0;
    unordered_set<int> seen;
    unordered_set<int> beacons;

    for (int k = 0; k <= AREA; k++) {
        if (k % 1000 == 0) cout << "x: " << k << endl;
        for (int j = 0; j <= AREA; j++) {
            bool found = false;

            for (int i = 0; i < input.size(); i++) {
                int dist = abs(input[i][0] - input[i][2]) + abs(input[i][1]-input[i][3]);
                int dist2 = abs(input[i][0] - k) + abs(input[i][1]-j);
                if (dist2 <= dist) {
                    // cout << k << ", " << j << " found by sensor at " << input[i][0] << ", " << input[i][1] << endl;
                    found = true;
                    break;
                }
            }

            
                


                // cout << "sensor at " << sensorx << ", " << sensory << " detecting beacon at " << beaconx << ", " << beacony << endl;
                // if (beacony == k) beacons.insert(beaconx);

                // if (abs(LINE - sensory) <= dist) {
                // for (int i = sensorx - (dist - abs(k - sensory)) ; i <= sensorx + (dist - abs(k - sensory)); i++) {
                //     // if (beacony == LINE && i == beaconx) continue;
                //     if (seen.find(i) == seen.end()) {
                //         // cout << i << endl;
                //         seen.insert(i);
                //     }
            if (!found) {
                cout << k << ", " << j << endl;
                flag = true;
                break;
            }
        }
        if (flag) break;


        // ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");

        // int sensorx, sensory, beaconx, beacony;
        // int sol = 0;

        // unordered_set<int> seen;
        // unordered_set<int> beacons;
        // while (file >> sensorx >> sensory >> beaconx >> beacony) {
        //     int dist = abs(sensorx - beaconx) + abs(sensory-beacony);
        //     // cout << "sensor at " << sensorx << ", " << sensory << " detecting beacon at " << beaconx << ", " << beacony << endl;
        //     if (beacony == k) beacons.insert(beaconx);

        //     // if (abs(LINE - sensory) <= dist) {
        //     for (int i = sensorx - (dist - abs(k - sensory)) ; i <= sensorx + (dist - abs(k - sensory)); i++) {
        //         // if (beacony == LINE && i == beaconx) continue;
        //         if (seen.find(i) == seen.end()) {
        //             // cout << i << endl;
        //             seen.insert(i);
        //         }
        //     }
        // }
        // for (int j = 0; j <= AREA; j++) {
        //     if (seen.find(j) == seen.end()) {
        //         cout << k << ", " << j << endl;
        //         flag = true;
        //         break;
        //     }
        // }
        // if (flag) break;
    }


    



    // cout << seen.size() << endl;    
}
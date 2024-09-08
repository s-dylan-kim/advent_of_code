#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
using namespace std;

long long gcd(long long int a, long long int b) 
{ 
  if (b == 0) 
    return a; 
  return gcd(b, a % b); 
} 
  
long long lcm(long a, int b) 
{ 
    return (a / gcd(a, b)) * b; 
} 


int main(void)
{
    auto start = chrono::high_resolution_clock::now();


    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");

    int sol = 0;

    string instructions;

    file >> instructions;

    unordered_map<string, pair<string, string>> map;

    string left, right;
    string trash;
    string room;
    vector<string> curRooms;
    vector<int> startCycle;
    vector<int> cycleLen;
    // vector<int> printCnt;
    while (file >> room >> trash >> left >> right) {
        left = left.substr(1, 3);
        right = right.substr(0, 3);
        map[room] = make_pair(left, right);
        if (room[2] == 'A') {
            curRooms.push_back(room);
            startCycle.push_back(0);
            cycleLen.push_back(0);
            // printCnt.push_back(0);
        }
    }

    int instructionIdx = 0;
    while (true) {
        bool flag = true;
        for (int i = 0; i < curRooms.size(); i++) {
            // cout << sol << ", " << i << ", " << curRooms[i] << endl;
            if (curRooms[i][2] == 'Z') {
                
                if (startCycle[i] != 0 && cycleLen[i] == 0)  {
                    cycleLen[i] = sol - startCycle[i];
                    if (cycleLen[i] == startCycle[i]) startCycle[i] = 0;
                }
                if (startCycle[i] == 0 && cycleLen[i] == 0) {
                    startCycle[i] = sol;
                    cout << sol << endl;
                }
            }
            if (cycleLen[i] == 0) {
                flag = false;
            }
        }
        if (flag) break;

        sol++;

        for (int i = 0; i < curRooms.size(); i++) {
            if (instructions[instructionIdx] == 'L') {
            curRooms[i] = map[curRooms[i]].first;
            } else {
                curRooms[i] = map[curRooms[i]].second;
            }
        }
        
        
        instructionIdx++;
        if (instructionIdx >= instructions.size()) {
            instructionIdx = 0;
        }
    }

    long long M = 1;
    cout << endl;
    for (int i = 0; i < cycleLen.size(); i++) {
        cout << startCycle[i] << ", " << cycleLen[i] << endl;
        M = lcm(M, cycleLen[i]);
    }
    vector<int> m;
    vector<int> mPrime;
    long long sol2 = 0;
    for (int i = 0; i < cycleLen.size(); i++) {
        m.push_back(M/cycleLen[i]);
        mPrime.push_back(m[i] % cycleLen[i]);
        sol2 += startCycle[i] * m[i] * mPrime[i]; 
    }



    cout << sol2 << endl;
    cout << M << endl;
    

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "time in seconds " << duration.count() << endl;    
}
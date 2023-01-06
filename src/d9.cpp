#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_set>
using namespace std;

#define PART 2

#define ARRAY_SIZE (PART == 2 ? 10 : 2)
#define headx x[j-1]
#define heady y[j-1]
#define tailx x[j]
#define taily y[j]

struct pair_hash {
    inline std::size_t operator()(const std::pair<int,int> & v) const {
        return v.first*31+v.second;
    }
};

int main(void)
{
    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");

    unordered_set<pair<int, int>,  pair_hash> visited;

    int repCnt;
    char dir;
    int sol = 0;

    int x[ARRAY_SIZE];
    int y[ARRAY_SIZE];

    for (int i = 0; i < ARRAY_SIZE; i++) {
        x[i] = 0;
        y[i] = 0;
    } 

    visited.insert(pair<int, int>(0, 0));
    sol++; // add (0,0) to sol

    while (file >> dir >> repCnt) {
        for (int i = 0; i < repCnt; i++) {

            switch(dir) {
                case 'R':
                    x[0]++;
                    break;
                case 'L':
                    x[0]--;
                    break;
                case 'U':
                    y[0]++;
                    break;
                case 'D':
                    y[0]--;
                    break;
            }

            for (int j = 1; j < ARRAY_SIZE; j++) {
                if (tailx != headx && taily != heady) {
                    if (abs(tailx - headx) > 1 || abs(taily - heady) > 1) {
                        if (tailx > headx) {
                            tailx--;
                        } else {
                            tailx++;
                        }

                        if (taily > heady) {
                            taily--;
                        } else {
                            taily++;
                        }
                    }
                } else {
                    if (tailx - headx > 1) tailx--;
                    if (tailx - headx < -1) tailx++;

                    if (taily - heady > 1) taily--;
                    if (taily - heady < -1) taily++;
                }

            }
            

            if (visited.find(pair<int,int>(x[ARRAY_SIZE - 1], y[ARRAY_SIZE - 1])) == visited.end()) {
                visited.insert(pair<int,int>(x[ARRAY_SIZE - 1], y[ARRAY_SIZE - 1]));
                sol++;
            }
        }
    }

    cout << sol << endl;    
}
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

#define ITERATION_COUNT 64

struct pair_hash {
    inline std::size_t operator()(const std::pair<int,int> & v) const {
        return v.first*256+v.second;
    }
};

int main(void)
{
    auto start = chrono::high_resolution_clock::now();

    vector<vector<bool>> graph;
    unordered_set<pair<int, int>, pair_hash>* curPoints = new unordered_set<pair<int, int>, pair_hash>();
    unordered_set<pair<int, int>, pair_hash>* nextPoints = new unordered_set<pair<int, int>, pair_hash>();

    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");

    string in;
    long sol = 0;

    int y = 0;
    int x;

    unordered_set<pair<int, int>, pair_hash>* temp;

    while (file >> in) {
        stringstream lineStream(in);
        char cur;
        vector<bool> curLine;

        x = 0;
        while (lineStream >> cur) {
            if (cur == 'S') {
                curPoints->insert(make_pair(x,y));
                cur = '.';
            }
            x++;
            curLine.push_back(cur == '.');
        }
        y++;
        graph.push_back(curLine);
    }

    for (int i = 0; i < ITERATION_COUNT; i++) {
        // cout << "\n\ni: " << i << endl;
        for (auto it = curPoints->begin(); it != curPoints->end(); ++it) {
            int curX = it->first;
            int curY = it->second;

            // cout << curX << ", " << curY << endl;

            if (curX > 0 && graph[curY][curX - 1]) {
                nextPoints->insert(make_pair(curX - 1, curY));
            }
            if (curX < graph[curY].size() && graph[curY][curX + 1]) {
                nextPoints->insert(make_pair(curX + 1, curY));
            }
            if (curY > 0 && graph[curY - 1][curX]) {
                nextPoints->insert(make_pair(curX, curY - 1));
            }
            if (curY < graph.size() && graph[curY + 1][curX]) {
                nextPoints->insert(make_pair(curX, curY + 1));
            }
        }

        temp = curPoints;
        curPoints = nextPoints;
        nextPoints = temp;
        nextPoints->clear();
    }

    sol = curPoints->size();

    cout << sol << endl;

    delete nextPoints;
    delete curPoints;



    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "time in seconds " << duration.count() << endl;    
}
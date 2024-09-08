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

struct pair_hash {
    inline std::size_t operator()(const std::pair<int,int> & v) const {
        return v.first*256+v.second;
    }
};


int getCount (int itCnt, unordered_set<pair<int, int>, pair_hash>* curPoints, unordered_set<pair<int, int>, pair_hash>* nextPoints, vector<vector<bool>>& graph, pair<int, int> startPoint) {
    unordered_set<pair<int, int>, pair_hash>* temp;
    curPoints->clear();
    nextPoints->clear();
    curPoints->insert(startPoint);
    for (int i = 0; i < itCnt; i++) {
        // cout << "\n\ni: " << i << endl;
        for (auto it = curPoints->begin(); it != curPoints->end(); ++it) {
            int curX = it->first;
            int curY = it->second;

            // cout << curX << ", " << curY << endl;

            if (curX > 0 && graph[curY][curX - 1]) {
                nextPoints->insert(make_pair(curX - 1, curY));
            }
            if (curX < graph[curY].size() - 1 && graph[curY][curX + 1]) {
                nextPoints->insert(make_pair(curX + 1, curY));
            }
            if (curY > 0 && graph[curY - 1][curX]) {
                nextPoints->insert(make_pair(curX, curY - 1));
            }
            if (curY < graph.size() - 1 && graph[curY + 1][curX]) {
                nextPoints->insert(make_pair(curX, curY + 1));
            }
        }

        temp = curPoints;
        curPoints = nextPoints;
        nextPoints = temp;
        nextPoints->clear();
    }
    return curPoints->size();
}

int main(void)
{
    auto start = chrono::high_resolution_clock::now();

    vector<vector<bool>> graph;
    unordered_set<pair<int, int>, pair_hash>* curPoints = new unordered_set<pair<int, int>, pair_hash>();
    unordered_set<pair<int, int>, pair_hash>* nextPoints = new unordered_set<pair<int, int>, pair_hash>();

    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");

    string in;
    long long sol = 0;

    int y = 0;
    int x;

    pair<int, int> startPoint;

    while (file >> in) {
        stringstream lineStream(in);
        char cur;
        vector<bool> curLine;

        x = 0;
        while (lineStream >> cur) {
            if (cur == 'S') {
                startPoint = make_pair(x,y);
                cur = '.';
            }
            x++;
            curLine.push_back(cur == '.');
        }
        y++;
        graph.push_back(curLine);
    }

    long long pattern1 = getCount(130, curPoints, nextPoints, graph, startPoint);
    long long pattern0 = getCount(131, curPoints, nextPoints, graph, startPoint);

    long long pattern1edge = pattern1 - getCount(65, curPoints, nextPoints, graph, startPoint);
    long long pattern0edge = pattern0 - getCount(64, curPoints, nextPoints, graph, startPoint); 
    

    sol = pattern1 * ((long long)202301 * (long long)202301) + pattern0 * ((long long)202300 * (long long)202300) + (long long)202300 * pattern0edge - (long long)202301 * pattern1edge;

    cout << sol << endl;

    delete nextPoints;
    delete curPoints;



    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "time in seconds " << duration.count() << endl;    
}
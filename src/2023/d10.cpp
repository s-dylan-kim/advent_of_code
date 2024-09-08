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

    vector<vector<int>> graph;
    vector<vector<int>> dists;

    queue<pair<int,int>> toVisit;
    int startX;
    int startY;

    int y = 0;
    int x = 0;

    while (getline(file, in)) {
        stringstream line(in);
        x= 0;
        char cur;
        vector<int> curLine;
        vector<int> curDists;
        while (line >> cur) {
            if (cur != 13) {
                curLine.push_back(cur);
                

                if (cur == 'S') {
                    startX = x;
                    startY = y;
                    curDists.push_back(0);
                } else {
                    curDists.push_back(-1);
                }
            }
            x++;
        }
        graph.push_back(curLine);
        dists.push_back(curDists);

        y++;
    }


    if (startX >= 1 && (graph[startY][startX-1] == 'L' || graph[startY][startX-1] == 'F' || graph[startY][startX-1] == '-')) {
        toVisit.push(make_pair(startY, startX-1));
        dists[startY][startX-1] = 1;
    }
    if (startX < graph[0].size() - 1 && (graph[startY][startX+1] == 'J' || graph[startY][startX+1] == '7' || graph[startY][startX+1] == '-')) {
        toVisit.push(make_pair(startY, startX+1));
        dists[startY][startX+1] = 1;
    }
    if (startY >= 1 && (graph[startY-1][startX] == '7' || graph[startY-1][startX] == 'F' || graph[startY-1][startX] == '|')) {
        toVisit.push(make_pair(startY-1, startX));
        dists[startY-1][startX] = 1;
    }
    if (startY < graph.size() - 1 && (graph[startY+1][startX] == 'J' || graph[startY+1][startX] == 'L' || graph[startY+1][startX] == '|')) {
        toVisit.push(make_pair(startY+1, startX));
        dists[startY+1][startX] = 1;
    }

    while (!toVisit.empty()) {
        pair<int, int> cur = toVisit.front();
        toVisit.pop();

        if (dists[cur.first][cur.second] > sol) sol = dists[cur.first][cur.second];

        switch (graph[cur.first][cur.second]) {
            case '-':
                if (dists[cur.first][cur.second-1] == -1) {
                    dists[cur.first][cur.second-1] = dists[cur.first][cur.second] + 1;
                    toVisit.push(make_pair(cur.first, cur.second-1));
                }
                if (dists[cur.first][cur.second+1] == -1) {
                    dists[cur.first][cur.second+1] = dists[cur.first][cur.second] + 1;
                    toVisit.push(make_pair(cur.first, cur.second+1));
                }
                break;
            case '|':
                if (dists[cur.first-1][cur.second] == -1) {
                    dists[cur.first-1][cur.second] = dists[cur.first][cur.second] + 1;
                    toVisit.push(make_pair(cur.first-1, cur.second));
                }
                if (dists[cur.first+1][cur.second] == -1) {
                    dists[cur.first+1][cur.second] = dists[cur.first][cur.second] + 1;
                    toVisit.push(make_pair(cur.first+1, cur.second));
                }
                break;
            case '7':
                if (dists[cur.first][cur.second-1] == -1) {
                    dists[cur.first][cur.second-1] = dists[cur.first][cur.second] + 1;
                    toVisit.push(make_pair(cur.first, cur.second-1));
                }
                if (dists[cur.first+1][cur.second] == -1) {
                    dists[cur.first+1][cur.second] = dists[cur.first][cur.second] + 1;
                    toVisit.push(make_pair(cur.first+1, cur.second));
                }
                break;
            case 'F':
                if (dists[cur.first][cur.second+1] == -1) {
                    dists[cur.first][cur.second+1] = dists[cur.first][cur.second] + 1;
                    toVisit.push(make_pair(cur.first, cur.second+1));
                }
                if (dists[cur.first+1][cur.second] == -1) {
                    dists[cur.first+1][cur.second] = dists[cur.first][cur.second] + 1;
                    toVisit.push(make_pair(cur.first+1, cur.second));
                }
                break;
            case 'L':
                if (dists[cur.first][cur.second+1] == -1) {
                    dists[cur.first][cur.second+1] = dists[cur.first][cur.second] + 1;
                    toVisit.push(make_pair(cur.first, cur.second+1));
                }
                if (dists[cur.first-1][cur.second] == -1) {
                    dists[cur.first-1][cur.second] = dists[cur.first][cur.second] + 1;
                    toVisit.push(make_pair(cur.first-1, cur.second));
                }
                break;
            case 'J':
                if (dists[cur.first][cur.second-1] == -1) {
                    dists[cur.first][cur.second-1] = dists[cur.first][cur.second] + 1;
                    toVisit.push(make_pair(cur.first, cur.second-1));
                }
                if (dists[cur.first-1][cur.second] == -1) {
                    dists[cur.first-1][cur.second] = dists[cur.first][cur.second] + 1;
                    toVisit.push(make_pair(cur.first-1, cur.second));
                }
                break;
        }
    }

    // for (int i = 0; i < dists.size(); i++) {
    //     for (int j = 0; j < dists[i].size(); j++) {
    //         cout << dists[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    cout << sol << endl;



    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "time in seconds " << duration.count() << endl;    
}
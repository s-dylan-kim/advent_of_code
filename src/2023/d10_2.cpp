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


    ifstream file("/mnt/c/Users/sdyla/Advent/input.txt");

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

    bool plusX = false, minusX = false,  minusY = false;

    if (startX >= 1 && (graph[startY][startX-1] == 'L' || graph[startY][startX-1] == 'F' || graph[startY][startX-1] == '-')) {
        toVisit.push(make_pair(startY, startX-1));
        dists[startY][startX-1] = 1;
        minusX = true;
    }
    if (startX < graph[0].size() - 1 && (graph[startY][startX+1] == 'J' || graph[startY][startX+1] == '7' || graph[startY][startX+1] == '-')) {
        toVisit.push(make_pair(startY, startX+1));
        dists[startY][startX+1] = 1;
        plusX = true;
    }
    if (startY >= 1 && (graph[startY-1][startX] == '7' || graph[startY-1][startX] == 'F' || graph[startY-1][startX] == '|')) {
        toVisit.push(make_pair(startY-1, startX));
        dists[startY-1][startX] = 1;
        minusY = true;
    }
    if (startY < graph.size() - 1 && (graph[startY+1][startX] == 'J' || graph[startY+1][startX] == 'L' || graph[startY+1][startX] == '|')) {
        toVisit.push(make_pair(startY+1, startX));
        dists[startY+1][startX] = 1;
    }

    if (minusX) {
        if (plusX) {
            graph[startY][startX] = '-';
        } else if (minusY) {
            graph[startY][startX] = 'J';
        } else {
            graph[startY][startX] = '7';
        }
    } else if (plusX) {
        if (minusY) {
            graph[startY][startX] = 'L';
        } else {
            graph[startY][startX] = 'F';
        }
    } else {
        graph[startY][startX] = '|';
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

    int pipeCount = 0;

    vector<vector<int>> newGraph;

    vector<int> firstLine(dists[0].size() + 2, '.');
    newGraph.push_back(firstLine);

    for (int i = 0; i < dists.size(); i++) {
        vector<int> newLine;
        newLine.push_back('.');
        for (int j = 0; j < dists[i].size(); j++) {
            if (dists[i][j] == -1) {
                graph[i][j] = '.';
            } else {
                pipeCount++;
            }
            newLine.push_back(graph[i][j]);
        }
        newLine.push_back('.');
        newGraph.push_back(newLine);
    }

    vector<int> lastLine(dists[0].size() + 2, '.');
    newGraph.push_back(lastLine);

    vector<vector<bool>> outside = vector<vector<bool>>(dists.size() + 1, vector<bool>(dists[0].size() + 1, false));
    vector<vector<bool>> visited = vector<vector<bool>>(dists.size() + 1, vector<bool>(dists[0].size() + 1, false));

    // arbitratily pick top left

    toVisit.push(make_pair(0,0));
    visited[0][0] = true;

    while(!toVisit.empty()) {
        pair<int, int> cur = toVisit.front();
        toVisit.pop();

        if (cur.second > 0 && !visited[cur.first][cur.second - 1] && newGraph[cur.first][cur.second] != '7' && newGraph[cur.first][cur.second] != '|' && newGraph[cur.first][cur.second] != 'F') {
            visited[cur.first][cur.second - 1] = true;
            toVisit.push(make_pair(cur.first, cur.second - 1));
        }
        if (cur.second < outside[0].size() - 1 && !visited[cur.first][cur.second + 1] && newGraph[cur.first][cur.second + 1] != '7' && newGraph[cur.first][cur.second + 1] != '|' && newGraph[cur.first][cur.second + 1] != 'F') {
            visited[cur.first][cur.second + 1] = true;
            toVisit.push(make_pair(cur.first, cur.second + 1));
        }
        if (cur.first > 0 && !visited[cur.first - 1][cur.second] && newGraph[cur.first][cur.second] != 'F' && newGraph[cur.first][cur.second] != '-' && newGraph[cur.first][cur.second] != 'L') {
            visited[cur.first - 1][cur.second] = true;
            toVisit.push(make_pair(cur.first - 1, cur.second));
        }
        // cout << "test4" << endl << flush;
        if (cur.first < outside.size() - 1 && !visited[cur.first + 1][cur.second] && newGraph[cur.first + 1][cur.second] != 'F' && newGraph[cur.first + 1][cur.second] != '-' && newGraph[cur.first + 1][cur.second] != 'L') {
            visited[cur.first + 1][cur.second] = true;
            toVisit.push(make_pair(cur.first + 1, cur.second));
        }
    }


    vector<vector<bool>> isOutside = vector<vector<bool>>(graph.size(), vector<bool>(graph[0].size(), false));

    for (int i = 0; i < visited.size(); i++) {
        for (int j = 0; j < visited[i].size(); j++) {
            if (visited[i][j]) {
                if (i >= 0 && i < graph.size() && j >= 0 && j < graph[i].size() && graph[i][j] == '.') {
                    isOutside[i][j] = true;
                }
                if (i >= 1 && i < graph.size() && j >= 0 && j < graph[i].size() && graph[i-1][j] == '.') {
                    isOutside[i - 1][j] = true;
                }
                if (i >= 0 && i < graph.size() && j >= 1 && j < graph[i].size() && graph[i][j - 1] == '.') {
                    isOutside[i][j - 1] = true;
                }
                if (i >= 1 && i < graph.size() && j >= 1 && j < graph[i].size() && graph[i - 1][j - 1] == '.') {
                    isOutside[i - 1][j - 1] = true;
                }
            }
        }
    }

    int sol2 = 0;
    for (int i = 0; i < isOutside.size(); i++) {
        for (int j = 0; j < isOutside[i].size(); j++) {
            // cout << (isOutside[i][j] ? "1" : graph[i][j] != '.' ? "2" : "0") << " ";
            sol2 += isOutside[i][j];
        }
        // cout << endl;
    }

    cout << pipeCount << endl;
    cout << sol2 << endl;
    cout << (isOutside.size() * isOutside[0].size()) - pipeCount - sol2 << endl;


    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "time in seconds " << duration.count() << endl;    
}
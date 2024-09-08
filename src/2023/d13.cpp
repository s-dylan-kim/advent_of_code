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

int getVal (vector<vector<bool>>& graph) {
    for (int i = 1; i < graph.size(); i++) {
        bool flag = true;
        int diff = 0;

        for (int j = 0; i - 1 - j >= 0 && i + j < graph.size() && diff < 2; j++) {
            for (int k = 0; k < graph[j].size() && diff < 2; k++) {
                if (graph[i - 1 - j][k] != graph[i + j][k]) {
                    diff++;
                }
            }
        }
        if (diff == 1) return (100 * i);
    }

    for (int i = 1; i < graph[0].size(); i++) {
        bool flag = true;
        int diff = 0;

        for (int j = 0; i - 1 - j >= 0 && i + j < graph[0].size() && diff < 2; j++) {
            for (int k = 0; k < graph.size() && diff < 2; k++) {
                if (graph[k][i - 1 - j] != graph[k][i + j]) {
                    diff++;
                }
            }
        }
        if (diff == 1) return i;
    }

    cout << "ERROR" << endl;

    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph[0].size(); j++) {
            cout << (graph[i][j] ? "#" : ".");
        }
        cout << endl;
    }
    cout << endl;

    return -1;
}

int main(void)
{
    auto start = chrono::high_resolution_clock::now();


    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");

    string in;
    int sol = 0;

    vector<vector<bool>> graph;

    while (getline(file, in)) {
        if (in[0] == 13) {
            sol += getVal(graph);

            graph.clear();
            continue;
        }

        stringstream sStream(in);
        char cur;
        vector<bool> curLine = vector<bool>(0, 0);
        while (sStream >> cur) {
            curLine.push_back(cur == '#');
        }

        graph.push_back(curLine);
    }

    // compute last one
    sol += getVal(graph);

    cout << sol << endl;



    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "time in microseconds " << duration.count() << endl;    
}
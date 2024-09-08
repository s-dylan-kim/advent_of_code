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

#define ITERATION_COUNT 26501365

struct tuple_hash {
    inline std::size_t operator()(const std::tuple<int,int,int,int> & v) const {
        return get<0>(v)*256+get<1>(v)+get<2>(v)*65536+get<3>(v)*4194304;
    }
};

int main(void)
{
    auto start = chrono::high_resolution_clock::now();

    vector<vector<bool>> graph;
    unordered_set<tuple<int, int, int, int>, tuple_hash>* curPoints = new unordered_set<tuple<int, int, int, int>, tuple_hash>();
    unordered_set<tuple<int, int, int, int>, tuple_hash>* nextPoints = new unordered_set<tuple<int, int, int, int>, tuple_hash>();
    unordered_set<tuple<int, int, int, int>, tuple_hash>* prevPoints = new unordered_set<tuple<int, int, int, int>, tuple_hash>();
    long sol1 = 0;
    long sol2 = 0;

    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");

    string in;
    long sol = 0;

    int y = 0;
    int x;

    unordered_set<tuple<int, int, int, int>, tuple_hash>* temp;

    while (file >> in) {
        stringstream lineStream(in);
        char cur;
        vector<bool> curLine;

        x = 0;
        while (lineStream >> cur) {
            if (cur == 'S') {
                curPoints->insert(make_tuple(x, y, 0, 0));
                cur = '.';
            }
            x++;
            curLine.push_back(cur == '.');
        }
        y++;
        graph.push_back(curLine);
    }

    bool curSol1 = false;
    for (int i = 0; i <= ITERATION_COUNT; i++) {
        if (i % 100000 == 0) cout << "starting it " << i << endl;
        curSol1 = !curSol1;
        // cout << "\n\ni: " << i << endl;
        for (auto it = curPoints->begin(); it != curPoints->end(); ++it) {
            if (curSol1) {
                sol1++;
            } else {
                sol2++;
            }

            int curX = get<0>(*it);
            int curY = get<1>(*it);
            int curXoff = get<2>(*it);
            int curYoff = get<3>(*it);

            // cout << curX << ", " << curY << endl;

            if (curX > 0) {
                if (graph[curY][curX - 1] && prevPoints->find(make_tuple(curX - 1, curY, curXoff, curYoff)) == prevPoints->end()) {
                    nextPoints->insert(make_tuple(curX - 1, curY, curXoff, curYoff));
                    // cout << "adding" << (curX - 1) << ", " << (curY) << endl;
                }
            } else if (graph[curY][graph[curY].size() - 1] && prevPoints->find(make_tuple(graph[curY].size() - 1, curY, curXoff - 1, curYoff)) == prevPoints->end()) {
                nextPoints->insert(make_tuple(graph[curY].size() - 1, curY, curXoff - 1, curYoff));
                // cout << "adding" << (graph[curY].size() - 1) << ", " << (curY) << endl;
            }
            if (curX < graph[curY].size() - 1) {
                if (graph[curY][curX + 1] && prevPoints->find(make_tuple(curX + 1, curY, curXoff, curYoff)) == prevPoints->end()) {
                    nextPoints->insert(make_tuple(curX + 1, curY, curXoff, curYoff));
                    // cout << "adding" << (curX + 1) << ", " << (curY) << endl;
                }
            } else if (graph[curY][0] && prevPoints->find(make_tuple(0, curY, curXoff + 1, curYoff)) == prevPoints->end()) {
                nextPoints->insert(make_tuple(0, curY, curXoff + 1, curYoff));
                // cout << "adding" << (0) << ", " << (curY) << endl;
            }
            if (curY > 0) {
                if (graph[curY - 1][curX] && prevPoints->find(make_tuple(curX, curY - 1, curXoff, curYoff)) == prevPoints->end()) {
                    nextPoints->insert(make_tuple(curX, curY - 1, curXoff, curYoff));
                    // cout << "adding" << (curX) << ", " << (curY - 1) << endl;
                }
            } else if (graph[graph.size() - 1][curX] && prevPoints->find(make_tuple(curX, graph.size() - 1, curXoff, curYoff - 1)) == prevPoints->end()) {
                nextPoints->insert(make_tuple(curX, graph.size() - 1, curXoff, curYoff - 1));
                // cout << "adding" << (curX) << ", " << (graph.size() - 1) << endl;
            }
            if (curY < graph.size() - 1) {
                if (graph[curY + 1][curX]  && prevPoints->find(make_tuple(curX, curY + 1, curXoff, curYoff)) == prevPoints->end()) {
                    nextPoints->insert(make_tuple(curX, curY + 1, curXoff, curYoff));
                }
            } else if (graph[0][curX] && prevPoints->find(make_tuple(curX, 0, curXoff, curYoff + 1)) == prevPoints->end()) {
                nextPoints->insert(make_tuple(curX, 0, curXoff, curYoff + 1));
            }
        }

        temp = prevPoints;
        prevPoints = curPoints;
        curPoints = nextPoints;
        nextPoints = temp;
        nextPoints->clear();

        // cout << "\n" << i << ": " << (curSol1 ? sol1 : sol2) << endl;;
    }

    sol = curSol1 ? sol1 : sol2;

    cout << sol << endl;

    delete nextPoints;
    delete curPoints;
    delete prevPoints;
 


    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "time in seconds " << duration.count() << endl;    
}
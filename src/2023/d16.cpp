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

enum Direction { North, South, East, West };

class PathElement {
    public:
    int x;
    int y;
    Direction dir;

    PathElement(int x, int y, Direction dir) {
        this->x = x;
        this->y = y;
        this->dir = dir;
    }

    vector<PathElement> getNext(vector<vector<int>>& graph) {
        int maxX = graph[0].size() - 1;
        int maxY = graph.size() - 1;
        vector<PathElement> sol;
        switch (graph[y][x]) {
            case '\\':
                switch (dir) {
                    case North:
                        if (x > 0) sol.push_back(PathElement(x - 1, y, West));
                        break;
                    case South:
                        if (x < maxX) sol.push_back(PathElement(x + 1, y, East));
                        break;
                    case East:
                        if (y < maxY) sol.push_back(PathElement(x, y + 1, South));
                        break;
                    case West:
                        if (y > 0) sol.push_back(PathElement(x, y - 1, North));
                        break;
                }
                break;
            case '/':
                switch (dir) {
                    case North:
                        if (x < maxX) sol.push_back(PathElement(x + 1, y, East));
                        break;
                    case South:
                        if (x > 0) sol.push_back(PathElement(x - 1, y, West));
                        break;
                    case East:
                        if (y > 0) sol.push_back(PathElement(x, y - 1, North));
                        break;
                    case West:
                        if (y < maxY) sol.push_back(PathElement(x, y + 1, South));
                        break;
                }
                break;
            case '|':
                if (dir != South) {
                    if (y > 0) sol.push_back(PathElement(x, y - 1, North));
                }
                if (dir != North) {
                    if (y < maxY) sol.push_back(PathElement(x, y + 1, South));
                }
                break;
            case '-':
                if (dir != East) {
                    if (x > 0) sol.push_back(PathElement(x - 1, y, West));
                }
                if (dir != West) {
                    if (x < maxX) sol.push_back(PathElement(x + 1, y, East));
                }
                break;
            case '.':
                if (dir == North && y > 0) sol.push_back(PathElement(x, y - 1, North));
                if (dir == South && y < maxY) sol.push_back(PathElement(x, y + 1, South));
                if (dir == West && x > 0) sol.push_back(PathElement(x - 1, y, West));
                if (dir == East && x < maxX) sol.push_back(PathElement(x + 1, y, East));
                break;
        }
        return sol;
    }
};

int main(void)
{
    auto start = chrono::high_resolution_clock::now();


    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");

    string inLine;
    int sol = 0;

    vector<vector<int>> graph;
    vector<vector<vector<bool>>> visited;

    while (getline(file, inLine)) {
        stringstream in(inLine);

        char c;
        vector<int> curLine;
        while (in >> c) {
            curLine.push_back(c);
        }
        visited.push_back(vector<vector<bool>>(curLine.size(), vector<bool>(4, false)));
        graph.push_back(curLine);
    }


    for (int row = 0; row < graph.size(); row++) {
        queue<PathElement> queue;
        queue.push(PathElement(0, row, East));
        visited[row][0][East] = true;

        while (!queue.empty()) {
            PathElement cur = queue.front();
            queue.pop();

            vector<PathElement> next = cur.getNext(graph);

            for (int i = 0; i < next.size(); i++) {
                PathElement toAdd = next[i];
                if (!visited[toAdd.y][toAdd.x][toAdd.dir]) {
                    queue.push(toAdd);
                    visited[toAdd.y][toAdd.x][toAdd.dir] = true;
                }
            }
        }

        int tempSol = 0;
        for (int i = 0; i < visited.size(); i++) {
            for (int j = 0; j < visited[i].size(); j++) {
                tempSol += (visited[i][j][0] || visited[i][j][1] || visited[i][j][2] || visited[i][j][3]) ? 1 : 0;
                visited[i][j][0] = false;
                visited[i][j][1] = false;
                visited[i][j][2] = false;
                visited[i][j][3] = false;
            }
        }

        if (tempSol > sol) {
            sol = tempSol;

            cout << "strating: (" << 0 << ", " << row << ") heading East \t sol: " << sol << endl;

            // for (int i = 0; i < visited.size(); i++) {
            //     for (int j = 0; j < visited[i].size(); j++) {
            //         cout << ((visited[i][j][0] || visited[i][j][1] || visited[i][j][2] || visited[i][j][3]) ? '#' : ' ');
            //         visited[i][j][0] = false;
            //         visited[i][j][1] = false;
            //         visited[i][j][2] = false;
            //         visited[i][j][3] = false;
            //     }
            //     cout << endl;
            // }
        }
    }

    for (int col = 0; col < graph[0].size(); col++) {
        queue<PathElement> queue;
        queue.push(PathElement(col, graph.size() - 1, North));
        visited[graph.size() - 1][col][North] = true;

        while (!queue.empty()) {
            PathElement cur = queue.front();
            queue.pop();

            vector<PathElement> next = cur.getNext(graph);

            for (int i = 0; i < next.size(); i++) {
                PathElement toAdd = next[i];
                if (!visited[toAdd.y][toAdd.x][toAdd.dir]) {
                    queue.push(toAdd);
                    visited[toAdd.y][toAdd.x][toAdd.dir] = true;
                }
            }
        }

        int tempSol = 0;
        for (int i = 0; i < visited.size(); i++) {
            for (int j = 0; j < visited[i].size(); j++) {
                tempSol += (visited[i][j][0] || visited[i][j][1] || visited[i][j][2] || visited[i][j][3]) ? 1 : 0;
                visited[i][j][0] = false;
                visited[i][j][1] = false;
                visited[i][j][2] = false;
                visited[i][j][3] = false;
            }
        }

        if (tempSol > sol) {
            sol = tempSol;

            cout << "strating: (" << col << ", " << (graph.size()-1) << ") heading North \t sol: " << sol << endl;

            // for (int i = 0; i < visited.size(); i++) {
            //     for (int j = 0; j < visited[i].size(); j++) {
            //         cout << ((visited[i][j][0] || visited[i][j][1] || visited[i][j][2] || visited[i][j][3]) ? '#' : ' ');
            //         visited[i][j][0] = false;
            //         visited[i][j][1] = false;
            //         visited[i][j][2] = false;
            //         visited[i][j][3] = false;
            //     }
            //     cout << endl;
            // }
        }
    }

    for (int row = 0; row < graph.size(); row++) {
        queue<PathElement> queue;
        queue.push(PathElement(graph[0].size() - 1, row, West));
        visited[row][graph[0].size() - 1][West] = true;

        while (!queue.empty()) {
            PathElement cur = queue.front();
            queue.pop();

            vector<PathElement> next = cur.getNext(graph);

            for (int i = 0; i < next.size(); i++) {
                PathElement toAdd = next[i];
                if (!visited[toAdd.y][toAdd.x][toAdd.dir]) {
                    queue.push(toAdd);
                    visited[toAdd.y][toAdd.x][toAdd.dir] = true;
                }
            }
        }

        int tempSol = 0;
        for (int i = 0; i < visited.size(); i++) {
            for (int j = 0; j < visited[i].size(); j++) {
                tempSol += (visited[i][j][0] || visited[i][j][1] || visited[i][j][2] || visited[i][j][3]) ? 1 : 0;
                visited[i][j][0] = false;
                visited[i][j][1] = false;
                visited[i][j][2] = false;
                visited[i][j][3] = false;
            }
        }

        if (tempSol > sol) {
            sol = tempSol;

            cout << "strating: (" << (graph.size()-1) << ", " << row << ") heading West \t sol: " << sol << endl;

            // for (int i = 0; i < visited.size(); i++) {
            //     for (int j = 0; j < visited[i].size(); j++) {
            //         cout << ((visited[i][j][0] || visited[i][j][1] || visited[i][j][2] || visited[i][j][3]) ? '#' : ' ');
            //         visited[i][j][0] = false;
            //         visited[i][j][1] = false;
            //         visited[i][j][2] = false;
            //         visited[i][j][3] = false;
            //     }
            //     cout << endl;
            // }
        }
    }

    for (int col = 0; col < graph[0].size(); col++) {
        queue<PathElement> queue;
        queue.push(PathElement(col, 0, South));
        visited[0][col][South] = true;

        while (!queue.empty()) {
            PathElement cur = queue.front();
            queue.pop();

            vector<PathElement> next = cur.getNext(graph);

            for (int i = 0; i < next.size(); i++) {
                PathElement toAdd = next[i];
                if (!visited[toAdd.y][toAdd.x][toAdd.dir]) {
                    queue.push(toAdd);
                    visited[toAdd.y][toAdd.x][toAdd.dir] = true;
                }
            }
        }

        int tempSol = 0;
        for (int i = 0; i < visited.size(); i++) {
            for (int j = 0; j < visited[i].size(); j++) {
                tempSol += (visited[i][j][0] || visited[i][j][1] || visited[i][j][2] || visited[i][j][3]) ? 1 : 0;
                visited[i][j][0] = false;
                visited[i][j][1] = false;
                visited[i][j][2] = false;
                visited[i][j][3] = false;
            }
        }

        if (tempSol > sol) {
            sol = tempSol;

            cout << "strating: (" << col << ", " << 0 << ") heading South \t sol: " << sol << endl;

            // for (int i = 0; i < visited.size(); i++) {
            //     for (int j = 0; j < visited[i].size(); j++) {
            //         cout << ((visited[i][j][0] || visited[i][j][1] || visited[i][j][2] || visited[i][j][3]) ? '#' : ' ');
            //         visited[i][j][0] = false;
            //         visited[i][j][1] = false;
            //         visited[i][j][2] = false;
            //         visited[i][j][3] = false;
            //     }
            //     cout << endl;
            // }
        }
    }

    cout << sol << endl;



    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "time in seconds " << duration.count() << endl;    
}
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

class DjikstrasNode {
    public:
    int y;
    int x;
    Direction dir;
    int walkCnt;
    int totalDist;

    DjikstrasNode(int y, int x, Direction dir, int walkCnt, int totalDist) {
        this->y = y;
        this->x = x;
        this->dir = dir;
        this->walkCnt = walkCnt;
        this->totalDist = totalDist;
    }

    // bool operator<(const DjikstrasNode& other) const {
    //     return (this->totalDist) > other.totalDist;
    // }
};

struct CompareDjikstrasNode {
    bool operator()(DjikstrasNode& n1, DjikstrasNode& n2)
    {
      return n1.totalDist > n2.totalDist;
    }
};

int main(void)
{
    auto start = chrono::high_resolution_clock::now();


    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");

    string in;
    int sol = 0;

    vector<vector<int>> weights;
    vector<vector<vector<vector<int>>>> visited;

    while (getline(file, in)) {
        vector<int> curLine;

        stringstream curString(in);
        char cur;
        while (curString >> cur) {
            curLine.push_back(cur - '0');
        }
        weights.push_back(curLine);
        visited.push_back(vector<vector<vector<int>>>(curLine.size(), vector<vector<int>>(4, vector<int>(10, -1))));
    }

    cout << flush;

    priority_queue<DjikstrasNode, std::vector<DjikstrasNode>, CompareDjikstrasNode> toVisit;

    toVisit.push(DjikstrasNode(0, 1, East, 0, weights[0][1]));
    toVisit.push(DjikstrasNode(1, 0, South, 0, weights[1][0]));
    visited[0][1][East][0] = weights[0][1];
    visited[1][0][South][0] = weights[1][0];

    // cout << weights[0][1] << endl;
    // cout << toVisit.top().x << ", " << toVisit.top().y << ", " << toVisit.top().walkCnt << ", " << toVisit.top().dir << endl;

    while (!toVisit.empty()) {
        DjikstrasNode cur = toVisit.top();
        // cout << cur.totalDist << endl;
        toVisit.pop();

        if (cur.x == ((int)weights[0].size() - 1) && cur.y == ((int)weights.size() - 1) && cur.walkCnt >= 3) {
            sol = cur.totalDist;
            break;
        }

        if ((cur.dir == North && cur.walkCnt < 9) || ((cur.dir == East || cur.dir == West) && cur.walkCnt >= 3)) {
            int newWalkCnt = 0;
            if (cur.dir == North) newWalkCnt = cur.walkCnt + 1;
            bool toAdd = true;
            if (cur.y > 0) {
                int newDist = cur.totalDist + weights[cur.y - 1][cur.x];
                // for (int i = 0; i <= newWalkCnt; i++) {
                if (visited[cur.y - 1][cur.x][North][newWalkCnt] <= newDist && visited[cur.y - 1][cur.x][North][newWalkCnt] != -1) {
                    toAdd = false;
                }
                // }
                if (toAdd) {
                    toVisit.push(DjikstrasNode(cur.y - 1, cur.x, North, newWalkCnt, newDist));
                    visited[cur.y - 1][cur.x][North][newWalkCnt] = newDist;
                }
            }
        }
        if ((cur.dir == South && cur.walkCnt < 9) || ((cur.dir == East || cur.dir == West) && cur.walkCnt >= 3)) {
            int newWalkCnt = 0;
            if (cur.dir == South) newWalkCnt = cur.walkCnt + 1;
            bool toAdd = true;
            if (cur.y < (int)weights.size() - 1) {
                int newDist = cur.totalDist + weights[cur.y + 1][cur.x];
                // for (int i = 0; i <= newWalkCnt; i++) {
                if (visited[cur.y + 1][cur.x][South][newWalkCnt] <= newDist && visited[cur.y + 1][cur.x][South][newWalkCnt] != -1) {
                    toAdd = false;
                }
                // }
                if (toAdd) {
                    toVisit.push(DjikstrasNode(cur.y + 1, cur.x, South, newWalkCnt, newDist));
                    visited[cur.y + 1][cur.x][South][newWalkCnt] = newDist;
                }
            }
        }
        if ((cur.dir == East && cur.walkCnt < 9) || ((cur.dir == North || cur.dir == South) && cur.walkCnt >= 3)) {
            int newWalkCnt = 0;
            if (cur.dir == East) newWalkCnt = cur.walkCnt + 1;
            bool toAdd = true;
            if (cur.x < (int)weights[0].size() - 1) {
                int newDist = cur.totalDist + weights[cur.y][cur.x + 1];
                // for (int i = 0; i <= newWalkCnt; i++) {
                if (visited[cur.y][cur.x + 1][East][newWalkCnt] <= newDist && visited[cur.y][cur.x + 1][East][newWalkCnt] != -1) {
                    toAdd = false;
                }
                // }
                if (toAdd) {
                    toVisit.push(DjikstrasNode(cur.y, cur.x + 1, East, newWalkCnt, newDist));
                    visited[cur.y][cur.x + 1][East][newWalkCnt] = newDist;
                }
            }
        }
        if ((cur.dir == West && cur.walkCnt < 9) || ((cur.dir == North || cur.dir == South) && cur.walkCnt >= 3)) {
            int newWalkCnt = 0;
            if (cur.dir == West) newWalkCnt = cur.walkCnt + 1;
            bool toAdd = true;
            if (cur.x > 0) {
                int newDist = cur.totalDist + weights[cur.y][cur.x - 1];
                // for (int i = 0; i <= newWalkCnt; i++) {
                if (visited[cur.y][cur.x - 1][West][newWalkCnt] <= newDist && visited[cur.y][cur.x - 1][West][newWalkCnt] != -1) {
                    toAdd = false;
                }
                // }
                if (toAdd) {
                    toVisit.push(DjikstrasNode(cur.y, cur.x - 1, West, newWalkCnt, newDist));
                    visited[cur.y][cur.x - 1][West][newWalkCnt] = newDist;
                }
            }
        }
        //     case South:
        //         if (cur.y < weights.size() - 1) {
        //             int newDist = cur.totalDist + weights[cur.y + 1][cur.x];
        //             for (int i = 0; i <= cur.walkCnt + 1; i++) {
        //                 if (visited[cur.y + 1][cur.x][South][i] < newDist && visited[cur.y + 1][cur.x][South][i] != -1) {
        //                     toAdd = false;
        //                 }
        //             }
        //             if (toAdd) {
        //                 toVisit.push(DjikstrasNode(cur.y + 1, cur.x, North, cur.walkCnt + 1, newDist));
        //                 visited[cur.y + 1][cur.x][South][cur.walkCnt + 1] = newDist;
        //             }
        //         }
        //         break;
        //     case East:
        //         if (cur.x < weights[0].size() - 1) {
        //             int newDist = cur.totalDist + weights[cur.y][cur.x + 1];
        //             for (int i = 0; i <= cur.walkCnt + 1; i++) {
        //                 if (visited[cur.y][cur.x + 1][East][i] < newDist && visited[cur.y][cur.x + 1][East][i] != -1) {
        //                     toAdd = false;
        //                 }
        //             }
        //             if (toAdd) {
        //                 toVisit.push(DjikstrasNode(cur.y, cur.x + 1, East, cur.walkCnt + 1, newDist));
        //                 visited[cur.y][cur.x + 1][East][cur.walkCnt + 1] = newDist;
        //             }
        //         }
        //         break;
        //     case West:
        //         if (cur.x > 0) {
        //             int newDist = cur.totalDist + weights[cur.y][cur.x - 1];
        //             for (int i = 0; i <= cur.walkCnt + 1; i++) {
        //                 if (visited[cur.y][cur.x - 1][West][i] < newDist && visited[cur.y][cur.x - 1][West][i] != -1) {
        //                     toAdd = false;
        //                 }
        //             }
        //             if (toAdd) {
        //                 toVisit.push(DjikstrasNode(cur.y, cur.x - 1, West, cur.walkCnt + 1, newDist));
        //                 visited[cur.y][cur.x - 1][West][cur.walkCnt + 1] = newDist;
        //             }
        //         }
        //         break;
        // }
        // }

    }


    // for (int i = 0; i < visited.size(); i++) {
    //     for (int j = 0; j < visited[i].size(); j++) {
    //         cout << "(" << i << ", " << j << ")" << endl;
    //         for (int k = 0; k < visited[i][j].size(); k++) {
    //             cout << k << ": ";
    //             for (int l = 0; l < visited[i][j][k].size(); l++) {
    //                 cout << visited[i][j][k][l] << ","; 
    //             }
    //             cout << "          ";
    //         }
    //         cout << endl; 
    //     }
    // }

    cout << sol << endl;



    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "time in seconds " << duration.count() << endl;    
}
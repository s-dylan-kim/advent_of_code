#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;


int main(void)
{
    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");

    string in;
    int sol = 0;

    vector<vector<int>> map;
    vector<vector<int>> dist;

    int endx;
    int endy;

    int line = 0;

    queue<int> x;
    queue<int> y;

    while (file >> in) {
        stringstream s(in);
        vector<int> cur_line;

        vector<int> dist_line;
        dist_line.resize(in.size(), -1);
        dist.push_back(dist_line);

        char cur;
        int col = 0;
        while (s >> cur) {

            if (cur == 'S') {
                cur = 'a';
            } else if (cur == 'E') {
                endx = line;
                endy = col;
                cur = 'z';
            }

            if (cur == 'a') {
                x.push(line);
                y.push(col);
                dist[line][col] = 0;
            }

            cur_line.push_back(cur);
            col++;
        }

        map.push_back(cur_line);
        line++;
    }


    while (!x.empty()) {
        int curx = x.front();
        int cury = y.front();

        x.pop();
        y.pop();

        if (curx - 1 >= 0 && dist[curx-1][cury] == -1 && map[curx - 1][cury] <= map[curx][cury] + 1) {
            if (curx - 1 == endx && cury == endy) {
                sol = dist[curx][cury] + 1;
                break;
            }
            dist[curx-1][cury] = dist[curx][cury] + 1;
            x.push(curx-1);
            y.push(cury);
        }

        if (curx + 1 < dist.size() && dist[curx+1][cury] == -1 && map[curx+1][cury] <= map[curx][cury] + 1) {
            if (curx + 1 == endx && cury == endy) {
                sol = dist[curx][cury] + 1;
                break;
            }
            dist[curx+1][cury] = dist[curx][cury] + 1;
            x.push(curx+1);
            y.push(cury);
        }

        if (cury - 1 >= 0 && dist[curx][cury-1] == -1 && map[curx][cury-1] <= map[curx][cury] + 1) {
            if (curx == endx && cury - 1 == endy) {
                sol = dist[curx][cury] + 1;
                break;
            }
            dist[curx][cury-1] = dist[curx][cury] + 1;
            x.push(curx);
            y.push(cury-1);
        }

        if (cury + 1 < dist[curx].size() && dist[curx][cury+1] == -1 && map[curx][cury+1] <= map[curx][cury] + 1) {
            if (curx == endx && cury + 1 == endy) {
                sol = dist[curx][cury] + 1;
                break;
            }
            dist[curx][cury+1] = dist[curx][cury] + 1;
            x.push(curx);
            y.push(cury+1);
        }
    }

    cout << sol << endl;    
}
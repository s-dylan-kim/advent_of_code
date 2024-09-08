#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;

struct pair_hash {
    inline std::size_t operator()(const std::pair<int,int> & v) const {
        return v.first^v.second;
    }
};

int main(void)
{
    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");

    string in;
    int sol = 0;

    int maxy = 0;
    unordered_set<pair<int, int>,  pair_hash> blocks;

    while (getline(file, in)) {
        stringstream s(in);

        string burn;
        int x, y;
        int x_new, y_new;

        if (y > maxy) y = maxy;

        s >> x >> y;

        blocks.insert(pair<int, int>(x, y));

        while (s >> burn >> x_new >> y_new) {
            if (y != y_new) {
                int y_min = min(y_new, y);
                int y_max = max(y_new, y);

                for (int i = y_min; i <= y_max; i++) {
                    blocks.insert(pair<int, int>(x, i));
                }

                if (y_max > maxy) maxy = y_max;

                y = y_new;
            } else {
                int x_min = min(x, x_new);
                int x_max = max(x, x_new);

                for (int i = x_min; i <= x_max; i++) {
                    blocks.insert(pair<int, int>(i, y));
                }

                x = x_new;
            }
        }
    }

    int floor_y = maxy + 2;
    
    int curx = 500;
    int cury = 0;

    while (blocks.find(pair<int, int>(500, 0)) == blocks.end()) {
        
        if (cury == floor_y - 1) {
            blocks.insert(pair<int, int>(curx, cury));
            sol++;
            curx = 500;
            cury = 0;
        }

        if (blocks.find(pair<int, int>(curx, cury+1)) == blocks.end()) {
            cury++;
        } else if (blocks.find(pair<int, int>(curx-1, cury+1)) == blocks.end()) {
            curx--;
            cury++;
        } else if (blocks.find(pair<int, int>(curx+1, cury+1)) == blocks.end()) {
            curx++;
            cury++;
        } else {
            blocks.insert(pair<int, int>(curx, cury));
            sol++;
            curx = 500;
            cury = 0;
        }
    }

    cout << sol << endl;    
}
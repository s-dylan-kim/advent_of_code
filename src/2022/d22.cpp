#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <ctype.h>
using namespace std;


int main(void)
{
    auto start = chrono::high_resolution_clock::now();


    ifstream file("/mnt/c/Users/sdyla/Advent/input.txt");

    string in;
    int sol = 0;

    vector<vector<int>> map;

    vector<int> start_x;
    vector<int> end_x;

    vector<int> start_y;
    vector<int> end_y;

    vector<int> lenx;
    vector<int> leny;

    int max_x = 0;

    while (getline(file, in)) {
        stringstream s(in);

        char cur;

        vector<int> cur_line;

        while (s >> noskipws >> cur) {
            switch (cur)
            {
                case ' ':
                    cur_line.push_back(-1);
                    break;
                case '.':
                    cur_line.push_back(0);
                    break;
                case '#':
                    cur_line.push_back(1);
                    break;
            }
        }

        for (int i = 0; i < cur_line.size(); i++) {
            cout << cur_line[i] << ", ";
        }
        cout << endl;

        if (cur_line.size() > max_x) max_x = cur_line.size();

        map.push_back(cur_line);
    }


    for (int i = 0; i < map.size(); i++) {
        int size = 0;
        bool found = false;
        int max = 0;
        for (int j = 0; j < map[i].size(); j++) {
            if (!found && map[i][j] != -1) {
                start_x.push_back(j);
                found = true;
            }
            if (map[i][j] != -1) {
                max = j;
                size++;
            }
        }
        end_x.push_back(max);
        lenx.push_back(size);
    }

    for (int i = 0; i < max_x; i++) {
        int size = 0;
        bool found = false;
        int max = 0;
        for (int j = 0; j < map.size(); j++) {
            if (!found && map[j].size() > i && map[j][i] != -1) {
                start_y.push_back(j);
                // cout << j;
                found = true;
            }
            if (map[j].size() > i && map[j][i] != -1) {
                max = j;
                size++;
            }
        }
        leny.push_back(size);
        end_y.push_back(max);
        // cout << " " << max << " " << size << endl;
    }

    // cout << "test3" << endl;


    int cury = 0;
    int curx;

    for (int i = 0; i < map[0].size(); i++) {
        // cout << map[0][i] << endl;
        if (map[0][i] != -1) {
            curx = i;
            break;
        }
    }

    ifstream file2("/mnt/c/Users/sdyla/Advent/input2.txt");

    int len = 0;
    string len_str = "";
    int dir = 0;
    char turn = ' ';
    char cur = ' ';

    while(file2 >> cur) {
        if (cur >= '0' && cur <= '9') {
            len_str += cur;
        } else {
            turn = cur;
            // cout << curx << ", " << cury << ", " << len_str << ", " << dir << endl;;
            len = stoi(len_str);
            len_str = "";

            int new_x = curx;
            int new_y = cury;

            int mod_val;

            if (dir < 2) mod_val = lenx[new_y];
            else mod_val = leny[new_x]; 

            for (int i = 1; i <= len; i++) {
                int temp_x = curx;
                int temp_y = cury;

                switch (dir) {
                    case 0:
                        temp_x += i;
                        if (temp_x > end_x[temp_y]) temp_x = start_x[temp_y] + (temp_x - end_x[temp_y] - 1);
                        break;
                    case 1:
                        temp_y += i;
                        // cout << end_y[temp_x] << ",| " << start_y[temp_x] << endl;
                        if (temp_y > end_y[temp_x]) temp_y = start_y[temp_x] + (temp_y - end_y[temp_x] - 1);
                        break;
                    case 2:
                        temp_x -= i;
                        if (temp_x < start_x[temp_y]) temp_x = end_x[temp_y] - (start_x[temp_y] - temp_x - 1);
                        break;
                    case 3:
                        temp_y -= i;
                        if (temp_y < start_y[temp_x]) temp_y = end_y[temp_x] - (start_y[temp_x] - temp_y - 1);
                        break;
                }

                // cout << temp_y << ", " << temp_x << endl;

                if (map[temp_y][temp_x]) {
                    if (map[temp_y][temp_x] == -1) {
                        cout << "WARNING @: " << temp_x << ", " << temp_y << endl;
                        return -1;
                    }
                    // cout << "TRIGGERED "  << temp_x << ", " << temp_y << ", " << dir << endl;
                    break;
                }

                new_x = temp_x;
                new_y = temp_y;
            }
            curx = new_x;
            cury = new_y;

            switch (turn)
            {
                case 'R':
                    dir = (dir + 1) % 4;
                    break;
                case 'L':
                    dir = (dir + 3) % 4; 
                    break;
            }
        }
    }

    len = stoi(len_str);

    int new_x = curx;
    int new_y = cury;

    int mod_val;

    if (dir < 2) mod_val = lenx[new_y];
    else mod_val = leny[new_x]; 

    for (int i = 1; i <= len % mod_val; i++) {
        int temp_x = curx;
        int temp_y = cury;

        switch (dir) {
            case 0:
                temp_x += i;
                if (temp_x > end_x[temp_y]) temp_x = start_x[temp_y] + (temp_x - end_x[temp_y] - 1);
                break;
            case 1:
                temp_y += i;
                if (temp_y > end_y[temp_x]) temp_y = start_y[temp_x] + (temp_y - end_y[temp_x] - 1);
                break;
            case 2:
                temp_x -= i;
                if (temp_x < start_x[temp_y]) temp_x = end_x[temp_y] - (start_x[temp_y] - temp_x - 1);
                break;
            case 3:
                temp_y -= i;
                if (temp_y < start_y[temp_x]) temp_y = end_y[temp_x] - (start_y[temp_x] - temp_y - 1);
                break;
        }

        if (map[temp_y][temp_x]) {
            if (map[temp_y][temp_x] == -1) {
                cout << "WARNING @: " << temp_x << ", " << temp_y << endl;
                return -1;
            }
            break;
        }

        new_x = temp_x;
        new_y = temp_y;
    }
    curx = new_x;
    cury = new_y;


    cout << curx << ", " << cury << ", " << dir << endl;



    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "time in seconds " << duration.count() << endl;    
}
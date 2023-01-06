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


    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");

    string in;
    int sol = 0;

    vector<vector<int>> map;
    vector<vector<int>> top(50, vector<int>());
    vector<vector<int>> bottom;

    vector<int> start_x;
    vector<int> end_x;

    vector<int> start_y;
    vector<int> end_y;

    vector<int> lenx;
    vector<int> leny;

    for (int i = 0; i < 50; i++) {
        getline(file, in);

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

        map.push_back(cur_line);

    }

    for (int i = 0; i < 50; i++) {
        getline(file, in);

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

        bottom.push_back(cur_line);
    }

    top.resize(50);

    for (int i = 0; i < 50; i++) {
        getline(file, in);

        stringstream s(in);

        char cur;

        int idx = 0;

        while (s >> noskipws >> cur) {
            switch (cur)
            {
                case ' ':
                    top[idx].push_back(-1);
                    break;
                case '.':
                    top[idx].push_back(0);
                    break;
                case '#':
                    top[idx].push_back(1);
                    break;
            }
            idx++;
        }
    }


    int cury = 0;
    int curx = 0;

    // cout << "WOOO" << endl;

    ifstream file2("/mnt/c/Users/sdyla/Advent/input_long2.txt");

    int len = 0;
    string len_str = "";
    int dir = 0;
    char turn = ' ';
    char cur = ' ';
    bool on_top = false;
    bool on_bottom = false;

    while(file2 >> cur) {
        


        if (cur >= '0' && cur <= '9') {
            len_str += cur;
        } else {
            turn = cur;
            // cout << curx << ", " << cury << ", " << len_str << ", " << dir << endl;;
            len = stoi(len_str);
            
            cout << "on top?:" << on_top << " on bottom?:" << on_bottom << " (" << curx << "," << cury << ") facing:" << dir << " traveling:" << len << " then turning:" << cur << endl; 
            
            len_str = "";

            int new_x = curx;
            int new_y = cury;
            bool new_on_top = on_top;
            bool new_on_bottom = on_bottom;
            int new_dir = dir;


            for (int i = 1; i <= len; i++) {
                int temp_x = curx;
                int temp_y = cury;
                bool temp_on_top = false;
                bool temp_on_bottom = false;
                int temp_dir = dir;

                int temp_store_x;
                int temp_store_y;


                if (on_top) {
                    temp_on_top = true;
                    switch (dir) {
                        case 0:
                            temp_x += i;
                            if (temp_x > 49) {
                                temp_store_x = temp_x;
                                temp_store_y = temp_y;
                                temp_on_top = false;
                                temp_x = 50 + temp_store_y;
                                temp_y = temp_store_x - 50;
                                temp_dir = 1;
                            }
                            break;
                        case 1:
                            temp_y -= i;
                            // cout << end_y[temp_x] << ",| " << start_y[temp_x] << endl;
                            if (temp_y < 0) {
                                temp_store_x = temp_x;
                                temp_store_y = temp_y;
                                temp_on_top = false;
                                temp_x = temp_store_x;
                                temp_y = ((temp_store_y + 1) * -1);
                                temp_dir = 1;
                            }
                            break;
                        case 2:
                            temp_x -= i;
                            if (temp_x < 0) {
                                temp_store_x = temp_x;
                                temp_store_y = temp_y;
                                temp_on_top = false;
                                temp_x = 150 + (49 - temp_store_y);
                                temp_y = ((temp_store_x + 1) * -1);

                                temp_dir = 1;
                            }
                            break;
                        case 3:
                            temp_y += i;
                            if (temp_y > 49) {
                                temp_store_x = temp_x;
                                temp_store_y = temp_y;
                                temp_on_top = false;
                                temp_x = 100 + (49 - temp_store_x);
                                temp_y = temp_store_y - 50;
                                temp_dir = 1;
                            }
                            break;
                    }
                } else if (on_bottom) {
                    temp_on_bottom = true;
                    switch (dir) {
                        case 0:
                            temp_x += i;
                            if (temp_x > 49) {
                                temp_store_x = temp_x;
                                temp_store_y = temp_y;
                                temp_on_bottom = false;
                                temp_y = 49 - (temp_store_x - 50);
                                temp_x = 50 + temp_y;
                                temp_dir = 3;
                            }
                            break;
                        case 1:
                            temp_y -= i;
                            if (temp_y < 0) {
                                temp_store_x = temp_x;
                                temp_store_y = temp_y;
                                temp_on_bottom = false;
                                temp_x = temp_store_x;
                                temp_y = 49 - ((temp_store_y + 1) * -1);
                                temp_dir = 3;
                            }
                            break;
                        case 2:
                            temp_x -= i;
                            if (temp_x < 0) {
                                temp_store_x = temp_x;
                                temp_store_y = temp_y;
                                temp_on_bottom = false;
                                temp_x = 150 + (49 - temp_store_y);
                                temp_y = 49 - ((temp_store_x + 1) * -1);

                                temp_dir = 3;
                            }
                            break;
                        case 3:
                            temp_y += i;
                            // cout << end_y[temp_x] << ",| " << start_y[temp_x] << endl;
                            if (temp_y > 49) {
                                temp_store_x = temp_x;
                                temp_store_y = temp_y;
                                temp_on_bottom = false;
                                temp_x = 100 + (49 - temp_store_x);
                                temp_y = 49 - (temp_store_y - 50);
                                temp_dir = 3;
                            }
                            break;
                    }
                } else {
                    switch (dir) {
                        case 0:
                            temp_x += i;
                            if (temp_x > 199) temp_x = temp_x - 199;
                            break;
                        case 1:
                            temp_y += i;
                            // cout << end_y[temp_x] << ",| " << start_y[temp_x] << endl;
                            if (temp_y > 49) {
                                temp_on_bottom = true;

                                if (temp_x < 50) {
                                    temp_store_x = temp_x;
                                    temp_store_y = temp_y;
                                    temp_x = temp_store_x;
                                    temp_y = temp_store_y - 50;
                                    temp_dir = 3;
                                } else if (temp_x < 100) {
                                    temp_store_x = temp_x;
                                    temp_store_y = temp_y;
                                    temp_y = temp_store_x - 50;
                                    temp_x = 49 - (temp_store_y - 50);
                                    temp_dir = 2;
                                } else if (temp_x < 150) {
                                    temp_store_x = temp_x;
                                    temp_store_y = temp_y;
                                    temp_x = 49 - (temp_store_x - 100);
                                    temp_y = 49 - (temp_store_y - 50);
                                    temp_dir = 1;
                                } else {
                                    temp_store_x = temp_x;
                                    temp_store_y = temp_y;
                                    temp_x = temp_store_y - 50;
                                    temp_y = 49 - (temp_store_x - 150);
                                    temp_dir = 0;
                                }
                            }
                            break;
                        case 2:
                            temp_x -= i;
                            if (temp_x < 0) temp_x = 200 + temp_x;
                            break;
                        case 3:
                            temp_y -= i;
                            if (temp_y < 0) {
                                temp_on_top = true;

                                if (temp_x < 50) {
                                    temp_store_x = temp_x;
                                    temp_store_y = temp_y;
                                    temp_x = temp_store_x;
                                    temp_y = (temp_store_y + 1) * -1 ;
                                    temp_dir = 3;
                                } else if (temp_x < 100) {
                                    temp_store_x = temp_x;
                                    temp_store_y = temp_y;
                                    temp_y = temp_store_x - 50;
                                    temp_x = 49 - ((temp_store_y + 1) * -1);
                                    temp_dir = 2;
                                } else if (temp_x < 150) {
                                    temp_store_x = temp_x;
                                    temp_store_y = temp_y;
                                    temp_x = 49 - (temp_store_x - 100);
                                    temp_y = 49 - (((temp_store_y + 1) * -1));
                                    // cout << temp_x << ", " <<  temp_y << endl;
                                    temp_dir = 1;
                                } else {
                                    temp_store_x = temp_x;
                                    temp_store_y = temp_y;
                                    temp_x = (temp_store_y + 1) * -1;
                                    // cout << temp_x << endl;
                                    temp_y = 49 - (temp_store_x - 150);
                                    temp_dir = 0;
                                }
                            }
                            break;
                    }
                }

                // cout << temp_y << ", " << temp_x << endl;

                if ((temp_on_bottom && bottom[temp_y][temp_x]) || (temp_on_top && top[temp_y][temp_x]) || (!temp_on_top && !temp_on_bottom && map[temp_y][temp_x])) {
                    // cout << "TRIGGERED "  << temp_x << ", " << temp_y << ", " << dir << endl;
                    break;
                }

                new_x = temp_x;
                new_y = temp_y;
                new_on_bottom = temp_on_bottom;
                new_on_top = temp_on_top;
                new_dir = temp_dir;
            }
            curx = new_x;
            cury = new_y;
            on_top = new_on_top;
            on_bottom = new_on_bottom;
            dir = new_dir;

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

    cout << "done with main loop" << endl;

    len = stoi(len_str);
    len_str = "";

    int new_x = curx;
    int new_y = cury;
    bool new_on_top = on_top;
    bool new_on_bottom = on_bottom;
    int new_dir = dir;


    for (int i = 1; i <= len; i++) {
        int temp_x = curx;
        int temp_y = cury;
        bool temp_on_top = false;
        bool temp_on_bottom = false;
        int temp_dir = dir;

        int temp_store_x;
        int temp_store_y;


        if (on_top) {
            temp_on_top = true;
            switch (dir) {
                case 0:
                    temp_x += i;
                    if (temp_x > 49) {
                        temp_store_x = temp_x;
                        temp_store_y = temp_y;
                        temp_on_top = false;
                        temp_x = 50 + temp_store_y;
                        temp_y = temp_store_x - 50;
                        temp_dir = 1;
                    }
                    break;
                case 1:
                    temp_y -= i;
                    // cout << end_y[temp_x] << ",| " << start_y[temp_x] << endl;
                    if (temp_y < 0) {
                        temp_store_x = temp_x;
                        temp_store_y = temp_y;
                        temp_on_top = false;
                        temp_x = temp_store_x;
                        temp_y = ((temp_store_y + 1) * -1);
                        temp_dir = 1;
                    }
                    break;
                case 2:
                    temp_x -= i;
                    if (temp_x < 0) {
                        temp_store_x = temp_x;
                        temp_store_y = temp_y;
                        temp_on_top = false;
                        temp_x = 150 + (49 - temp_store_y);
                        temp_y = ((temp_store_x + 1) * -1);

                        temp_dir = 1;
                    }
                    break;
                case 3:
                    temp_y += i;
                    if (temp_y > 49) {
                        temp_store_x = temp_x;
                        temp_store_y = temp_y;
                        temp_on_top = false;
                        temp_x = 100 + (49 - temp_store_x);
                        temp_y = temp_store_y - 50;
                        temp_dir = 1;
                    }
                    break;
            }
        } else if (on_bottom) {
            temp_on_bottom = true;
            switch (dir) {
                case 0:
                    temp_x += i;
                    if (temp_x > 49) {
                        temp_store_x = temp_x;
                        temp_store_y = temp_y;
                        temp_on_bottom = false;
                        temp_y = 49 - (temp_store_x - 50);
                        temp_x = 50 + temp_y;
                        temp_dir = 3;
                    }
                    break;
                case 1:
                    temp_y -= i;
                    if (temp_y < 0) {
                        temp_store_x = temp_x;
                        temp_store_y = temp_y;
                        temp_on_bottom = false;
                        temp_x = temp_store_x;
                        temp_y = 49 - ((temp_store_y + 1) * -1);
                        temp_dir = 3;
                    }
                    break;
                case 2:
                    temp_x -= i;
                    if (temp_x < 0) {
                        temp_store_x = temp_x;
                        temp_store_y = temp_y;
                        temp_on_bottom = false;
                        temp_x = 150 + (49 - temp_store_y);
                        temp_y = 49 - ((temp_store_x + 1) * -1);

                        temp_dir = 3;
                    }
                    break;
                case 3:
                    temp_y += i;
                    // cout << end_y[temp_x] << ",| " << start_y[temp_x] << endl;
                    if (temp_y > 49) {
                        temp_store_x = temp_x;
                        temp_store_y = temp_y;
                        temp_on_bottom = false;
                        temp_x = 100 + (49 - temp_store_x);
                        temp_y = 49 - (temp_store_y - 50);
                        temp_dir = 3;
                    }
                    break;
            }
        } else {
            switch (dir) {
                case 0:
                    temp_x += i;
                    if (temp_x > 199) temp_x = temp_x - 199;
                    break;
                case 1:
                    temp_y += i;
                    // cout << end_y[temp_x] << ",| " << start_y[temp_x] << endl;
                    if (temp_y > 49) {
                        temp_on_bottom = true;

                        if (temp_x < 50) {
                            temp_store_x = temp_x;
                            temp_store_y = temp_y;
                            temp_x = temp_store_x;
                            temp_y = temp_store_y - 50;
                            temp_dir = 3;
                        } else if (temp_x < 100) {
                            temp_store_x = temp_x;
                            temp_store_y = temp_y;
                            temp_y = temp_store_x - 50;
                            temp_x = 49 - (temp_store_y - 50);
                            temp_dir = 2;
                        } else if (temp_x < 150) {
                            temp_store_x = temp_x;
                            temp_store_y = temp_y;
                            temp_x = 49 - (temp_store_x - 100);
                            temp_y = 49 - (temp_store_y - 50);
                            temp_dir = 1;
                        } else {
                            temp_store_x = temp_x;
                            temp_store_y = temp_y;
                            temp_x = temp_store_y - 50;
                            temp_y = 49 - (temp_store_x - 150);
                            temp_dir = 0;
                        }
                    }
                    break;
                case 2:
                    temp_x -= i;
                    if (temp_x < 0) temp_x = 200 + temp_x;
                    break;
                case 3:
                    temp_y -= i;
                    if (temp_y < 0) {
                        temp_on_top = true;

                        if (temp_x < 50) {
                            temp_store_x = temp_x;
                            temp_store_y = temp_y;
                            temp_x = temp_store_x;
                            temp_y = (temp_store_y + 1) * -1 ;
                            temp_dir = 3;
                        } else if (temp_x < 100) {
                            temp_store_x = temp_x;
                            temp_store_y = temp_y;
                            temp_y = temp_store_x - 50;
                            temp_x = 49 - ((temp_store_y + 1) * -1);
                            temp_dir = 2;
                        } else if (temp_x < 150) {
                            // cout << temp_x << ", " << temp_y << endl;
                            temp_store_x = temp_x;
                            temp_store_y = temp_y;
                            temp_x = 49 - (temp_store_x - 100);
                            temp_y = 49 - (((temp_store_y + 1) * -1));
                            temp_dir = 1;
                        } else {
                            temp_store_x = temp_x;
                            temp_store_y = temp_y;
                            temp_x = (temp_store_y + 1) * -1;
                            temp_y = 49 - (temp_store_x - 150);
                            temp_dir = 0;
                        }
                    }
                    break;
            }
        }

        // cout << temp_y << ", " << temp_x << endl;

        if ((temp_on_bottom && bottom[temp_y][temp_x]) || (temp_on_top && top[temp_y][temp_x]) || (!temp_on_top && !temp_on_bottom && map[temp_y][temp_x])) {
            // cout << "TRIGGERED "  << temp_x << ", " << temp_y << ", " << dir << endl;
            break;
        }

        new_x = temp_x;
        new_y = temp_y;
        new_on_bottom = temp_on_bottom;
        new_on_top = temp_on_top;
        new_dir = temp_dir;
    }
    curx = new_x;
    cury = new_y;
    on_top = new_on_top;
    on_bottom = new_on_bottom;
    dir = new_dir;


    cout << curx << ", " << cury << ", " << dir << endl;



    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "time in seconds " << duration.count() << endl;    
}
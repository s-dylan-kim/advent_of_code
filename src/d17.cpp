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

    char cur;
    int sol = 0;

    vector<vector<vector<int>>> patterns {
        {
            {1, 1, 1, 1},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
            
        }, {
            {0, 1, 0, 0},
            {1, 1, 1, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 0}
        }, {
            {1, 1, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 0}
        }, {
            {1, 0, 0, 0},
            {1, 0, 0, 0},
            {1, 0, 0, 0},
            {1, 0, 0, 0}
        }, {
            {1, 1, 0, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        }
    };

    vector<vector<pair<int, int>>> bottom {
        {
            {0, 0},
            {0, 1},
            {0, 2},
            {0, 3}
        }, {
            {1, 0},
            {0, 1},
            {1, 2}
        }, {
            {0, 0},
            {0, 1},
            {0, 2}
        }, {
            {0, 0}
        }, {
            {0, 0},
            {0, 1}
        }
    };

    vector<vector<pair<int, int>>> left {
        {
            {0, 0},
        }, {
            {1, 0},
            {0, 1},
            {2, 1}
        }, {
            {0, 0},
            {1, 2},
            {2, 2}
        }, {
            {0, 0},
            {1, 0},
            {2, 0},
            {3, 0}
        }, {
            {0, 0},
            {1, 0}
        }
    };

    vector<vector<pair<int, int>>> right {
        {
            {0, 3},
        }, {
            {1, 2},
            {0, 1},
            {2, 1}
        }, {
            {0, 2},
            {1, 2},
            {2, 2}
        }, {
            {0, 0},
            {1, 0},
            {2, 0},
            {3, 0}
        }, {
            {0, 1},
            {1, 1}
        }
    };

    vector<int> width {4, 3, 3, 1, 2};

    vector<bool> left_wind;

    while (file >> cur) {
        left_wind.push_back(cur == '<');
    }

    int top_height = -1;
    int wind_idx = 0;

    vector<vector<bool>> image(7, vector<bool>(7, false));

    for (int i = 0; i < 1720+1605; i++) {
        int x = 2;
        int y = top_height + 4;

        bool falling = true;
        bool cur_wind = true;

        while (falling) {
            // cout << x << ", " << y << endl;

            bool move_allowed = true;

            if (!cur_wind) {
                for (int bottom_it = 0; bottom_it < bottom[i % 5].size(); bottom_it++) {
                    pair<int, int> cur = bottom[i % 5][bottom_it];
                    if (cur.first + y - 1 < 0 || image[cur.first + y - 1][cur.second + x]) {
                        falling = false;

                        // update blocks
                        for (int i_x = 0; i_x < 4 && i_x + x < 7; i_x++) {
                            for (int i_y = 0; i_y < 4; i_y++) {
                                if (patterns[i % 5][i_y][i_x] && !image[i_y + y][i_x + x]) {
                                    image[i_y + y][i_x + x] = true;
                                    if (i_y + y > top_height) top_height = i_y + y;
                                }
                            }
                        }
                        break;
                    }
                }
                y--;
                cur_wind = true;
            } else {
                if(left_wind[wind_idx]) {
                    for (int left_it = 0; left_it < left[i % 5].size(); left_it++) {
                        pair<int, int> cur = left[i % 5][left_it];
                        if (cur.second + x - 1 < 0 || image[cur.first + y][cur.second + x - 1]) {
                            move_allowed = false;
                            break;
                        }
                    }
                    if (move_allowed) x--;
                } else {
                    for (int right_it = 0; right_it < right[i % 5].size(); right_it++) {
                        pair<int, int> cur = right[i % 5][right_it];
                        if (cur.second + x + 1 >= 7 || image[cur.first + y][cur.second + x + 1]) {
                            move_allowed = false;
                            break;
                        }
                    }
                    if (move_allowed) x++;
                }

                wind_idx++;
                if (wind_idx >= left_wind.size()) wind_idx = wind_idx % left_wind.size(); 
                cur_wind = false;
            }
        }

        while (image.size() < top_height + 8) {
            image.push_back(vector<bool>(7, false));
        }

        if (i % 5 == 0 && wind_idx % left_wind.size() == 13) {// && wind_idx % left_wind.size() == 0
            cout << i << ":" << wind_idx % left_wind.size() << endl;
            for (int i = image.size()-1; i >= image.size() - 15; i--) {
                for (int j = 0; j < image[i].size(); j++) {
                    cout << (image[i][j] ? "#" : ".");
                }
                cout << endl;
            }
            cout << "max height: " << top_height << endl;
        }
        
    }

    cout << top_height + 1 << endl;

}
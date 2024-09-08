#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <string>
using namespace std;


int main(void)
{
    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");

    string in;
    int sol = 0;

    vector<vector<int>> map;

    while (file >> in) {
        vector<int> cur_map;
        
        stringstream s(in);

        char cur;
        while (s >> cur) {
            int cur_int = cur;

            cur_map.push_back(cur_int - '0');
        }

        map.push_back(cur_map);
    }

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }

    // cout << map.size() << ", " << map[0].size() << endl;

    vector<vector<bool>> seen;

    for (int i = 0; i < map.size(); i++) {
        vector<bool> cur_vec;
        for (int j = 0; j < map[i].size(); j++) {
            cur_vec.push_back(false);
        }
        seen.push_back(cur_vec);
    }

    // cout << seen.size() << ", " << seen[0].size() << endl;

    // for (int i = 0; i < seen.size(); i++) {
    //     seen[i][0] = true;
    //     seen[i][seen[i].size()-1] = true;
    //     int max;
        
    //     max = map[i][0];
    //     for (int j = 1; j < seen[i].size(); j++) {
    //         if (map[i][j] > max)  {
    //             seen[i][j] = true;
    //             max = map[i][j];
    //         }
    //     }

    //     max = map[i][seen[i].size()-1];
    //     for (int j = seen[i].size()-2; j >= 0; j--) {
    //         if (map[i][j] > max)  {
    //             seen[i][j] = true;
    //             max = map[i][j];
    //         }
    //     }
    // }

    // for (int i = 0; i < seen[0].size(); i++) {
    //     seen[0][i] = true;
    //     seen[seen.size()-1][i] = true;


    //     int max;
        
    //     max = map[0][i];
    //     for (int j = 1; j < seen.size(); j++) {
    //         if (map[j][i] > max)  {
    //             seen[j][i] = true;
    //             max = map[j][i];
    //         }
    //     }

    //     max = map[seen.size()-1][i];
    //     for (int j = seen.size()-2; j >= 0; j--) {
    //         // cout << j << ", " << i << ": " << max << " ";
    //         if (map[j][i] > max)  {
    //             // cout << map[j][i] << "triggered";
    //             seen[j][i] = true;
    //             max = map[j][i];
    //         }
    //         // cout << endl;
    //     }
    // }
    int max = 0;

    for (int i = 0; i < seen.size(); i++) {
        for (int j = 0; j < seen[i].size(); j++) {
            // cout << i << ", " << j << ": ";

            int total = 1;
            
            int cur = 1;
            for (; j + cur < seen[i].size(); cur++) {
                if (map[i][j] <= map[i][j+cur]) break;
            }
            if (j + cur == seen[i].size()) cur--;
            total *= cur;
            if (i == 7 && j == 48) {
                cout << cur << " ";
            }


            cur = 1;
            for (; j - cur >= 0; cur++) {
                if (map[i][j] <= map[i][j-cur]) break;
            }
            if (j - cur == -1) cur--;
            total *= cur;
            if (i == 7 && j == 48) {
                cout << cur << " ";
            }

            cur = 1;
            for (; i + cur < seen[i].size(); cur++) {
                if (map[i][j] <= map[i+cur][j]) break;
            }
            if (i + cur== seen.size()) cur--;
            total *= cur;
            if (i == 7 && j == 48) {
                cout << cur << " ";
            }

            cur = 1;
            for (; i - cur >= 0; cur++) {
                if (map[i][j] <= map[i-cur][j]) break;
            }
            if (i - cur == -1) cur--;
            total *= cur;
            if (i == 7 && j == 48) {
                cout << cur << " ";
            }

            if (total > max) max = total;
            // cout << endl;
        }
    }


    // for (int i = 0; i < seen.size(); i++) {
    //     for (int j = 0; j < seen[i].size(); j++) {
    //         cout << seen[i][j] << " ";
    //         if (seen[i][j]) sol++;
    //     }
    //     cout << endl;
    // }

    // cout << sol << endl;    
    cout << max << endl;
}
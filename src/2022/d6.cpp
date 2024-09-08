#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;


int main(void)
{
    ifstream file("/mnt/c/Users/sdyla/Advent/input.txt");

    char in;
    int sol = 0;
    vector<char> cur;

    while (file >> in) {
        if (cur.size() < 13) {
            cur.push_back(in);
        } else {
            bool found = false;
            // cout << in << endl;
            for(int i = 0; i < 13; i++) {
                if (in == cur[i]) {
                    // cout << "flagged here" << endl;
                    found = true;
                }
            }
            for(int i = 0; i < 13; i++) {
                for(int j = 1; j < 13; j++) {
                    if (cur[i] == cur[(i + j) % 14]) {
                        // cout << "flagged there" << i << j << endl;
                        found = true;
                    }
                }
            }
            if (!found) break;

            cur[sol%13] = in;
        }
        sol++;
    }
    sol++;

    cout << sol << endl;    
}
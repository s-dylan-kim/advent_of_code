#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
// #define DEBUG
using namespace std;



int compare (vector<int> left, vector<int> right, int li, int ri) {
    while (li < left.size() && ri < right.size()) {
        if (left[li] == -2 && right[ri] == -2) return 0;
        if (left[li] == -2 && right[ri] != -2) return -1;
        if (left[li] != -2 && right[ri] == -2) return 1;

        if (left[li] == -1 && right[ri] == -1) {
            #ifdef DEBUG
            cout << "comparing: arrays" << endl;
            #endif

            int comp_val = compare(left, right, li + 1, ri + 1);
            if (comp_val) return comp_val;
            
            stack<int> temp;
            temp.push(0);


            li++;
            while (!temp.empty()) {
                if(left[li] == -1) {
                    temp.push(0);
                } else if (left[li] == -2) {
                    temp.pop();
                }
                li++;
            }

            temp.push(0);
            ri++;
            while (!temp.empty()) {
                if(right[ri] == -1) {
                    temp.push(0);
                } else if (right[ri] == -2) {
                    temp.pop();
                }
                ri++;
            }

        } else if (left[li] != -1 && right[ri] != -1) {
            #ifdef DEBUG
            cout << "comparing: " << left[li] << ", " << right[ri] << endl;
            #endif
            if (left[li] < right[ri]) return -1;
            else if (left[li] > right[ri]) return 1;
            li++;
            ri++;
        } else {
            if (left[li] == -1) {
                #ifdef DEBUG
                cout << "left is array" << endl;
                #endif
                vector<int> temp_vec;
                temp_vec.push_back(right[ri]);
                temp_vec.push_back(-2);
                int comp_val = compare(left, temp_vec, li + 1, 0);

                if (comp_val) return comp_val;
                
                stack<int> temp;
                temp.push(0);


                li++;
                while (!temp.empty()) {
                    if(left[li] == -1) {
                        temp.push(0);
                    } else if (left[li] == -2) {
                        temp.pop();
                    }
                    li++;
                }

                ri++;
            } else {
                #ifdef DEBUG
                cout << "right is array" << endl;
                #endif
                vector<int> temp_vec;
                temp_vec.push_back(left[li]);
                temp_vec.push_back(-2);
                int comp_val = compare(temp_vec, right, 0, ri + 1);

                if (comp_val) return comp_val;
                
                stack<int> temp;
                temp.push(0);
                ri++;
                while (!temp.empty()) {
                    if(right[ri] == -1) {
                        temp.push(0);
                    } else if (right[ri] == -2) {
                        temp.pop();
                    }
                    ri++;
                }

                li++;
            }
        }
    }
    return 0;
}

bool compare_help (vector<int> left, vector<int> right) {
    return compare(left, right, 1, 1) == -1;
}


int main(void)
{
    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");

    string left_str;
    string right_str;
    string burn;
    int sol = 0;

    int x = 0;
    int pair_num = 1;

    vector<vector<int>> packets;
    

    while (getline(file, left_str) && getline(file, right_str)) {

        stringstream ls(left_str);
        stringstream rs(right_str);

        vector<int> left;
        vector<int> right;

        string cur;
        while (ls >> cur) {
            if (cur == "[") {
                left.push_back(-1);
            }
            else if (cur == "]") {
                left.push_back(-2);
            }
            else {
                left.push_back(stoi(cur));
            }
        }

        while (rs >> cur) {
            if (cur == "[") {
                right.push_back(-1);
            }
            else if (cur == "]") {
                right.push_back(-2);
            }
            else {
                right.push_back(stoi(cur));
            }
        }
        
        packets.push_back(left);
        packets.push_back(right);
        // for (int i = 0; i < left.size(); i++) {
        //     cout << left[i] << " ";
        // }
        // cout << endl;
        

        getline(file, burn);
    }


    vector<int> pac1{-1, -1, 2, -2, -2};
    vector<int> pac2{-1, -1, 6, -2, -2};
    packets.push_back(pac1);
    packets.push_back(pac2);

    sort(packets.begin(), packets.end(), compare_help);

    for (int i = 0; i < packets.size(); i++) {
        cout << (i+1) << ": ";
        for (int j = 0; j < packets[i].size(); j++) {
            cout << packets[i][j] << " ";
        }
        cout << endl;
    }


    cout << sol << endl;    
}

// 90, 119, 
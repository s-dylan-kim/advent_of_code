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


int nextVal(vector<int>& input) {
    bool flag = true;

    vector<int> diffs;

    for (int i = 1; i < input.size(); i++) {
        diffs.push_back(input[i] - input[i-1]);
        if (input[i] != input[i-1]) {
            flag = false;
        }
    }
    if (flag) return input[0];
    else {
        return input[input.size() - 1] + nextVal(diffs);
    }
}

int prevVal(vector<int>& input) {
    bool flag = true;

    vector<int> diffs;

    for (int i = 1; i < input.size(); i++) {
        diffs.push_back(input[i] - input[i-1]);
        if (input[i] != input[i-1]) {
            flag = false;
        }
    }
    if (flag) return input[0];
    else {
        return input[0] - prevVal(diffs);
    }
}

int main(void)
{
    auto start = chrono::high_resolution_clock::now();


    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");

    string in;
    int sol = 0;

    while (getline(file, in)) {
        stringstream curLine(in);

        vector<int> curVals;

        int curVal;
        while (curLine >> curVal) curVals.push_back(curVal);

        int temp = prevVal(curVals);

        sol += temp;
        cout << temp << endl;
    }

    cout << sol << endl;



    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "time in seconds " << duration.count() << endl;    
}
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

struct pair_hash {
    std::size_t operator () (const std::pair<string,long> &p) const {
        auto h1 = std::hash<string>{}(p.first);
        auto h2 = std::hash<long>{}(p.second);
        return h1 ^ h2;  
    }
};

unordered_map<pair<string, int>, long, pair_hash> memo;

// p1 version
int patternCheck(string code, vector<int>& pattern) {
    int sol = 0;

    for (int i = 0; i < code.size(); i++) {
        if (code[i] == '?') {
            code[i] = '.';
            sol += patternCheck(code, pattern);
            code[i] = '#';
            sol += patternCheck(code, pattern);
            return sol;
        }
    }

    int runSize = 0;
    int curIdx = 0;

    for (int i = 0; i < code.size(); i++) {
        if (code[i] == '#') runSize++;
        else {
            if (runSize > 0) {
                if (curIdx >= pattern.size() || pattern[curIdx] != runSize) {
                    return 0;
                }
                curIdx++;
                runSize = 0; 
            }
        }
    }

    if (!runSize) {
        return curIdx == pattern.size();
    } else {
        return curIdx == pattern.size() - 1 && pattern[curIdx] == runSize;
    }
    return 1;
}

long patternCheck2(string code, vector<int>& pattern) {
    // long sol = 0;

    // if (idx >= pattern.size()) {
    //     for (int i = 0; i < code.size(); i++) {
    //         if (code[i] == '#') return 0;
    //     }
    //     return 1;
    // }

    // int maxStart = -1;
    // int runLen = 0;
    // for (int i = 0; i < code.size() && (maxStart == -1 || (maxStart + pattern[idx] > i)); i++) {
    //     if (code[i] != '.') {
    //         if (code[i] == '#' && maxStart == -1) {
    //             maxStart = i;
    //         }
    //         runLen++;
    //     } else {
    //         if (maxStart >= 0) break;
    //         runLen = 0;
    //     }

    //     if (runLen >= pattern[idx]) {
    //         if (i + 1 >= code.size() || (i + 2 >= code.size() && code[i+1] != '#')) {
    //             if (memo.find(make_pair("", idx + 1)) != memo.end()) {
    //                 sol += memo[make_pair("",idx + 1)];
    //             } else {
    //                 sol += patternCheck2("", pattern, idx+1);
    //             }
    //         } else if (code[i+1] != '#') {
    //             string tempSub = code.substr(i+2);
    //             if (memo.find(make_pair(tempSub, idx + 1)) != memo.end()) {
    //                 sol += memo[make_pair(tempSub,idx + 1)];
    //             } else {
    //                 sol += patternCheck2(tempSub, pattern, idx+1);
    //             }
    //         }
    //     }
    // }

    // memo[make_pair(code, idx)] = sol;
    // return sol;

    code += ".";

    vector<vector<long>> dp(pattern.size(), vector<long>(code.size(), 0));

    int runLen = 0;
    int firstForce = -1;
    bool found = false;
    bool valid = true;

    int curCnt = 0;

    for (int i = 0; i < code.size(); i++) {
        // cout << i << " " << runLen << " "  << found << " "  << valid << " " << curCnt << endl;

        dp[0][i] = (found && valid && code[i] != '#') ? curCnt : 0; 

        if (code[i] != '.') {
            if (code[i] == '#') {
                curCnt = 0;
                if (firstForce == -1) {
                    firstForce = i;
                }
                if (firstForce != -1 && firstForce + pattern[0] <= i) {
                    valid = false;
                }
                
            }
            runLen++;

            if (runLen >= pattern[0] && code[i + 1] != '#') {
                if (firstForce == -1 || firstForce + pattern[0] > i) curCnt++;
                found = true;
            }
        } else {
            runLen = 0;
        }
    }

    // cout << code << endl;

    for (int i = 1; i < pattern.size(); i++) {
        int runLen = 0;
        
        for (int j = 0; j + 1 < code.size(); j++) {
            if (code[j] != '.') {
                runLen++;
            } else {
                runLen = 0;
            }
            // cout << i << ", " << j << ": " << runLen << endl;

            if (runLen >= pattern[i] && code[j + 1] != '#') {
                for (int k = j + 1; k < code.size() && code[k] != '#' && j-pattern[i] >= 0; k++) {
                    dp[i][k] += dp[i - 1][j - pattern[i]];
                }
            }
        }
    }

    // for (int i = 0; i < pattern.size(); i++) {
    //     for (int j = 0; j < code.size(); j++) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    // cout << dp[pattern.size() - 1][code.size() - 1] << endl;

    return dp[pattern.size() - 1][code.size() - 1];
}

int main(void)
{
    auto start = chrono::high_resolution_clock::now();

    ofstream fileOut("test2.txt");
    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");

    string codeString;
    long sol = 0;

    while (file >> codeString) {
        memo.clear();
        string code(codeString);

        for (int i = 0; i < 4; i++) {
            code += "?";
            code += codeString;
        }

        // code = codeString;

        string patternString;

        file >> patternString;
        stringstream patternStream(patternString);

        int val;
        char trash;
        vector<int> pattern;
        vector<int> patternTemp;
        while (patternStream >> val) {
            patternTemp.push_back(val);
            patternStream >> trash;
        }

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < patternTemp.size(); j++) {
                pattern.push_back(patternTemp[j]);
            }
        }

        // pattern = patternTemp;

        long temp = patternCheck2(code, pattern);
        // int temp2 = patternCheck(code, pattern);

        // if (temp != temp2) {
        //     cout << code << "\t actual: " << temp << "\t expected: " << temp2 << endl;
        // }
        
        // cout << "pattern: " << code << " returned: " << temp << endl; 

        fileOut << code << " " << temp << "\n";

        sol += temp;

        // return 0;
    }

    cout << sol << endl;

    fileOut.close();

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "time in seconds " << duration.count() << endl;    
}
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



int main(void)
{
    auto start = chrono::high_resolution_clock::now();


    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");

    string in;
    int sol = 0;

    vector<vector<int>> graph;
    vector<vector<int>> signpost;

    while (getline(file, in)) {
        stringstream curLine(in);

        vector<int> curLineVec;

        char cur;
        while (curLine >> cur) {
            switch(cur) {
                case 'O':
                    curLineVec.push_back(2);
                    break;
                case '#':
                    curLineVec.push_back(1);
                    break;
                case '.':
                    curLineVec.push_back(0);
                    break;
            }
        }

        graph.push_back(curLineVec);
    }

    int target_it = -1;
    // arbitrarily large to get into cycle
    for (long l = 0; l < 1000000000; l++) {
        for (int i = 0; i < graph.size(); i++) {
            for (int j = 0; j < graph[i].size(); j++) {
                if (graph[i][j] == 2) {
                    for (int k = i - 1; k >= 0; k--) {
                        if (graph[k][j] == 0) {
                            graph[k][j] = 2;
                            graph[k+1][j] = 0;
                        } else {
                            break;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < graph.size(); i++) {
            for (int j = 0; j < graph[i].size(); j++) {
                if (graph[i][j] == 2) {
                    for (int k = j - 1; k >= 0; k--) {
                        if (graph[i][k] == 0) {
                            graph[i][k] = 2;
                            graph[i][k + 1] = 0;
                        } else {
                            break;
                        }
                    }
                }
            }
        }

        for (int i = graph.size() - 1; i >= 0; i--) {
            for (int j = 0; j < graph[i].size(); j++) {
                if (graph[i][j] == 2) {
                    for (int k = i + 1; k < graph.size(); k++) {
                        if (graph[k][j] == 0) {
                            graph[k][j] = 2;
                            graph[k-1][j] = 0;
                        } else {
                            break;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < graph.size(); i++) {
            for (int j = graph[i].size(); j >= 0; j--) {
                if (graph[i][j] == 2) {
                    for (int k = j + 1; k < graph.size(); k++) {
                        if (graph[i][k] == 0) {
                            graph[i][k] = 2;
                            graph[i][k - 1] = 0;
                        } else {
                            break;
                        }
                    }
                }
            }
        }

        // if (vals.find(sol) == vals.end()) {
        //     vals[sol] = vector<int>(1, l);
        //     consec_old = 0;
        // } else {
        //     vals[sol].push_back(l);
        //     consec_old++;
        // }

        if (l == 1000000) {
            for (int i = 0; i < graph.size(); i++) {
                vector<int> curLineCopy;
                for (int j = 0; j < graph[i].size(); j++) {
                    curLineCopy.push_back(graph[i][j]);
                }
                signpost.push_back(curLineCopy);
            }
        }
        if (l > 1000000 && target_it == -1) {
            bool same = true;
            for (int i = 0; i < graph.size() && same; i++) {
                for (int j = 0; j < graph[i].size() && same; j++) {
                    if (graph[i][j] != signpost[i][j]) {
                        same = false;
                        break;
                    }
                }
            }

            if (same) {
                cout << "matched on line: " << l << endl;
                target_it = ((1000000000 - l) % (l - 1000000)) + l - 1; // 1 is 0 vs 1 indexing offset
                cout << "target set to: " << target_it << endl;
            }
        }

        // if (l == 1000004) {
        //     cout << "sanity check" << endl;
        //     int sol = 0;
        //     for (int i = 0; i < graph.size(); i++) {
        //         for (int j = 0; j < graph[i].size(); j++) {
        //             if (graph[i][j] == 2) sol += graph.size() - i;
        //         }
        //     }
        //     cout << sol << endl;
        // }

        if (target_it == l) {
            int sol = 0;
            for (int i = 0; i < graph.size(); i++) {
                for (int j = 0; j < graph[i].size(); j++) {
                    if (graph[i][j] == 2) sol += graph.size() - i;
                }
            }
            cout << sol << endl;
            return sol;
        }

        if (l % 100000 == 0) {
            cout << "iteration " << l << " done" << endl;
        }

        // if (consec_old > 997) {
        //     cout << "val: " << sol << " prev: " << vals[sol][vals[sol].size() - 2] << " now: " << l << endl;
        // } 
        // if (consec_old > 1000) break;
    }

    
    

    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph[i].size(); j++) {
            cout << graph[i][j];
            if (graph[i][j] == 2) sol += graph.size() - i;
        }
        cout << endl;
    }

    cout << sol << endl;



    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "time in seconds " << duration.count() << endl;    
}
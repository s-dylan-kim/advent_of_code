#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
// #include <chrono>
using namespace std;

class Node {
    public:
    int flow;
    unordered_set<string> dest;

    Node (int flow, unordered_set<string> dest) {
        this->flow = flow;
        this->dest = dest;
    }
};

class C_Node {
    public:
    int flow;
    unordered_map<string, int> dist;

    C_Node (int flow, unordered_map<string, int> dist) {
        this->flow = flow;
        this->dist = dist;
    }
};


int main(void)
{
    // auto start = chrono::high_resolution_clock::now();

    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");

    int sol = 0;

    unordered_map<string, Node*> nodes;
    unordered_set<string> non_zero;
    string in;

    while (getline(file, in)) {
        stringstream s(in);

        string cur_name;
        int flow_rate;
        s >> cur_name >> flow_rate;

        unordered_set<string> cur_dest;
        
        string dest;

        while (s >> dest) {
            cur_dest.insert(dest);
        }

        if (flow_rate) non_zero.insert(cur_name);

        nodes[cur_name] = new Node(flow_rate, cur_dest);
        
    }

    non_zero.insert("AA"); // artificially insert AA

    unordered_map<string, C_Node*> c_nodes;
    
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        if (non_zero.find(it->first) != non_zero.end()) {
            // find dist to "neighbor" non-0 flow nodes
            unordered_map<string, int> cur_dists;
            


            int dist = 1;
            queue<string> to_visit;
            unordered_set<string> visited;

            to_visit.push(it->first);
            visited.insert(it->first);

            to_visit.push(".");

            while (!to_visit.empty()) {
                string cur = to_visit.front();
                to_visit.pop();

                if (cur == ".") {
                    if (to_visit.empty()) break;
                    to_visit.push(".");
                    dist++;
                    continue;
                }

                for (auto it2 = nodes[cur]->dest.begin(); it2 != nodes[cur]->dest.end(); it2++) {
                    if (visited.find(*it2) == visited.end()) {
                        visited.insert(*it2);
                        if (non_zero.find(*it2) != non_zero.end()) {
                            cur_dists[*it2] = dist;
                            
                        }
                        to_visit.push(*it2);
                    }
                }
            }

            c_nodes[it->first] = new C_Node(it->second->flow, cur_dists);
        }
    }


    // for (auto it = c_nodes.begin(); it != c_nodes.end(); it++) {
    //     cout << it->first << ":" << it->second->flow << endl;
    //     for (auto it2 = it->second->dist.begin(); it2 != it->second->dist.end(); it2++) {
    //         cout << it2->first << ", " << it2->second << endl;
    //     }
    // }

    unordered_map<string, int> str_to_idx;
    vector<string> idx_to_str;

    // for (auto it = c_nodes.begin(); it != c_nodes.end(); it++) {
    //     idx_to_str.push_back(it->first);
    //     str_to_idx[it->first] = idx_to_str.size()-1;
    //     cout << it->first;
    // }
    // cout << endl;

    vector<vector<unordered_map<int,int>>> dp;


    dp.resize(31, vector<unordered_map<int,int>>(c_nodes.size()));

    dp[0][str_to_idx["AA"]][0] = 0;

    for (int i = 0; i < 27; i++) {
        for (int j = 0; j < c_nodes.size(); j++) {
            for (auto it = dp[i][j].begin(); it != dp[i][j].end(); it++) {   
                if (it->second > sol) sol = it->second;
                int k = it->first;
                if (i == 11) {
                }
                int pressure_add = 0;
                for (int l = 0; l < c_nodes.size(); l++) {
                    if ((k >> l) % 2 == 1) {
                        pressure_add += c_nodes[idx_to_str[l]]->flow;
                    }
                }

                

                for (int l = 0; l < c_nodes.size(); l++) {
                    int new_set = it->first;

                    if (j == l) {
                        if ((k >> l) % 2 == 0) {
                            new_set += 1 << l;
                        }

                        int new_val = dp[i][j][k] + pressure_add;

                        if (i < 30) {
                            
                            if (dp[i+1][j].find(new_set) != dp[i+1][j].end()) {
                                if (dp[i+1][j][new_set] > new_val) new_val = dp[i+1][j][new_set];
                            }

                            dp[i+1][j][new_set] = new_val;
                        } 
                    } else {
                        if ((k >> l) % 2 == 0) {
                            int dist = c_nodes[idx_to_str[j]]->dist[idx_to_str[l]];
                            int arrive_time = i + dist;
                            if (arrive_time < 29) {
                                int new_val = dp[i][j][k] + pressure_add * dist;
                                // if (i == 9 && j == 3 && k == 14) cout << "NEW_VAL: " << new_val << endl;

                                if (dp[arrive_time][l].find(new_set) != dp[arrive_time][l].end()) {
                                    if (dp[arrive_time][l][new_set] > new_val) new_val = dp[arrive_time][l][new_set];
                                }

                                dp[arrive_time][l][new_set] = new_val;
                            }
                        }
                    }
                }

            }
        }
    }

    // part 2 stuff

    vector<int> largest;
    largest.resize(pow(2, c_nodes.size()));

    for (int j = 0; j < c_nodes.size(); j++) {
        for (auto it = dp[26][j].begin(); it != dp[26][j].end(); it++) {
            // cout << it->first << endl;
            if (largest[it->first] < it->second) largest[it->first] = it->second;
        }
    }

    sol = 0;
    for (int i = 0; i < largest.size(); i++) {
        for (int k = i; k < largest.size(); k++) {
            if ((i & k) == 0 && sol < largest[i] + largest[k]) sol = largest[i] + largest[k];
        }
    }

    cout << sol << endl;   

    // auto stop = chrono::high_resolution_clock::now();
    // auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    // cout << "time in seconds " << duration.count() << endl; 
}
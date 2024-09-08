#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <algorithm>
using namespace std;

bool sortbyz(const tuple<int, int, int, int, int, int>& a,  
               const tuple<int, int, int, int, int, int>& b) 
{ 
    return (get<2>(a) < get<2>(b)); 
}

struct hash_pair {
    size_t operator()(const pair<int, int>& p) const
    {
        auto hash1 = hash<int>{}(p.first);
        auto hash2 = hash<int>{}(p.second);
 
        if (hash1 != hash2) {
            return hash1 ^ hash2;              
        }
         
        // If hash1 == hash2, their XOR is zero.
          return hash1;
    }
};

int getFall (int i, vector<unordered_set<int>>& dependencies, vector<int>& inCnt) {
    int total = 0;

    queue<int> toVisit;
    vector<int> visits(dependencies.size(), 0);
    for (auto it = dependencies[i].begin(); it != dependencies[i].end(); ++it) {
        toVisit.push(*it);
    }

    while (!toVisit.empty()) {
        int cur = toVisit.front();
        toVisit.pop();

        visits[cur]++;

        if (visits[cur] == inCnt[cur]) {
            total++;
            for (auto it = dependencies[cur].begin(); it != dependencies[cur].end(); ++it) {
                toVisit.push(*it);
            }
        }
    }

    return total;
} 

int main(void)
{
    auto start = chrono::high_resolution_clock::now();


    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");

    int sol = 0;

    int x1, y1, z1, x2, y2, z2;
    char trash;

    vector<tuple<int, int, int, int, int, int>> blocks;

    while (file >> x1 >> trash >> y1 >> trash >> z1 >> trash >> x2 >> trash >> y2 >> trash >> z2) {
        if (z1 < z2) {
            blocks.push_back(make_tuple(x1, y1, z1, x2, y2, z2));
        } else {
            blocks.push_back(make_tuple(x2, y2, z2, x1, y1, z1));
        }
        
    }

    sort(blocks.begin(), blocks.end(), sortbyz);

    int maxHeight = get<2>(blocks[blocks.size() - 1]);

    vector<bool> removable(blocks.size(), true);
    vector<unordered_set<int>> dependencies(blocks.size());
    vector<int> inCnt(blocks.size());

    vector<unordered_map<pair<int, int>, int, hash_pair>> blockGrid(maxHeight);

    for (int i = 0; i < blocks.size(); i++) {
        int curX1 = get<0>(blocks[i]);
        int curY1 = get<1>(blocks[i]);
        int curZ1 = get<2>(blocks[i]);
        int curX2 = get<3>(blocks[i]);
        int curY2 = get<4>(blocks[i]);
        int curZ2 = get<5>(blocks[i]);

        int minX = min(curX1, curX2);
        int maxX = max(curX1, curX2);
        int minY = min(curY1, curY2);
        int maxY = max(curY1, curY2);
        int minZ = min(curZ1, curZ2);
        int maxZ = max(curZ1, curZ2);

        unordered_set<int> touching;
        for (int z = minZ; z >= 0; z--) {
            for (int x = minX; z != 0 && x <= maxX; x++) {
                for (int y = minY; y <= maxY; y++) {
                    if (blockGrid[z - 1].find(make_pair(x, y)) != blockGrid[z - 1].end()) {
                        touching.insert(blockGrid[z-1][make_pair(x, y)]);
                    }
                }
            }
            if (touching.size() > 0 || z == 0) {
                for (int x = minX; x <= maxX; x++) {
                    for (int y = minY; y <= maxY; y++) {
                        blockGrid[z + maxZ - minZ][make_pair(x, y)]= i;
                    }
                }
                if (touching.size() == 1) {
                    removable[*(touching.begin())] = false;
                }
                for (auto it = touching.begin(); it != touching.end(); it++) {
                    dependencies[*(it)].insert(i);
                    // cout << i << " supported by " << *(touching.begin()) << endl;
                }
                inCnt[i] = touching.size();
                break;
            }
        }
    }

    for (int i = 0; i < removable.size(); i++) {
        if (removable[i]) sol++;
    }

    int sol2 = 0;

    for (int i = 0; i < dependencies.size(); i++) {
        sol2 += getFall(i, dependencies, inCnt);
    }   

    // for (int i = 0; i < blockGrid.size(); i++) {
    //     cout << "\n\n" << i << ":" << endl;
    //     for (auto it = blockGrid[i].begin(); it != blockGrid[i].end(); it++) {
    //         cout << "(" << it->first.first << ", " << it->first.second << "): " << it->second << endl;
    //     }
    // }

    cout << sol << endl;
    cout << sol2 << endl;



    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "time in seconds " << duration.count() << endl;    
}
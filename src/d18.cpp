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

struct Node {
 
    int x;
    int y;
    int z;

    Node (int xn, int yn, int zn) {
        x = xn;
        y = yn;
        z = zn;
    }

    // This function is used by unordered_set to compare
    bool operator==(const Node& t) const
    {
        return (this->x == t.x && this->y == t.y && this->z == t.z);
    }
};

class MyHashFunction {
public:
    // id is returned as hash function
    size_t operator()(const Node& p) const
    {
        return (hash<int>()(p.x << 16) ^ hash<int>()(p.y << 8) ^ hash<int>()(p.z));
    }
};


int main(void)
{
    auto start = chrono::high_resolution_clock::now();


    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");

    int x, y, z;
    int sol = 0;

    unordered_set<Node, MyHashFunction> cubes;
    int minx = -1;
    int maxx = -1;
    int maxy = -1;
    int miny = -1;
    int maxz = -1;
    int minz = -1;

    unordered_map<Node, int, MyHashFunction> pockets;

    while (file >> x >> y >> z) {
        cubes.insert(Node(x, y, z));
    }

    for (auto it = cubes.begin(); it != cubes.end(); it++) {
        int curx = it->x;
        int cury = it->y;
        int curz = it->z;

        if (curx < minx || minx == -1) minx = curx;
        if (curx > maxx || maxx == -1) maxx = curx;
        if (cury < miny || miny == -1) miny = cury;
        if (cury > maxy || maxy == -1) maxy = cury;
        if (curz < minz || minz == -1) minz = curz;
        if (curz > maxz || maxz == -1) maxz = curz;


        if (cubes.find(Node(curx - 1, cury, curz)) == cubes.end()) {
            pockets[Node(curx - 1, cury, curz)]++;
            sol++;
        }

        if (cubes.find(Node(curx + 1, cury, curz)) == cubes.end()) {
            pockets[Node(curx + 1, cury, curz)]++;
            sol++;
        }
        
        if (cubes.find(Node(curx, cury - 1, curz)) == cubes.end()) {
            pockets[Node(curx, cury - 1, curz)]++;
            sol++;
        }

        if (cubes.find(Node(curx, cury + 1, curz)) == cubes.end()) {
            pockets[Node(curx, cury + 1, curz)]++;
            sol++;
        }

        if (cubes.find(Node(curx, cury, curz - 1)) == cubes.end()) {
            pockets[Node(curx, cury, curz - 1)]++;
            sol++;
        }

        if (cubes.find(Node(curx, cury, curz + 1)) == cubes.end()) {
            pockets[Node(curx, cury, curz + 1)]++;
            sol++;
        }
    }

    // cout << minx << " " << maxx << " " << miny << " " << maxy << " " << minz << " " << maxz << endl;

    int sol2;

    unordered_map<Node, bool, MyHashFunction> seen_vals;

    for (auto it = pockets.begin(); it != pockets.end(); it++) {
        if (seen_vals.find(it->first) != seen_vals.end()) {
            sol2 += seen_vals[it->first] ? it->second : 0;
            continue;
        }

        queue<Node> q;
        unordered_set<Node, MyHashFunction> visited;
        bool found = false;

        q.push(Node(it->first.x, it->first.y, it->first.z));
        visited.insert(Node(it->first.x, it->first.y, it->first.z));

        while (!q.empty()) {
            Node cur = q.front();
            int curx = cur.x;
            int cury = cur.y;
            int curz = cur.z;

            q.pop();


            if (cur.x <= minx || cur.x >= maxx || cur.y <= miny || cur.y >= maxy || cur.z <= minz || cur.z >= maxz) {
                sol2 += it->second;
                found = true;
                // cout << "valid";
                break;
            }

            if (cubes.find(Node(curx - 1, cury, curz)) == cubes.end() && visited.find(Node(curx - 1, cury, curz)) == visited.end()) {
                if (seen_vals.find(Node(curx - 1, cury, curz)) != seen_vals.end()) {
                    if (seen_vals[Node(curx - 1, cury, curz)]) {
                        found = true;
                        sol2 += it->second;
                    }
                    break;
                }

                visited.insert(Node(curx - 1, cury, curz));
                q.push(Node(curx - 1, cury, curz));
            }

            if (cubes.find(Node(curx + 1, cury, curz)) == cubes.end() && visited.find(Node(curx + 1, cury, curz)) == visited.end()) {
                if (seen_vals.find(Node(curx + 1, cury, curz)) != seen_vals.end()) {
                    if (seen_vals[Node(curx + 1, cury, curz)]) {
                        found = true;
                        sol2 += it->second;
                    }
                    break;
                }

                visited.insert(Node(curx + 1, cury, curz));
                q.push(Node(curx + 1, cury, curz));
            }

            if (cubes.find(Node(curx, cury - 1, curz)) == cubes.end() && visited.find(Node(curx, cury - 1, curz)) == visited.end()) {
                if (seen_vals.find(Node(curx, cury - 1, curz)) != seen_vals.end()) {
                    if (seen_vals[Node(curx, cury - 1, curz)]) {
                        found = true;
                        sol2 += it->second;
                    }
                    break;
                }

                visited.insert(Node(curx, cury - 1, curz));
                q.push(Node(curx, cury - 1, curz));
            }

            if (cubes.find(Node(curx, cury + 1, curz)) == cubes.end() && visited.find(Node(curx, cury + 1, curz)) == visited.end()) {
                if (seen_vals.find(Node(curx, cury + 1, curz)) != seen_vals.end()) {
                    if (seen_vals[Node(curx, cury + 1, curz)]) {
                        found = true;
                        sol2 += it->second;
                    }
                    break;
                }

                visited.insert(Node(curx, cury + 1, curz));
                q.push(Node(curx, cury + 1, curz));
            }

            if (cubes.find(Node(curx, cury, curz - 1)) == cubes.end() && visited.find(Node(curx, cury, curz - 1)) == visited.end()) {
                if (seen_vals.find(Node(curx, cury, curz - 1)) != seen_vals.end()) {
                    if (seen_vals[Node(curx, cury, curz - 1)]) {
                        found = true;
                        sol2 += it->second;
                    }
                    break;
                }

                visited.insert(Node(curx, cury, curz - 1));
                q.push(Node(curx, cury, curz - 1));
            }

            if (cubes.find(Node(curx, cury, curz + 1)) == cubes.end() && visited.find(Node(curx, cury, curz + 1)) == visited.end()) {
                if (seen_vals.find(Node(curx, cury, curz + 1)) != seen_vals.end()) {
                    if (seen_vals[Node(curx, cury, curz + 1)]) {
                        found = true;
                        sol2 += it->second;
                    }
                    break;
                }

                visited.insert(Node(curx, cury, curz + 1));
                q.push(Node(curx, cury, curz + 1));
            }
        }

        for (auto it2 = visited.begin(); it2 != visited.end(); it2++) {
            seen_vals[*it2] = found;
        }

        // cout << endl;
    }


    cout << sol << endl;
    cout << sol2 << endl;


    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "time in seconds " << duration.count() << endl;
}
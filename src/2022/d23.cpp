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

#define ROUNDS 10

struct Node {
    public:
    int x, y;

    Node (int x, int y) {
        this->x = x;
        this->y = y;
    }

    bool operator==(const Node& t) const
    {
        return (this->x == t.x && this->y == t.y);
    }
};

class MyHashFunction {
public:
    // id is returned as hash function
    size_t operator()(const Node& t) const
    {
        return t.x ^ (t.y << 16);
    }
};

int main(void)
{
    auto start = chrono::high_resolution_clock::now();


    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");

    string in;
    int sol = 0;

    int y = 0;

    int maxy;
    int maxx;

    unordered_set<Node, MyHashFunction> elves;

    while (getline(file, in)) {
        int x = 0;
        stringstream s(in);

        char cur;

        while (s >> cur) {
            if (cur == '#') {
                elves.insert(Node(x, y));
            }
            x++;
        }

        maxx = x;

        y++;
    }
    maxy = y;

    // for (auto it = elves.begin(); it != elves.end(); it++) {
    //     cout << it->x << ", " << it->y << endl;
    // }
    // cout << endl << elves.size() << endl << endl;

    bool moved = true;
    int i = 0;

    while (moved) {
        moved = false;
        unordered_set<Node, MyHashFunction> visited;
        unordered_set<Node, MyHashFunction> overlap;

        for (auto it = elves.begin(); it != elves.end(); it++) {
            Node cur = *it;
            bool found = false;

            if (
                elves.find(Node(cur.x, cur.y-1)) == elves.end() &&
                elves.find(Node(cur.x-1, cur.y-1)) == elves.end() &&
                elves.find(Node(cur.x+1, cur.y-1)) == elves.end() &&
                elves.find(Node(cur.x, cur.y+1)) == elves.end() &&
                elves.find(Node(cur.x-1, cur.y+1)) == elves.end() &&
                elves.find(Node(cur.x+1, cur.y+1)) == elves.end() &&
                elves.find(Node(cur.x-1, cur.y)) == elves.end() &&
                elves.find(Node(cur.x+1, cur.y)) == elves.end()
            ) {
                // cout << cur.x << ", " << cur.y << " declare stay" << endl;
                continue;
            }

            for (int j = 0; j < 4; j++) {
                int dir = (i + j) % 4;

                switch (dir) {
                    case 0:
                        if (
                            elves.find(Node(cur.x, cur.y-1)) == elves.end() &&
                            elves.find(Node(cur.x-1, cur.y-1)) == elves.end() &&
                            elves.find(Node(cur.x+1, cur.y-1)) == elves.end()
                        ) {
                            // cout << cur.x << ", " << cur.y << " declare up" << endl;
                            found = true;
                            if (visited.find(Node(cur.x, cur.y-1)) == visited.end()) {
                                visited.insert(Node(cur.x, cur.y-1));
                            } else {
                                overlap.insert(Node(cur.x, cur.y-1));
                            }
                        }
                        break;

                    case 1:
                        if (
                            elves.find(Node(cur.x, cur.y+1)) == elves.end() &&
                            elves.find(Node(cur.x-1, cur.y+1)) == elves.end() &&
                            elves.find(Node(cur.x+1, cur.y+1)) == elves.end()
                        ) {
                            // cout << cur.x << ", " << cur.y << " declare down" << endl;
                            found = true;
                            if (visited.find(Node(cur.x, cur.y+1)) == visited.end()) {
                                visited.insert(Node(cur.x, cur.y+1));
                            } else {
                                overlap.insert(Node(cur.x, cur.y+1));
                            }
                        }
                        break;

                    case 2:
                        if (
                            elves.find(Node(cur.x-1, cur.y)) == elves.end() &&
                            elves.find(Node(cur.x-1, cur.y-1)) == elves.end() &&
                            elves.find(Node(cur.x-1, cur.y+1)) == elves.end()
                        ) {
                            // cout << cur.x << ", " << cur.y << " declare left" << endl;
                            found = true;
                            if (visited.find(Node(cur.x-1, cur.y)) == visited.end()) {
                                visited.insert(Node(cur.x-1, cur.y));
                            } else {
                                overlap.insert(Node(cur.x-1, cur.y));
                            }
                        }
                        break;

                    case 3:
                        if (
                            elves.find(Node(cur.x+1, cur.y)) == elves.end() &&
                            elves.find(Node(cur.x+1, cur.y-1)) == elves.end() &&
                            elves.find(Node(cur.x+1, cur.y+1)) == elves.end()
                        ) {
                            // cout << cur.x << ", " << cur.y << " declare right" << endl;
                            found = true;
                            if (visited.find(Node(cur.x+1, cur.y)) == visited.end()) {
                                visited.insert(Node(cur.x+1, cur.y));
                            } else {
                                overlap.insert(Node(cur.x+1, cur.y));
                            }
                        }
                        break;
                }
                if (found) break;
            }

            
        }

        unordered_set<Node, MyHashFunction> new_elves;

        for (auto it = elves.begin(); it != elves.end(); it++) {
            Node cur = *it;
            bool found = false;

            if (
                elves.find(Node(cur.x, cur.y-1)) == elves.end() &&
                elves.find(Node(cur.x-1, cur.y-1)) == elves.end() &&
                elves.find(Node(cur.x+1, cur.y-1)) == elves.end() &&
                elves.find(Node(cur.x, cur.y+1)) == elves.end() &&
                elves.find(Node(cur.x-1, cur.y+1)) == elves.end() &&
                elves.find(Node(cur.x+1, cur.y+1)) == elves.end() &&
                elves.find(Node(cur.x-1, cur.y)) == elves.end() &&
                elves.find(Node(cur.x+1, cur.y)) == elves.end()
            ) {
                new_elves.insert(cur);
                continue;
            }

            for (int j = 0; j < 4; j++) {
                int dir = (i + j) % 4;

                switch (dir) {
                    case 0:
                        if (
                            elves.find(Node(cur.x, cur.y-1)) == elves.end() &&
                            elves.find(Node(cur.x-1, cur.y-1)) == elves.end() &&
                            elves.find(Node(cur.x+1, cur.y-1)) == elves.end()
                        ) {
                            found = true;
                            if (overlap.find(Node(cur.x, cur.y-1)) == overlap.end()) {
                                moved = true;
                                new_elves.insert(Node(cur.x, cur.y-1));
                            } else {
                                // cout << "overlap at " << cur.x << ", " << cur.y << endl;
                                new_elves.insert(Node(cur.x, cur.y));
                            }
                        }
                        break;

                    case 1:
                        if (
                            elves.find(Node(cur.x, cur.y+1)) == elves.end() &&
                            elves.find(Node(cur.x-1, cur.y+1)) == elves.end() &&
                            elves.find(Node(cur.x+1, cur.y+1)) == elves.end()
                        ) {
                            found = true;
                            if (overlap.find(Node(cur.x, cur.y+1)) == overlap.end()) {
                                moved = true;
                                new_elves.insert(Node(cur.x, cur.y+1));
                            } else {
                                new_elves.insert(Node(cur.x, cur.y));
                            }
                        }
                        break;

                    case 2:
                        if (
                            elves.find(Node(cur.x-1, cur.y)) == elves.end() &&
                            elves.find(Node(cur.x-1, cur.y-1)) == elves.end() &&
                            elves.find(Node(cur.x-1, cur.y+1)) == elves.end()
                        ) {
                            found = true;
                            if (overlap.find(Node(cur.x-1, cur.y)) == overlap.end()) {
                                moved = true;
                                new_elves.insert(Node(cur.x-1, cur.y));
                            } else {
                                new_elves.insert(Node(cur.x, cur.y));
                            }
                        }
                        break;

                    case 3:
                        if (
                            elves.find(Node(cur.x+1, cur.y)) == elves.end() &&
                            elves.find(Node(cur.x+1, cur.y-1)) == elves.end() &&
                            elves.find(Node(cur.x+1, cur.y+1)) == elves.end()
                        ) {
                            found = true;
                            if (overlap.find(Node(cur.x+1, cur.y)) == overlap.end()) {
                                moved = true;
                                new_elves.insert(Node(cur.x+1, cur.y));
                            } else {
                                new_elves.insert(Node(cur.x, cur.y));
                            }
                        }
                        break;
                }
                if (found) break;
            }
            if (!found) new_elves.insert(Node(cur.x, cur.y));
        }

        elves = new_elves;

        // int min_x = -6969;
        // int min_y = -6969;
        // int max_x = -6969;
        // int max_y = -6969;

        // for (auto it = elves.begin(); it != elves.end(); it++) {
        //     if (min_x == -6969 || it->x < min_x) min_x = it->x;
        //     if (max_x == -6969 || it->x > max_x) max_x = it->x;
        //     if (min_y == -6969 || it->y < min_y) min_y = it->y;
        //     if (max_y == -6969 || it->y > max_y) max_y = it->y;
        // } 

        // cout << i << endl;
        // for (int z = min_y; z <= max_y; z++) {
        //     for (int p = min_x; p <= max_x; p++) {
        //         cout << (elves.find(Node(p, z)) == elves.end() ? '.' : '#');
        //     }
        //     cout << endl;
        // }
        // cout << endl << endl;
        i++;
    }


    int min_x = -6969;
    int min_y = -6969;
    int max_x = -6969;
    int max_y = -6969;

    for (auto it = elves.begin(); it != elves.end(); it++) {
        if (min_x == -6969 || it->x < min_x) min_x = it->x;
        if (max_x == -6969 || it->x > max_x) max_x = it->x;
        if (min_y == -6969 || it->y < min_y) min_y = it->y;
        if (max_y == -6969 || it->y > max_y) max_y = it->y;
    } 

    cout << min_x << " " << max_x << " " << min_y << " " << max_y << " " << elves.size() << " " << i << endl;



    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "time in microseconds " << duration.count() << endl;    
}
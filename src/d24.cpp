#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <unistd.h>
using namespace std;

struct Node {
    public:
    int x, y, dir, flag;

    Node (int x, int y, int dir, int flag) {
        this->x = x;
        this->y = y;
        this->dir = dir;
        this->flag = flag;
    }

    bool operator==(const Node& t) const
    {
        return (this->x == t.x && this->y == t.y && this->dir == t.dir && this->flag == t.flag);
    }
};

class NodeHashFunction {
public:
    // id is returned as hash function
    size_t operator()(const Node& t) const
    {
        return (t.x << 6) ^ (t.y << 19) ^ (t.dir << 4) ^ t.flag;
    }
};



int main(void)
{
    auto start = chrono::high_resolution_clock::now();


    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");

    string in;
    int sol = 0;

    unordered_set<Node, NodeHashFunction> nodes;

    int y = 0;
    int x = 0;

    while (file >> in) {
        stringstream s(in);

        char cur;

        x = 0;

        while (s >> cur) {
            if (cur != '.') {
                int dir = -1;

                if (cur == '>') dir = 0;
                if (cur == 'v') dir = 1;
                if (cur == '<') dir = 2;
                if (cur == '^') dir = 3;

                nodes.insert(Node(x, y, dir, 0));
            }
            x++;
        }
        y++;
    }

    int max_x = x - 1;
    int max_y = y - 1;

    unordered_set<Node, NodeHashFunction> visited; // no dir (all dir = -1)

    queue<Node> to_visit; // no dir (all dir = -1)

    to_visit.push(Node(-1, -1, -1, 0));
    to_visit.push(Node(0, -1, -1, 0));

    unordered_set<Node, NodeHashFunction> bad_nodes; // no dir (all dir = -1)

    int time = 1;

    while (!to_visit.empty()) {
        Node cur = to_visit.front();
        to_visit.pop();

        if (cur.x == -1 && cur.y == -1) {
            bad_nodes.clear();
            visited.clear();
            time++;
            
            for (auto it = nodes.begin(); it != nodes.end(); it++) {
                int cur_x = it->x;
                int cur_y = it->y;

                switch (it->dir) {
                    case 0:
                        cur_x = (cur_x + time) % (max_x + 1);
                        break;
                    case 1:
                        cur_y = (cur_y + time) % (max_y + 1);
                        break;
                    case 2:
                        cur_x = (cur_x - time) % (max_x + 1);
                        if (cur_x < 0) cur_x = cur_x + (max_x + 1);
                        break;
                    case 3:
                        cur_y = (cur_y - time) % (max_y + 1);
                        if (cur_y < 0) cur_y = cur_y + (max_y + 1);
                        break;
                }

                bad_nodes.insert(Node(cur_x, cur_y, -1, 0));
            }
            to_visit.push(Node(-1, -1, -1, 0));
        } else {
            if (cur.x == max_x && cur.y == max_y) {
                if (cur.flag == 0) {
                    
                    auto stop = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

                    cout << time << endl;
                    cout << "time in microseconds " << duration.count() << endl;    
                    return 1;
                }
                if (cur.flag == 0) {
                    visited.insert(Node(max_x, max_y + 1, -1, 1));
                    to_visit.push(Node(max_x, max_y + 1, -1, 1));
                } 
            }

            if (cur.x == 0 && cur.y == 0 && cur.flag == 1) {
                visited.insert(Node(0, -1, -1, 2));
                to_visit.push(Node(0, -1, -1, 2));
            }

            if (cur.x - 1 >= 0 && cur.y >= 0 && cur.y <= max_y && (bad_nodes.find(Node(cur.x - 1, cur.y, -1, 0)) == bad_nodes.end())) {
                if (visited.find(Node(cur.x - 1, cur.y, -1, cur.flag)) == visited.end()) {
                    visited.insert(Node(cur.x - 1, cur.y, -1, cur.flag));
                    to_visit.push(Node(cur.x - 1, cur.y, -1, cur.flag));
                }
            }

            if (cur.x + 1 <= max_x && cur.y >= 0 && cur.y <= max_y && (bad_nodes.find(Node(cur.x + 1, cur.y, -1, 0)) == bad_nodes.end())) {
                if (visited.find(Node(cur.x + 1, cur.y, -1, cur.flag)) == visited.end()) {
                    visited.insert(Node(cur.x + 1, cur.y, -1, cur.flag));
                    to_visit.push(Node(cur.x + 1, cur.y, -1, cur.flag));
                }
            }

            if (cur.y - 1 >= 0 && (bad_nodes.find(Node(cur.x, cur.y - 1, -1, 0)) == bad_nodes.end())) {
                if (visited.find(Node(cur.x, cur.y - 1, -1, cur.flag)) == visited.end()) {
                    visited.insert(Node(cur.x, cur.y - 1, -1, cur.flag));
                    to_visit.push(Node(cur.x, cur.y - 1, -1, cur.flag));
                }
            }

            if (cur.y + 1 <= max_y && (bad_nodes.find(Node(cur.x, cur.y + 1, -1, 0)) == bad_nodes.end())) {
                if (visited.find(Node(cur.x, cur.y + 1, -1, cur.flag)) == visited.end()) {
                    visited.insert(Node(cur.x, cur.y + 1, -1, cur.flag));
                    to_visit.push(Node(cur.x, cur.y + 1, -1, cur.flag));
                }
            }

            if (visited.find(Node(cur.x, cur.y, -1, cur.flag)) == visited.end() && (bad_nodes.find(Node(cur.x, cur.y, -1, 0)) == bad_nodes.end())) {
                visited.insert(Node(cur.x, cur.y, -1, cur.flag));
                to_visit.push(Node(cur.x, cur.y, -1, cur.flag));
            }
        }
    }



    cout << sol << endl;



    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "time in seconds " << duration.count() << endl;    
}
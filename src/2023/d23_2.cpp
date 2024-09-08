#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <climits>
using namespace std;

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

class Node {
    public:
    int x;
    int y;
    unordered_map<Node*, int> children;

    Node () {

    }

    Node (int x, int y) {
        this->x = x;
        this->y = y;
        children = unordered_map<Node*, int>();
    }
};

unordered_map<pair<int, int>, Node*, hash_pair> nodes;

Node* computeGraph (unordered_map<pair<int, int>, int, hash_pair>& graph, int startX, int endY) {

    queue<pair<pair<int, int>, pair<Node*, pair<int, int>>>> curPath;

    Node* head = new Node(startX, 0);
    nodes[make_pair(startX, 0)] = head;

    curPath.push(make_pair(make_pair(startX, 0), make_pair(head, make_pair(-1, -1))));
    unordered_set<pair<int, int>, hash_pair> visited;


    while (!curPath.empty()) {
        int curStartX = curPath.front().first.first;
        int curStartY = curPath.front().first.second;
        Node* source = curPath.front().second.first;
        int tempVisitedX = curPath.front().second.second.first;
        int tempVisitedY = curPath.front().second.second.second;
        curPath.pop();

        // cout << "starting path on (" << curStartX << ", " << curStartY << ")" << endl;
        

        queue<pair<int, int>> toVisit;
        toVisit.push(make_pair(curStartX, curStartY));
        visited.insert(make_pair(tempVisitedX, tempVisitedY));

        int dist = 0;
        while (!toVisit.empty()) {
            int curEndX = toVisit.front().first;
            int curEndY = toVisit.front().second;
            toVisit.pop();
            // cout << "visiting (" << curEndX << ", " << curEndY << ")" << endl;
            
            dist++;

            int connections = 0;

            

            if (graph.find(make_pair(curEndX - 1, curEndY)) != graph.end()) {
                connections++;
                if (visited.find(make_pair(curEndX - 1, curEndY)) == visited.end()) toVisit.push(make_pair(curEndX - 1, curEndY));
            }
            if (graph.find(make_pair(curEndX + 1, curEndY)) != graph.end()) {
                connections++;
                if (visited.find(make_pair(curEndX + 1, curEndY)) == visited.end()) toVisit.push(make_pair(curEndX + 1, curEndY));
            }
            if (graph.find(make_pair(curEndX, curEndY - 1)) != graph.end()) {
                connections++;
                if (visited.find(make_pair(curEndX, curEndY - 1)) == visited.end()) toVisit.push(make_pair(curEndX, curEndY - 1));
            }
            if (graph.find(make_pair(curEndX, curEndY + 1)) != graph.end()) {
                connections++;
                if (visited.find(make_pair(curEndX, curEndY + 1)) == visited.end()) toVisit.push(make_pair(curEndX, curEndY + 1));
            }

            // cout << "connections: " << connections << endl;

            if (connections > 2 || curEndY == endY) {
                Node* cur;
                if (nodes.find(make_pair(curEndX, curEndY)) == nodes.end()) {
                    cur = new Node(curEndX, curEndY);
                    nodes[make_pair(curEndX, curEndY)] = cur;
                } else {
                    cur = nodes[make_pair(curEndX, curEndY)];
                }



                if (graph.find(make_pair(curEndX - 1, curEndY)) != graph.end() && visited.find(make_pair(curEndX - 1, curEndY)) == visited.end()) {
                    curPath.push(make_pair(make_pair(curEndX - 1, curEndY), make_pair(cur, make_pair(curEndX, curEndY))));
                }
                if (graph.find(make_pair(curEndX + 1, curEndY)) != graph.end() && visited.find(make_pair(curEndX + 1, curEndY)) == visited.end()) {
                    curPath.push(make_pair(make_pair(curEndX + 1, curEndY), make_pair(cur, make_pair(curEndX, curEndY))));
                }
                if (graph.find(make_pair(curEndX, curEndY - 1)) != graph.end() && visited.find(make_pair(curEndX, curEndY - 1)) == visited.end()) {
                    curPath.push(make_pair(make_pair(curEndX, curEndY - 1), make_pair(cur, make_pair(curEndX, curEndY))));
                }
                if (graph.find(make_pair(curEndX, curEndY + 1)) != graph.end() && visited.find(make_pair(curEndX, curEndY + 1)) == visited.end()) {
                    curPath.push(make_pair(make_pair(curEndX, curEndY + 1), make_pair(cur, make_pair(curEndX, curEndY))));
                }

                cur->children[source] = dist;
                source->children[cur] = dist;
                visited.erase(make_pair(tempVisitedX, tempVisitedY));
                // cout << "linked (" << cur->x << ", " << cur->y << ") with (" << source->x << ", " << source->y << ") dist: " << dist << endl;
                break;
            }
            
            visited.insert(make_pair(curEndX, curEndY));
        } 
    }

    // for (int i = 0; i < nodes.size(); i++) {
    //     for (int j = 0; j < nodes.size(); j++) {
    //         if (i == j) continue;
    //         if (abs(nodes[i]->startX - nodes[j]->endX) <= 1 && abs(nodes[i]->startY - nodes[j]->endY) <= 1) {
    //             nodes[j]->children.push_back(nodes[i]);
    //         }
    //     }
    //     if (nodes[i]->startY == 0) startNode = nodes[i];
    // }


    // for (auto it = nodes.begin(); it != nodes.end(); it++) {
    //     cout << "(" << it->second->x << ", " << it->second->y << "): " << it->second->children.size() << endl;
    // }

    return head;
}

int getMaxDistHelper(Node* cur, unordered_set<Node*> visited, int endY) {
    int max = INT_MIN;
    // cout << "DFS through (" << cur->x << ", " << cur->y << ")" << endl;
    if (cur->y == endY) return 0;
    for (auto it = cur->children.begin(); it != cur->children.end(); it++) {
        if (visited.find(it->first) == visited.end()) {
            unordered_set<Node*> visitedCopy(visited);
            visitedCopy.insert(it->first);
            int childDist = getMaxDistHelper(it->first, visitedCopy, endY) + it->second;
            if (max < childDist) {
                max = childDist;
            }
        }
    }
    return max;
}

int getMaxDist(Node* cur, int endY) {
    unordered_set<Node*> visited;
    return getMaxDistHelper(cur, visited, endY) - 1;
}

int main(void)
{
    auto start = chrono::high_resolution_clock::now();


    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");

    string in;
    int sol = 0;


    int y = 0;

    unordered_map<pair<int, int>, int, hash_pair> graph;
    int startX;
    int endY;

    while (file >> in) {
        int x = 0;
        stringstream curLine(in);

        char c;
        while (curLine >> c) {
            switch (c) {
                case '^':
                    graph[make_pair(x, y)] = 1;
                    break;
                case '>':
                    graph[make_pair(x, y)] = 2;
                    break;
                case 'v':
                    graph[make_pair(x, y)] = 3;
                    break;
                case '<':
                    graph[make_pair(x, y)] = 4;
                    break;
                case '.':
                    graph[make_pair(x, y)] = 0;
                    if (y == 0) startX = x;
                    break;
            }
            x++;
        }
        y++;
    }
    endY = y - 1;

    Node* head = computeGraph(graph, startX, endY);

    int sol2 = getMaxDist(head, endY);

    cout << sol2 << endl;



    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "time in seconds " << duration.count() << endl;    
}
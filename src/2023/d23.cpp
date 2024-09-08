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
    int startX;
    int startY;
    int endX;
    int endY;
    int dist;
    vector<Node*> children;

    Node () {

    }

    Node (int startX, int startY, int endX, int endY, int dist) {
        this->startX = startX;
        this->endX = endX;
        this->startY = startY;
        this->endY = endY;
        this->dist = dist;
        children = vector<Node*>(0);
    }
};

vector<Node*> nodes;

Node* computeGraph (unordered_map<pair<int, int>, int, hash_pair>& graph, int startX, int endY) {

    queue<pair<int, int>> curPath;
    curPath.push(make_pair(startX, 0));
    

    unordered_set<pair<int, int>, hash_pair> startsDone;

    while (!curPath.empty()) {
        int curStartX = curPath.front().first;
        int curStartY = curPath.front().second;
        curPath.pop();

        if (startsDone.find(make_pair(curStartX, curStartY)) != startsDone.end()) {
            continue;
        }

        startsDone.insert(make_pair(curStartX, curStartY));

        // cout << "starting path on (" << curStartX << ", " << curStartY << ")" << endl;
        

        queue<pair<int, int>> toVisit;
        unordered_set<pair<int, int>, hash_pair> visited;
        toVisit.push(make_pair(curStartX, curStartY));

        switch (graph[make_pair(curStartX, curStartY)]) {
            case 1:
                visited.insert(make_pair(curStartX, curStartY + 1));
                break;
            case 2:
                visited.insert(make_pair(curStartX - 1, curStartY));
                break;
            case 3:
                visited.insert(make_pair(curStartX, curStartY - 1));
                break;
            case 4:
                visited.insert(make_pair(curStartX + 1, curStartY));
                break;
        }

        int dist = 0;
        while (!toVisit.empty()) {
            int curEndX = toVisit.front().first;
            int curEndY = toVisit.front().second;
            toVisit.pop();
            // cout << "visiting (" << curEndX << ", " << curEndY << ")" << endl;
            
            dist++;

            int connections = 0;
            visited.insert(make_pair(curEndX, curEndY));

            if (graph.find(make_pair(curEndX - 1, curEndY)) != graph.end() && visited.find(make_pair(curEndX - 1, curEndY)) == visited.end()) {
                connections++;
                toVisit.push(make_pair(curEndX - 1, curEndY));
            }
            if (graph.find(make_pair(curEndX + 1, curEndY)) != graph.end() && visited.find(make_pair(curEndX + 1, curEndY)) == visited.end()) {
                connections++;
                toVisit.push(make_pair(curEndX + 1, curEndY));
            }
            if (graph.find(make_pair(curEndX, curEndY - 1)) != graph.end() && visited.find(make_pair(curEndX, curEndY - 1)) == visited.end()) {
                connections++;
                toVisit.push(make_pair(curEndX, curEndY - 1));
            }
            if (graph.find(make_pair(curEndX, curEndY + 1)) != graph.end() && visited.find(make_pair(curEndX, curEndY + 1)) == visited.end()) {
                connections++;
                toVisit.push(make_pair(curEndX, curEndY + 1));
            }

            // cout << "connections: " << connections << endl;

            if (connections > 1 || curEndY == endY) {
                if (graph.find(make_pair(curEndX - 1, curEndY)) != graph.end() && visited.find(make_pair(curEndX - 1, curEndY)) == visited.end()) {
                    if (graph[make_pair(curEndX - 1, curEndY)] == 4) {
                        curPath.push(make_pair(curEndX - 1, curEndY));
                    }
                }
                if (graph.find(make_pair(curEndX + 1, curEndY)) != graph.end() && visited.find(make_pair(curEndX + 1, curEndY)) == visited.end()) {
                    if (graph[make_pair(curEndX + 1, curEndY)] == 2) {
                        curPath.push(make_pair(curEndX + 1, curEndY));
                    }
                }
                if (graph.find(make_pair(curEndX, curEndY - 1)) != graph.end() && visited.find(make_pair(curEndX, curEndY - 1)) == visited.end()) {
                    if (graph[make_pair(curEndX, curEndY - 1)] == 1) {
                        curPath.push(make_pair(curEndX, curEndY - 1));
                    }
                }
                if (graph.find(make_pair(curEndX, curEndY + 1)) != graph.end() && visited.find(make_pair(curEndX, curEndY + 1)) == visited.end()) {
                    if (graph[make_pair(curEndX, curEndY + 1)] == 3) {
                        curPath.push(make_pair(curEndX, curEndY + 1));
                    }
                }

                nodes.push_back(new Node(curStartX, curStartY, curEndX, curEndY, dist));
                break;
            }
            
        }
    }

    Node* startNode;

    for (int i = 0; i < nodes.size(); i++) {
        for (int j = 0; j < nodes.size(); j++) {
            if (i == j) continue;
            if (abs(nodes[i]->startX - nodes[j]->endX) <= 1 && abs(nodes[i]->startY - nodes[j]->endY) <= 1) {
                nodes[j]->children.push_back(nodes[i]);
            }
        }
        if (nodes[i]->startY == 0) startNode = nodes[i];
    }


    for (int i = 0; i < nodes.size(); i++) {
        cout << "(" << nodes[i]->startX << ", " << nodes[i]->startY << ") -> (" << nodes[i]->endX << ", " << nodes[i]->endY << "): " << nodes[i]->dist << " " << nodes[i]->children.size() << endl;
    }

    return startNode;
}

int getMaxDist(Node* cur) {
    int max = 0;
    for (int i = 0; i < cur->children.size(); i++) {
        int childDist = getMaxDist(cur->children[i]);
        if (max < childDist) {
            max = childDist;
        }
    }
    return max + cur->dist;
}

void freeAll() {
    for (int i = 0; i < nodes.size(); i++) {
        delete(nodes[i]);
    }
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

    sol = getMaxDist(head);

    freeAll();

    cout << sol - 1 << endl;



    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "time in seconds " << duration.count() << endl;    
}
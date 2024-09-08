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
    size_t operator()(const pair<string, string>& p) const
    {
        auto hash1 = hash<string>{}(p.first);
        auto hash2 = hash<string>{}(p.second);
 
        if (hash1 != hash2) {
            return hash1 ^ hash2;              
        }
         
        // If hash1 == hash2, their XOR is zero.
          return hash1;
    }
};

class RandomSet {
    private:
    unordered_map<pair<string, string>, int, hash_pair> idx; 
    vector<pair<string, string>> edges;
    int size;

    public:
    RandomSet() {
        idx = unordered_map<pair<string, string>, int, hash_pair>();
        edges = vector<pair<string, string>>();
        size = 0;
    }

    RandomSet(RandomSet& other) {
        for (auto it = other.idx.begin(); it != other.idx.end(); ++it) {
            idx[it->first] = it->second;
        }
        edges = vector<pair<string, string>>(other.edges);
        size = other.size;
    }

    void insert(pair<string, string> edge) {
        if (idx.find(edge) != idx.end()) return;

        int i =size;
        if (edges.size() <= size) {
            edges.push_back(edge);
            // cout << &(edges[edges.size() - 1]) << endl;
        } else {
            edges[size] = edge;
        }

        idx[edge] = size;
        size++;
    }

    void remove(pair<string, string> edge) {
        if (idx.find(edge) == idx.end()) return;

        // cout << edge.first << " " << edge.second << endl << flush;
        // cout << edges.size() << endl << flush;
        // cout << (void*)&(edges[0]) << endl;
        idx[edges[size - 1]] = idx[edge];
        edges[idx[edge]] = edges[size - 1];
        idx.erase(edge);
        
        size--;
    }

    pair<string, string> getRandom() {
        return edges[rand() % size];
    }

    int getSize() {
        return size;
    }

    pair<string, string> &operator[](int idx) {
        if (idx >= size) return edges[0];

        return edges[idx];
    }
};

class UnionFind {
    private:
    unordered_map<string, string> parents;
    int size;
    int gCount;

    public:
    UnionFind() {
        parents = unordered_map<string, string>();
        size = 0;
        gCount = 0;
    }

    UnionFind(UnionFind& other) {
        for (auto it = other.parents.begin(); it != other.parents.end(); ++it) {
            parents[it->first] = it->second;
        }
        size = other.size;
        gCount = other.gCount;
    }

    void insert(string node) {
        // cout << node << endl;
        if (parents.find(node) != parents.end()) return;
        
        parents[node] = node;
        size++;
        gCount++;
    }

    string find(string node) {
        if (parents[node] == node) return node;

        string group = find(parents[node]);
        parents[node] = group;
        return group;
    }

    void merge(string first, string second) {
        string firstGroup = find(first);
        string secondGroup = find(second);

        if (firstGroup == secondGroup) return;

        parents[secondGroup] = firstGroup;
        gCount--;
    }

    int groupCount() {
        return gCount;
    }

    int getSol() {
        unordered_map<string, int> counts;
        for (auto it = parents.begin(); it != parents.end(); it++) {
            string group = find(it->first);
            if (counts.find(group) == counts.end()) {
                counts[group] = 1;
            } else {
                counts[group]++;
            }
        }

        int sol = 1;
        for (auto it = counts.begin(); it != counts.end(); it++) {
            sol *= it->second;
            // cout << it->first << " " << it->second << endl;
        }
        return sol;
    }
};

int main(void)
{
    auto start = chrono::high_resolution_clock::now();


    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");

    string in;
    srand ( time(NULL) );
    int sol = 0;

    UnionFind nodes;
    RandomSet rSet;

    while (getline(file, in)) {
        stringstream cur(in);

        string source;
        cur >> source;
        source = source.substr(0, source.size()-1);
        nodes.insert(source);

        string end;
        while (cur >> end) {
            nodes.insert(end);
            rSet.insert(make_pair(source, end));
        }
    }

    while (true) {
        UnionFind nodeCopy(nodes);
        RandomSet rSetCopy(rSet);

        while(nodeCopy.groupCount() > 2) {
            pair<string, string> randEdge = rSetCopy.getRandom();
            if (nodeCopy.find(randEdge.first) != nodeCopy.find(randEdge.second)) {
                nodeCopy.merge(randEdge.first, randEdge.second);
            }
            rSetCopy.remove(randEdge);
        }

        RandomSet rSetCopyCopy(rSetCopy);
        for (int i = 0; i < rSetCopyCopy.getSize(); i++) {
            pair<string, string> curEdge = rSetCopyCopy[i];
            string g1 = nodeCopy.find(curEdge.first);
            string g2 = nodeCopy.find(curEdge.second);

            if (g1 == g2) {
                rSetCopy.remove(curEdge);
            }
        }

        cout << "found cut of size: " << rSetCopy.getSize() << endl;

        if (rSetCopy.getSize() == 3) {
            sol = nodeCopy.getSol();
            break;
        }
    }

    cout << sol << endl;



    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "time in seconds " << duration.count() << endl;    
}
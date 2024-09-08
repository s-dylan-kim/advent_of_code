#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
using namespace std;

int solution0;
int solution1;

class file_node {
    public:
    bool is_file;
    int size;
    file_node* parent;

    unordered_map<string, file_node*> children;

    file_node(bool is_file, int size, file_node* parent) {
        this->is_file = is_file;
        this->size = size;
        this->parent = parent;
    }
};

void do_size(file_node* cur) {
    int sum = 0;
    for (auto i: cur->children) {
        if((i.second)->is_file) {
            sum += (i.second)->size;
        } else {
            do_size(i.second);
            sum += (i.second)->size;
        }
    }
    cur->size = sum;

    if (sum <= 100000) {
        solution0 += sum;
    }

    // root -> size = 46975962
    if (sum >= 30000000 - (70000000 - 46975962) && (sum < solution1 || solution1 == -1)) {
        solution1 = sum;
    }
}

int main(void)
{   
    solution0 = 0;
    solution1 = -1;

    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");

    int in;
    string name;
    file_node* root = new file_node(0, -1, NULL);
    file_node* cur = root;

    string line;

    // skip root one
    getline(file, line);

    while (getline(file, line)) {
        stringstream s(line);

        if (line.rfind("$ cd", 0) == 0) {
            if (line.rfind("$ cd ..", 0) == 0) {
                cur = cur->parent;
                continue;
            }
            cur = cur->children[line.substr(5, line.size() - 5)];
        } else if (line.rfind("$ ls", 0) == 0) {
            continue;
        } 
        else if (line.rfind("dir", 0) == 0) {
            cur->children[line.substr(4, line.size() - 4)] = new file_node(false, -1, cur);
        } else {
            s >> in >> name;
            cur->children[name] = new file_node(true, in, cur);;
        }
    }

    do_size(root);

    cout << root->size << endl;

    cout << solution0 << endl;    
    cout << solution1 << endl;
}
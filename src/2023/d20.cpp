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

class Module {
    public:
    int type; // 0 = flip-flop (off), 1 = flip-flop (on), 2 = conjunction, 3 = broadcast
    vector<string> dest;
    unordered_map<string, bool> inputs; // for conjunction

    Module () {

    }

    Module (int type, vector<string> dest, unordered_map<string, bool> inputs) {
        this->type = type;
        this->dest = dest;
        this->inputs = inputs;
    }
};

int main(void)
{
    auto start = chrono::high_resolution_clock::now();


    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");

    string in;
    int sol = 0;

    unordered_map<string, Module> modules;
    unordered_set<string> conjunctions;

    while (file >> in) {
        int curType;
        if (in[0] == '%') curType = 0;
        else if (in[0] == '&') curType = 2;
        else curType = 3;

        string name = in;
        if (curType != 3) {
            name = in.substr(1);
        }
        

        if (curType == 2) conjunctions.insert(name);

        string dest;
        file >> dest;
        string lineRem;
        getline(file, lineRem);
        stringstream destsStr(lineRem);
        vector<string> destVec;

        while (destsStr >> dest) {
            if (dest[dest.size() - 1] == ',') {
                dest = dest.substr(0, dest.size() - 1);
            }
            destVec.push_back(dest);
        }
        modules[name] = Module(curType, destVec, unordered_map<string, bool>());
        // cout << name << endl;
    }

    for (auto it = modules.begin(); it != modules.end(); ++it) {
        for (int i = 0; i < it->second.dest.size(); i++) {
            if (conjunctions.find(it->second.dest[i]) != conjunctions.end()) {
                modules[it->second.dest[i]].inputs[it->first] = false;
                // cout << "adding " << it->first << " to dests of " << it->second.dest[i] << endl;
            }
        }
    }

    int lowCnt = 0;
    int highCnt = 0;
    long sol2 = 0;

    for (long i = 0; i < 100000000; i++) {
        // cout << i << "\n\n" << endl;
        queue<tuple<string, bool, string>> pulses;
        pulses.push(make_tuple("broadcaster", false, ""));

        while (!pulses.empty()) {
            string curStr = get<0>(pulses.front());
            bool signal = get<1>(pulses.front());
            string source = get<2>(pulses.front());
            // cout << source << " -" << signal << "-> " << curStr << endl;
            if (curStr == "rx" && !signal) {
                sol2 = i;
                cout << sol2 << endl;
                break;
            }
            if (signal) highCnt++;
            else lowCnt++;
            pulses.pop();

            if (modules[curStr].type == 0 || modules[curStr].type == 1) {
                if (!signal) {
                    modules[curStr].type = 1 - modules[curStr].type;
                    for (int j = 0; j < modules[curStr].dest.size(); j++) {
                        pulses.push(make_tuple(modules[curStr].dest[j], modules[curStr].type, curStr));
                    }
                }
                continue;
            }

            if (modules[curStr].type == 3) {
                for (int j = 0; j < modules[curStr].dest.size(); j++) {
                    pulses.push(make_tuple(modules[curStr].dest[j], signal, curStr));
                }
                continue;
            }

            if (modules[curStr].type == 2) {
                modules[curStr].inputs[source] = signal;
                bool out = false;

                for (auto it = modules[curStr].inputs.begin(); it != modules[curStr].inputs.end(); it++) {
                    // cout << it->first << ": " << it->second << endl;
                    if (!it->second) {
                        out = true;
                        break;
                    }
                }

                for (int j = 0; j < modules[curStr].dest.size(); j++) {
                    pulses.push(make_tuple(modules[curStr].dest[j], out, curStr));
                }
            }
        }

        if (sol2 != 0) break;
    }

    sol = (long) lowCnt * (long) highCnt;
    



    cout << sol << endl;



    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "time in seconds " << duration.count() << endl;    
}
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

class Conditions {
    public:
    char ruleComponent;
    bool lessThan;
    int threshold;
    string destination;
    bool universal;

    Conditions (char ruleComponent, bool lessThan, int threshold, string destination, bool universal) {
        this->ruleComponent = ruleComponent;
        this->lessThan = lessThan;
        this->threshold = threshold;
        this->destination = destination;
        this->universal = universal;
    }
};

class Range {
    public:
    int minX, minM, minA, minS;
    int maxX, maxM, maxA, maxS;

    Range (int minX, int maxX, int minM, int maxM, int minA, int maxA, int minS, int maxS) {
        this->minX = minX;
        this->maxX = maxX;
        this->minM = minM;
        this->maxM = maxM;
        this->minA = minA;
        this->maxA = maxA;
        this->minS = minS;
        this->maxS = maxS;
    }
};

int main(void)
{
    auto start = chrono::high_resolution_clock::now();


    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");

    string in;
    int sol = 0;

    unordered_map<string, vector<Conditions>> workflows;

    bool finishedWorkflow = false;
    while (getline(file, in)) {
        if (in[0] == 13) {
            finishedWorkflow = true;
            continue;
        }
        if (finishedWorkflow) {
            unordered_map<char, int> vals;

            int cur = 0;
            while (in[cur] != '=') cur++;
            cur++;
            int intStart = cur;
            while (in[cur] != ',') cur++;
            vals['x'] = stoi(in.substr(intStart, cur - intStart));
            cur++;
            while (in[cur] != '=') cur++;
            cur++;
            intStart = cur;
            while (in[cur] != ',') cur++;
            vals['m'] = stoi(in.substr(intStart, cur - intStart));
            cur++;
            while (in[cur] != '=') cur++;
            cur++;
            intStart = cur;
            while (in[cur] != ',') cur++;
            vals['a'] = stoi(in.substr(intStart, cur - intStart));
            cur++;
            while (in[cur] != '=') cur++;
            cur++;
            intStart = cur;
            while (in[cur] != '}') cur++;
            vals['s'] = stoi(in.substr(intStart, cur - intStart));

            
            string curState = "in";

            while (curState != "A" && curState != "R") {
                // cout << curState << ", ";
                for (int i = 0; i < workflows[curState].size(); i++) {
                    if (workflows[curState][i].universal) {
                        curState = workflows[curState][i].destination;
                        break;
                    }
                    bool greater = (vals[workflows[curState][i].ruleComponent] > workflows[curState][i].threshold);
                    if (greater != workflows[curState][i].lessThan) {
                        curState = workflows[curState][i].destination;
                        break;
                    }
                }
            }
            // cout << curState << endl;

            if (curState == "A") {
                // cout << vals['x'] << " " << vals['m'] << " " << vals['a'] << " " << vals['s'] << endl;
                sol += vals['x'] + vals['m'] + vals['a'] + vals['s'];
            }
        } else {
            int cur = 0;
            while (in[cur] != '{') cur++;
            string name = in.substr(0, cur);
            cur++;

            vector<Conditions> conditions;
            while (in[cur] != '}') {
                int strStart = cur;
                while (in[cur] != '<' && in[cur] != '>' && in[cur] != '}') cur++;
                string ruleComponent = in.substr(strStart, cur - strStart);
                if (in[cur] == '}') {
                    conditions.push_back(Conditions(0, true, 0, ruleComponent, true));
                    break;
                }
                bool lessThan = (in[cur] == '<');
                cur++;
                strStart = cur;
                while (in[cur] != ':') cur++;
                int threshold = stoi(in.substr(strStart, cur - strStart));
                cur++;
                strStart = cur;
                while (in[cur] != ',' && in[cur] != '}') cur++;
                string destination = in.substr(strStart, cur - strStart);
                conditions.push_back(Conditions(ruleComponent[0], lessThan, threshold, destination, false));
                cur++;
            }

            workflows[name] = conditions;
        }
    }

    queue<pair<string, Range>> rangeQueue;
    rangeQueue.push(make_pair("in", Range(1, 4000, 1, 4000, 1, 4000, 1, 4000)));

    long sol2 = 0;

    while (!rangeQueue.empty()) {
        pair<string, Range> cur = rangeQueue.front();
        Range curRange = cur.second;
        string curLoc = cur.first;

        // cout << curLoc << ": (" << curRange.minX << "," << curRange.maxX << ") (" << curRange.minM << "," << curRange.maxM << ") (" << curRange.minA << "," << curRange.maxA << ") (" << curRange.minS << "," << curRange.maxS << ")" << endl;

        rangeQueue.pop();
        if (curLoc == "R") continue;
        if (curLoc == "A") {
            sol2 += ((long)(curRange.maxX - curRange.minX + 1)) * ((long)(curRange.maxM - curRange.minM + 1)) * ((long)(curRange.maxA - curRange.minA + 1)) * ((long)(curRange.maxS - curRange.minS + 1));
            continue;
        }

        
        for (int i = 0; i < workflows[curLoc].size(); i++) {
            if(workflows[curLoc][i].universal) {
                rangeQueue.push(make_pair(workflows[curLoc][i].destination, curRange));
            }

            int thresholdVal = workflows[curLoc][i].threshold;
            int lessThan = workflows[curLoc][i].lessThan;

            switch (workflows[curLoc][i].ruleComponent) {
                case 'x':
                    if (lessThan) {
                        if (curRange.minX < thresholdVal) {
                            rangeQueue.push(make_pair(workflows[curLoc][i].destination, Range(curRange.minX, thresholdVal - 1, curRange.minM, curRange.maxM, curRange.minA, curRange.maxA, curRange.minS, curRange.maxS)));
                            curRange.minX = thresholdVal;
                        }
                    } else {
                        if (curRange.maxX >= thresholdVal) {
                            rangeQueue.push(make_pair(workflows[curLoc][i].destination, Range(thresholdVal + 1, curRange.maxX, curRange.minM, curRange.maxM, curRange.minA, curRange.maxA, curRange.minS, curRange.maxS)));
                            curRange.maxX = thresholdVal;
                        }
                    }
                    break;
                case 'm':
                    if (lessThan) {
                        if (curRange.minM < thresholdVal) {
                            rangeQueue.push(make_pair(workflows[curLoc][i].destination, Range(curRange.minX, curRange.maxX, curRange.minM, thresholdVal - 1, curRange.minA, curRange.maxA, curRange.minS, curRange.maxS)));
                            curRange.minM = thresholdVal;
                        }
                    } else {
                        if (curRange.maxM >= thresholdVal) {
                            rangeQueue.push(make_pair(workflows[curLoc][i].destination, Range(curRange.minX, curRange.maxX, thresholdVal + 1, curRange.maxM, curRange.minA, curRange.maxA, curRange.minS, curRange.maxS)));
                            curRange.maxM = thresholdVal;
                        }
                    }
                    break;
                case 'a':
                    if (lessThan) {
                        if (curRange.minA < thresholdVal) {
                            rangeQueue.push(make_pair(workflows[curLoc][i].destination, Range(curRange.minX, curRange.maxX, curRange.minM, curRange.maxM, curRange.minA, thresholdVal - 1, curRange.minS, curRange.maxS)));
                            curRange.minA = thresholdVal;
                        }
                    } else {
                        if (curRange.maxA >= thresholdVal) {
                            rangeQueue.push(make_pair(workflows[curLoc][i].destination, Range(curRange.minX, curRange.maxX, curRange.minM, curRange.maxM, thresholdVal + 1, curRange.maxA, curRange.minS, curRange.maxS)));
                            curRange.maxA = thresholdVal;
                        }
                    }
                    break;
                case 's':
                    if (lessThan) {
                        if (curRange.minS < thresholdVal) {
                            rangeQueue.push(make_pair(workflows[curLoc][i].destination, Range(curRange.minX, curRange.maxX, curRange.minM, curRange.maxM, curRange.minA, curRange.maxA, curRange.minS, thresholdVal - 1)));
                            curRange.minS = thresholdVal;
                        }
                    } else {
                        if (curRange.maxS >= thresholdVal) {
                            rangeQueue.push(make_pair(workflows[curLoc][i].destination, Range(curRange.minX, curRange.maxX, curRange.minM, curRange.maxM, curRange.minA, curRange.maxA, thresholdVal + 1, curRange.maxS)));
                            curRange.maxS = thresholdVal;
                        }
                    }
                    break;
            }
        }
    }


    // for (auto it = workflows.begin(); it != workflows.end(); ++it) {
    //     cout << it->first << endl;
    //     for (int i = 0; i < it->second.size(); i++) {
    //         cout << it->second[i].ruleComponent << " " << it->second[i].lessThan << " " << it->second[i].threshold << " " << it->second[i].destination << " " << it->second[i].universal << endl; 
    //     }
    // }

    cout << sol << endl;
    cout << sol2 << endl;



    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "time in seconds " << duration.count() << endl;    
}
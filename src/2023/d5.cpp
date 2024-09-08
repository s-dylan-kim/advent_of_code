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

bool sortcol(const vector<long>& v1, const vector<long>& v2)
{
    return v1[1] > v2[1];
}

int main(void)
{
    auto start = chrono::high_resolution_clock::now();


    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");

    long in, in2;
    long sol = 0;

    string trash;
    file >> trash;

    vector<pair<long, long>> seeds;
    while (file >> in >> in2) {
        seeds.push_back(make_pair(in, in2));
    }

    file.clear();
    while (getline(file, trash)) {
        vector<vector<long>> ranges;
        long dst, src, rng;
        while (file >> dst >> src >> rng) {
            ranges.push_back(vector<long>{dst, src, rng});
        }
        file.clear();
        
        // sort ranges by src start time
        sort(ranges.begin(), ranges.end(), sortcol);

        vector<pair<long, long>> newSeeds;
        for (long i = 0; i < seeds.size(); i++) {
            // keep track of what seeds have been covered to prevent leaking ranges
            long highestUncovered = seeds[i].first + seeds[i].second - 1;
            
            // skip to first range that can potentially overlap with current seed i.e. (beginning of range <= end of seed range)
            long j = 0;
            while(j < ranges.size() && ranges[j][1] > seeds[i].first + seeds[i].second - 1) j++; // - 1 adj for endpolong since second is range not + offset

            // loop for all valid overlapping ranges
            for (; j < ranges.size() && ranges[j][1] + ranges[j][2] > seeds[i].first; j++) {
                long newLen;

                // calc new length resulting from overlaping
                if (seeds[i].first < ranges[j][1]) {
                    newLen = min(seeds[i].second + seeds[i].first - ranges[j][1], ranges[j][2]);
                } else {
                    newLen = min(ranges[j][2] + ranges[j][1] - seeds[i].first, seeds[i].second);
                }

                // calc combined range start point
                long newStart = max(seeds[i].first, ranges[j][1]);

                // make sure no part of seed range leaks (create new seed element for any leaks if needed)
                if (newStart + newLen <= highestUncovered) {
                    long fillerStart = newStart + newLen;
                    long fillerLen = highestUncovered - fillerStart + 1;
                    newSeeds.push_back(make_pair(fillerStart, fillerLen));
                }

                // apply transformation of range
                long transformedStart = newStart + ranges[j][0] - ranges[j][1];

                newSeeds.push_back(make_pair(transformedStart, newLen));
                
                highestUncovered = newStart - 1;
            }

            // one last check for leaks
            if (highestUncovered > seeds[i].first) {
                newSeeds.push_back(make_pair(seeds[i].first, highestUncovered - seeds[i].first + 1));
            }
        }

        seeds = newSeeds;
    }

    sol = seeds[0].first;
    for (long i = 1; i < seeds.size(); i++) {
        if (sol > seeds[i].first) sol = seeds[i].first;
    }

    cout << sol << endl;

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "time in seconds " << duration.count() << endl;    
}
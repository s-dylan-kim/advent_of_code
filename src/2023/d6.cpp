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


int main(void)
{
    auto start = chrono::high_resolution_clock::now();


    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");

    long in;
    long sol = 1;
    long sol2;

    long bigTime = 0;
    long bigDist = 0;

    string trash;
    
    vector<long> times;
    vector<long> dists;

    file >> trash;
    while (file >> in) {
        times.push_back(in);

        long temp = in;
        while (temp) {
            temp /= 10;
            bigTime *= 10;
        }
        bigTime += in;
    }
    file.clear();

    file >> trash;
    while (file >> in) {
        dists.push_back(in);
        long temp = in;
        while (temp) {
            temp /= 10;
            bigDist *= 10;
        }
        bigDist += in;
    }

    for (long i = 0; i < times.size(); i++) {
        long lower, upper;

        for (lower = 0; lower * (times[i] - lower) <= dists[i]; lower++);
        for (upper = times[i]; upper * (times[i] - upper) <= dists[i]; upper--);

        sol *= (upper - lower + 1);
    }

    cout << sol << endl;

    long lower, upper;

    for (lower = 0; lower * (bigTime - lower) <= bigDist; lower++);
    for (upper = bigTime; upper * (bigTime - upper) <= bigDist; upper--);

    sol2 = (upper - lower + 1);

    cout << sol2 << endl;

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "time in seconds " << duration.count() << endl;    
}
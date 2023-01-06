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

    string in;
    long tot_sol = 0;

    while (file >> in) {
        stringstream s(in);
        char cur;
        long sol = 0;
        while (s >> cur) {
            sol *= 5;
            switch (cur) {
                case '2':
                    sol += 2;
                    break;
                case '1':
                    sol += 1;
                    break;
                case '-':
                    sol -= 1;
                    break;
                case '=':
                    sol -= 2;
                    break;
            }
        }
        tot_sol += sol;
    }

    string final_sol = "";

    while (tot_sol != 0) {
        switch (((tot_sol % 5) + 5) % 5) {
            case 0:
                final_sol = '0' + final_sol;
                break;
            case 1:
                final_sol = '1' + final_sol;
                tot_sol -= 1;
                break;
            case 2:
                final_sol = '2' + final_sol;
                tot_sol -= 2;
                break;
            case 3:
                final_sol = '=' + final_sol;
                tot_sol += 2;
                break;
            case 4:
                final_sol = '-' + final_sol;
                tot_sol += 1;
                break;
        }
        tot_sol /= 5;
    }

    cout << final_sol << endl;



    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "time in seconds " << duration.count() << endl;    
}
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;


int main(void)
{
    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");

    string op;
    int in;
    int sol = 0;

    int cycle = 0;
    int x = 1;

    while (file >> op) {
        
        // if ((cycle-20) % 40 == 0) {
        //     cout << cycle << ", " << x << ": " << x*cycle << endl;
        //     sol += x*cycle;
        // }
        // cout << x << " " <<  cycle;
        if (abs(x - (cycle%40)) <= 1) cout << "#";
        else cout << ".";
        if ((cycle+1)%40==0) cout << endl;

        cycle++;
        
        if (op == "addx") {
            // if ((cycle-20) % 40 == 0) {
            //     cout << cycle << ", " << x << ": " << x*cycle << endl;
            //     sol += x*cycle;
            // }
            // cout << x << " " << cycle;
            if (abs(x - (cycle%40)) <= 1) cout << "#";
            else cout << ".";
            if ((cycle+1)%40==0) cout << endl;

            cycle++;

            file >> in;
            x += in;
        }


    }

    cout << sol << endl;    
}
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

// #define test

class HailStone {
    public:
    double x, y, z, dx, dy, dz;

    HailStone(double x, double y, double z, double dx, double dy, double dz) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->dx = dx;
        this->dy = dy;
        this->dz = dz;
    }
};

int main(void)
{
    auto start = chrono::high_resolution_clock::now();


    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");

    double x, y, z, dx, dy, dz;
    char c;
    int sol = 0;

    vector<HailStone> stones;
    while (file >> x >> c >> y >> c >> z >> c >> dx >> c >> dy >> c >> dz) {
        stones.push_back(HailStone(x, y, z, dx, dy, dz));
    }

    for (int i = 0; i < stones.size(); i++) {
        for (int j = i + 1; j < stones.size(); j++) {
            double right = stones[j].x/stones[j].dx - stones[j].y/stones[j].dy;
            double left = stones[i].x/stones[j].dx - stones[i].y/stones[j].dy;
            double coeff = stones[i].dx/stones[j].dx - stones[i].dy/stones[j].dy;

            // cout << left << ", " << coeff << ", " << right << endl;

            double t1 = (right - left)/coeff;

            if (t1 < 0) continue;

            double xVal = stones[i].x + stones[i].dx * t1;
            double yVal = stones[i].y + stones[i].dy * t1;

            double t2 = (xVal - stones[j].x)/stones[j].dx;

            if (t2 < 0) continue;

            #ifdef test
            if (xVal >= 7 && yVal >= 7 && xVal <= 27 && yVal <= 27) {
                sol++;
                cout << "hailstones at " << stones[i].x << ", " << stones[i].y << ", " << stones[i].z << " @ " << stones[i].dx << ", " << stones[i].dy << ", " << stones[i].dz << " and "  << stones[j].x << ", " << stones[j].y << ", " << stones[j].z << " @ " << stones[j].dx << ", " << stones[j].dy << ", " << stones[j].dz << " intersect at " << xVal << ", " << yVal << endl;
            }
            #else
            if (xVal >= 200000000000000 && yVal >= 200000000000000 && xVal <= 400000000000000 && yVal <= 400000000000000) {
                sol++;
            }
            #endif
        }
    }

    cout << sol << endl;



    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "time in seconds " << duration.count() << endl;    
}
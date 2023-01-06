#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <unistd.h>
using namespace std;

struct Blueprint {
    int ore_cost;
    int clay_cost;
    int obsidian_ore_cost;
    int obsisidan_clay_cost;
    int geode_ore_cost;
    int geode_obsidian_cost;

    int max_ore;
    int max_clay;

    Blueprint(int ore_cost, int clay_cost, int obsidian_ore_cost, int obsisidian_clay_cost, int geode_ore_cost, int geode_obsidian_cost) {
        this->ore_cost = ore_cost;
        this->clay_cost = clay_cost;
        this->obsidian_ore_cost = obsidian_ore_cost;
        this->obsisidan_clay_cost = obsisidian_clay_cost;
        this->geode_ore_cost = geode_ore_cost;
        this->geode_obsidian_cost = geode_obsidian_cost;

        max_ore = max(max(max(ore_cost, clay_cost), obsidian_ore_cost), geode_ore_cost);
    }
};

struct Node {
 
    int ore;
    int ore_robots;
    int clay;
    int clay_robots;
    int obsidian;
    int obsidian_robots;
    int geodes;
    int geode_robots;

    Node (int ore, int ore_robots, int clay, int clay_robots, int obsidian, int obsidian_robots, int geodes, int geode_robots) {
        this->ore = ore;
        this->ore_robots = ore_robots;
        this->clay = clay;
        this->clay_robots = clay_robots;
        this->obsidian = obsidian;
        this->obsidian_robots = obsidian_robots;
        this->geodes = geodes;
        this->geode_robots = geode_robots;
    }

    // This function is used by unordered_set to compare
    bool operator==(const Node& t) const
    {
        return (
            this->ore == t.ore &&
            this->ore_robots == t.ore_robots &&
            this->clay == t.clay &&
            this->clay_robots == t.clay_robots &&
            this->obsidian == t.obsidian &&
            this->obsidian_robots == t.obsidian_robots &&
            this->geodes == t.geodes &&
            this->geode_robots == t.geode_robots
        );
    }
};

class MyHashFunction {
public:
    // id is returned as hash function
    size_t operator()(const Node& p) const
    {
        return (
            hash<int>()(p.ore << 27) ^
            hash<int>()(p.ore_robots << 24) ^
            hash<int>()(p.clay << 19) ^
            hash<int>()(p.clay_robots << 16) ^
            hash<int>()(p.obsidian << 11) ^
            hash<int>()(p.obsidian_robots << 8) ^
            hash<int>()(p.geodes << 3) ^
            hash<int>()(p.geode_robots)
        );
    }
};


int main(void)
{
    auto start = chrono::high_resolution_clock::now();


    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");

    int sol = 0;

    int ore_cost;
    int clay_cost;
    int obsidian_ore_cost;
    int obsisidan_clay_cost;
    int geode_ore_cost;
    int geode_obsidian_cost;

    vector<Blueprint> blueprints;

    while (file >> ore_cost >> clay_cost >> obsidian_ore_cost >> obsisidan_clay_cost >> geode_ore_cost >> geode_obsidian_cost) {
        blueprints.push_back(Blueprint(ore_cost, clay_cost, obsidian_ore_cost, obsisidan_clay_cost, geode_ore_cost, geode_obsidian_cost));
    }



    for (int i = 0; i < 3; i++) {

        cout << "running index " << i << ": " << endl;

        // cout << blueprints[i].ore_cost << " " << blueprints[i].clay_cost << " " << blueprints[i].obsidian_ore_cost << " " << blueprints[i].obsisidan_clay_cost << " " << blueprints[i].geode_ore_cost << " " << blueprints[i].geode_obsidian_cost << endl;

        int cur_max = 0;

        vector<unordered_set<Node, MyHashFunction>> dp(32);
        dp[0].insert(Node(0, 1, 0, 0, 0, 0, 0, 0));

        for (int j = 0; j < 32; j++) {
            cout << j << " size(" << dp[j].size() <<") " << endl;

            for (auto it = dp[j].begin(); it != dp[j].end(); it++) {
                Node cur = *it;

                // cout << cur.ore << " " << cur.ore_robots << " " << cur.clay << " " << cur.clay_robots << " " << cur.obsidian << " " << cur.obsidian_robots << " " << cur.geodes << " " << cur.geode_robots << endl;

                if (cur.geodes + cur.geode_robots > cur_max) cur_max = cur.geodes + cur.geode_robots;

                if (j == 31) continue;

                // if (cur.clay + cur.clay_robots < 0) cout << "HUH" << endl;
                int new_ore = cur.ore + cur.ore_robots;
                int new_clay = cur.clay + cur.clay_robots;
                int new_obsidian = cur.obsidian + cur.obsidian_robots;
                int new_geode = cur.geodes + cur.geode_robots;

                if (cur.ore_robots == blueprints[i].max_ore) new_ore = blueprints[i].max_ore;
                if (cur.clay_robots == blueprints[i].obsisidan_clay_cost) new_clay = blueprints[i].obsisidan_clay_cost;
                if (cur.obsidian_robots == blueprints[i].geode_obsidian_cost) new_clay = blueprints[i].obsisidan_clay_cost;

                // if (new_ore > blueprints[i].max_ore) new_ore = blueprints[i].max_ore;
                // if (new_clay > blueprints[i].obsisidan_clay_cost) new_clay = blueprints[i].obsisidan_clay_cost;
                // if (new_obsidian > blueprints[i].geode_obsidian_cost) new_obsidian = blueprints[i].geode_obsidian_cost;

                if (cur.ore < blueprints[i].max_ore) {
                    Node temp(new_ore, cur.ore_robots, new_clay, cur.clay_robots, new_obsidian, cur.obsidian_robots, new_geode, cur.geode_robots);
                    dp[j+1].insert(temp);
                }

                if (cur.ore >= blueprints[i].ore_cost && cur.ore_robots < blueprints[i].max_ore) {
                    Node temp(new_ore - blueprints[i].ore_cost, cur.ore_robots + 1, new_clay, cur.clay_robots, new_obsidian, cur.obsidian_robots, new_geode, cur.geode_robots);
                    dp[j+1].insert(temp);
                }

                if (cur.ore >= blueprints[i].clay_cost && cur.clay_robots < blueprints[i].obsisidan_clay_cost) {
                    Node temp(new_ore - blueprints[i].clay_cost, cur.ore_robots, new_clay, cur.clay_robots + 1, new_obsidian, cur.obsidian_robots, new_geode, cur.geode_robots);
                    dp[j+1].insert(temp);
                    // cout << "temp" << temp.ore << " " << temp.ore_robots << " " << temp.clay << " " << temp.clay_robots << " " << temp.obsidian << " " << temp.obsidian_robots << " " << temp.geodes << " " << temp.geode_robots << endl;
                }

                if (cur.ore >= blueprints[i].obsidian_ore_cost && cur.clay >= blueprints[i].obsisidan_clay_cost && cur.obsidian_robots < blueprints[i].geode_obsidian_cost) {
                    Node temp(new_ore - blueprints[i].obsidian_ore_cost, cur.ore_robots, new_clay - blueprints[i].obsisidan_clay_cost, cur.clay_robots, new_obsidian, cur.obsidian_robots + 1, new_geode, cur.geode_robots);
                    // cout << "temp2" << temp.ore << " " << temp.ore_robots << " " << temp.clay << " " << temp.clay_robots << " " << temp.obsidian << " " << temp.obsidian_robots << " " << temp.geodes << " " << temp.geode_robots << endl;
                    dp[j+1].insert(temp);
                }

                if (cur.ore >= blueprints[i].geode_ore_cost && cur.obsidian >= blueprints[i].geode_obsidian_cost) {
                    Node temp(new_ore - blueprints[i].geode_ore_cost, cur.ore_robots, new_clay, cur.clay_robots, new_obsidian - blueprints[i].geode_obsidian_cost, cur.obsidian_robots, new_geode, cur.geode_robots + 1);
                    dp[j+1].insert(temp);
                }

                // usleep(100000);
            }

            // cout << cur_max << endl;
        }

        cout << cur_max << endl;
        
        sol += cur_max * (i + 1);
    }

    cout << sol << endl;

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "time in microseconds " << duration.count() << endl;    
}
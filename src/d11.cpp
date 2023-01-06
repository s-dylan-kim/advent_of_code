#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Monkey {
    public:
    queue<long> items;
    char op;
    int op_end;
    int div_check;
    int true_throw;
    int false_throw;

    Monkey(vector<int> items, char op, int op_end, int div_check, int true_throw, int false_throw) {
        for (int i = 0; i < items.size(); i++) {
            this->items.push(items[i]);
        }
        this->op = op;
        this->op_end = op_end;
        this->div_check = div_check;
        this->true_throw = true_throw;
        this->false_throw = false_throw;
    }
};


int main(void)
{
    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");

    string in;
    int sol = 0;

    vector<Monkey*> monkies;
    vector<int> inspect_times;

    while (getline(file, in)) {
        // cout << in << endl;
        stringstream s(in);
        int item;
        vector<int> cur;
        while (s >> item) {
            cur.push_back(item);
        }
        char op_in;
        int div_check_in, op_end_in, true_throw_in, false_throw_in;
        file >> op_in >> op_end_in >> div_check_in >> true_throw_in >> false_throw_in;
        // cout <<  op_in << " " << op_end_in << " " << div_check_in << " " << true_throw_in << " " << false_throw_in << endl;
        monkies.push_back(new Monkey(cur, op_in, op_end_in, div_check_in, true_throw_in, false_throw_in));
        getline(file, in);
    }

    inspect_times.resize(monkies.size());

    for (int i = 0; i < 10000; i++) {
        for (int j = 0; j < monkies.size(); j++) {
            Monkey* cur = monkies[j];
            while (!cur->items.empty()) {
                inspect_times[j]++;
                long item = cur->items.front();
                cur->items.pop();

                switch(cur->op) {
                    case '*':
                        item *= cur->op_end;
                        break;
                    case '+':
                        item += cur->op_end;
                        break;
                    case '^':
                        // always ^2
                        item *= item;
                        break;
                }
                // div by 3 cause bored?
                item = item % 9699690;

                if (item % cur->div_check) {
                    (monkies[cur->false_throw])->items.push(item);
                    // cout << "monkey " << j << " threw " << item << " at monkey " << cur->false_throw << endl;
                } else {
                    (monkies[cur->true_throw])->items.push(item);
                    // cout << "monkey " << j << " threw " << item << " at monkey " << cur->true_throw << endl;
                }
            }
        }
    }

    for (int i = 0; i < inspect_times.size(); i++) {
        cout << inspect_times[i] << endl; 
    }

       
}
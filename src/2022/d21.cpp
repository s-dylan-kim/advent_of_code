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

class Node {
    public:
    bool is_int;
    long val;
    string a;
    string b;
    char op;
    bool has_humn;

    Node (string a, string b, char op) {
        this->is_int = false;
        this->a = a;
        this->b = b;
        this->op = op;
        has_humn = false;
    }

    Node (long val) {
        this->is_int = true;
        this->val = val;
        has_humn = false;
    }
};

unordered_map<string, Node*> map;

long get_val(string cur_str) {
    // cout << cur_str << endl;
    if (cur_str == "humn") {
        map["humn"]->is_int = true;
        map["humn"]->val = -1;
        map["humn"]->has_humn = true;
        return -1;
    }

    if (!map[cur_str]->is_int) {
        if (get_val(map[cur_str]->a) == -1 | get_val(map[cur_str]->b) == -1) {
            map[cur_str]->has_humn = true;
            map[cur_str]->val = -1;
            return -1;
        }

        long val;

        switch (map[cur_str]->op) {
            case '+':
                val = get_val(map[cur_str]->a) + get_val(map[cur_str]->b);
                break;
            case '-':
                val = get_val(map[cur_str]->a) - get_val(map[cur_str]->b);
                break;
            case '*':
                val = get_val(map[cur_str]->a) * get_val(map[cur_str]->b);
                break;
            case '/':
                val = get_val(map[cur_str]->a) / get_val(map[cur_str]->b);
                break;
        }

        if (cur_str == "vprg") {
            cout << "VPRG " << val << " " << endl;
        }
        map[cur_str]->is_int = true;
        map[cur_str]->val = val;
        return val;

    } else return map[cur_str]->val;
}

// bool check_humn(string cur_str) {
//     if (cur_str == "humn") return true;
//     if (map[cur_str]->is_int) return false;
//     return check_humn(map[cur_str]->a) || check_humn(map[cur_str]->b);
// }

long force_val(string cur_str, long val) {
    cout << cur_str << ": " << val << endl;

    if (cur_str == "humn") return val;

    if (map[map[cur_str]->a]->has_humn && map[map[cur_str]->b]->has_humn) {
        cout << "?????" << endl;
    }

    if (map[map[cur_str]->a]->has_humn) {
        switch (map[cur_str]->op) {
            case '+':
                cout << "adding " << map[cur_str]->a << " ? + " << map[map[cur_str]->b]->val << " = " << val << endl;
                return force_val(map[cur_str]->a, val - map[map[cur_str]->b]->val);
            case '-':
                cout << "subtracting  " << map[cur_str]->a << " ? - " << map[map[cur_str]->b]->val << " = " << val << endl;
                return force_val(map[cur_str]->a, val + map[map[cur_str]->b]->val);
            case '*':
                cout << "multiplying  " << map[cur_str]->a << " ? * " << map[map[cur_str]->b]->val << " = " << val << endl;
                if (map[map[cur_str]->b]->val == 0) return force_val(map[cur_str]->a, 0);
                return force_val(map[cur_str]->a, val / map[map[cur_str]->b]->val);
            case '/':
                cout << "divide  " << map[cur_str]->a << " ? / " << map[map[cur_str]->b]->val << " = " << val << endl;
                return force_val(map[cur_str]->a, val * map[map[cur_str]->b]->val);
        }
    } else {
        switch (map[cur_str]->op) {
            case '+':
                cout << "adding " << map[cur_str]->b << " " << map[map[cur_str]->a]->val << " + ? = " << val << endl;
                return force_val(map[cur_str]->b, val - map[map[cur_str]->a]->val);
            case '-':
                cout << "subtracting  " << map[cur_str]->b << " " << map[map[cur_str]->a]->val << " - ? = " << val << endl;
                return force_val(map[cur_str]->b, map[map[cur_str]->a]->val - val);
            case '*':
                cout << "multiplying  " << map[cur_str]->b << " " << map[map[cur_str]->a]->val << " * ? = " << val << endl;
                if (map[map[cur_str]->a]->val == 0) return force_val(map[cur_str]->b, 0);
                return force_val(map[cur_str]->b, val / map[map[cur_str]->a]->val);
            case '/':
                cout << "divide  " << map[cur_str]->b << " " << map[map[cur_str]->a]->val << " / ? = " << val << endl;
                if (val == 0) return force_val(map[cur_str]->b, 0);
                return force_val(map[cur_str]->b, map[map[cur_str]->a]->val / val);
        }
    }

    return -1;
}

int main(void)
{
    auto start = chrono::high_resolution_clock::now();


    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");

    string in;
    int sol = 0;

    


    while (getline(file, in)) {

        stringstream s(in);

        string name;
        s >> name;

        long val;
        s >> val;

        // cout << "Node" << endl;

        if (!s.fail()) {
            // cout << val << endl;
            map[name] = new Node(val);
        } else {
            stringstream alt(in);
            string a;
            string b;
            char op;
            alt >> name >> a >> op >> b;
            map[name] = new Node(a, b, op);
        }
    }

    cout << get_val(map["root"]->a) << " " << get_val(map["root"]->b) << endl;

    long target_val = 5697586809113;

    long sol2 = force_val(map["root"]->a, 5697586809113);

    cout << sol2 << endl;


    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "time in seconds " << duration.count() << endl;    
}
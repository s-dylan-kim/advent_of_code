#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <list>
#include <unistd.h>
using namespace std;


class Linked_List_Node {
    public:
    long val;
    Linked_List_Node* next;
    Linked_List_Node* prev;

    Linked_List_Node (long val, Linked_List_Node* next, Linked_List_Node* prev) {
        this->val = val;
        this->next = next;
        this->prev = prev;
    }
};

int main(void)
{
    auto start = chrono::high_resolution_clock::now();


    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");

    long in;
    long sol = 0;

    Linked_List_Node* head = NULL;
    Linked_List_Node* cur = NULL;

    Linked_List_Node* zero = NULL;

    vector<Linked_List_Node*> order;

    while (file >> in) {
        // cout << "hello" << endl;

        if (head == NULL) {
            // cout << "1" << endl;
            head = new Linked_List_Node(in * 811589153, NULL, NULL);
            cur = head;
        } else {
            // cout << "2" << endl;
            cur->next = new Linked_List_Node(in * 811589153, NULL, cur);
            cur = cur->next;
        }

        if (in == 0) zero = cur;

        order.push_back(cur);
    }

    cur->next = head;
    head->prev = cur;
    
    // cout << order.size() - 1;
    for (int o = 0; o < 10; o++) {
        for (long i = 0; i < order.size(); i++) {
            Linked_List_Node* orig_node = order[i];
            long val = orig_node->val;
            val = val % (long)(order.size() - 1);
            if (val < 0) val += (order.size() - 1);


            // cout << orig_node->val << " " << val << endl;

            if (val == 0) continue;

            Linked_List_Node* cur_node = orig_node;

            orig_node->prev->next = orig_node->next; // remove node
            orig_node->next->prev = orig_node->prev;


            for (long j = 0; j < val; j++) {
                cur_node = cur_node->next;
            }

            orig_node->next = cur_node->next;
            orig_node->prev = cur_node;

            orig_node->next->prev = orig_node;
            cur_node->next = orig_node;

            // cur = zero;

            // long k = 0;
            // while (cur->next != zero) {
            //     cout << k << ": " << cur->val << endl;
            //     // if (k % 1000 == 0) {
            //     //     cout << cur->val << endl;
            //     // }
            //     cur = cur->next;
            //     k++;
            // }
            // cout << k << ": " << cur->val << endl << endl;
        }
    }

    cur = zero->next;

    for (long k = 1; k <= 3000; k++) {
        // cout << k << ": " << cur->val << endl;
        if (k % 1000 == 0) {
            cout << cur->val << endl;
        }
        cur = cur->next;
    }

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "time in seconds " << duration.count() << endl;    
}
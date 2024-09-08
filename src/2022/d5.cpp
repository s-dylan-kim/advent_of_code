#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
using namespace std;

int main(void)
{
    std::ifstream file("../input_long.txt");
    int in;
    int sol = 0;

    vector<stack<char>> stacks;

    vector<int> test;

    stack<char> temp_stack;

    test.push_back(4);

    for (int i = 0; i < 9; i++) {
        
        stacks.push_back(stack<char>());
    }

    stacks[0].push('F');
    stacks[0].push('D');
    stacks[0].push('B');
    stacks[0].push('Z');
    stacks[0].push('T');
    stacks[0].push('J');
    stacks[0].push('R');
    stacks[0].push('N');

    stacks[1].push('R');
    stacks[1].push('S');
    stacks[1].push('N');
    stacks[1].push('J');
    stacks[1].push('H');

    stacks[2].push('C');
    stacks[2].push('R');
    stacks[2].push('N');
    stacks[2].push('J');
    stacks[2].push('G');
    stacks[2].push('Z');
    stacks[2].push('F');
    stacks[2].push('Q');

    stacks[3].push('F');
    stacks[3].push('V');
    stacks[3].push('N');
    stacks[3].push('G');
    stacks[3].push('R');
    stacks[3].push('T');
    stacks[3].push('Q');

    stacks[4].push('L');
    stacks[4].push('T');
    stacks[4].push('Q');
    stacks[4].push('F');

    stacks[5].push('Q');
    stacks[5].push('C');
    stacks[5].push('W');
    stacks[5].push('Z');
    stacks[5].push('B');
    stacks[5].push('R');
    stacks[5].push('G');
    stacks[5].push('N');

    stacks[6].push('F');
    stacks[6].push('C');
    stacks[6].push('L');
    stacks[6].push('S');
    stacks[6].push('N');
    stacks[6].push('H');
    stacks[6].push('M');

    stacks[7].push('D');
    stacks[7].push('N');
    stacks[7].push('Q');
    stacks[7].push('M');
    stacks[7].push('T');
    stacks[7].push('J');

    stacks[8].push('P');
    stacks[8].push('G');
    stacks[8].push('S');

    string junk;
    string junk2;
    string junk3;

    int in2;
    int in3;

    while (file >> junk >> in >> junk2 >> in2 >> junk3 >> in3) {
        for (int i = 0; i < in; i++) {
            temp_stack.push(stacks[in2 - 1].top());
            stacks[in2-1].pop();
        }

        while (!temp_stack.empty()) {
            stacks[in3-1].push(temp_stack.top());
            temp_stack.pop();
        }
        
    }

    for (int i = 0; i < 9; i++) {
        std::cout << stacks[i].top() << std::endl;
    }

    
}

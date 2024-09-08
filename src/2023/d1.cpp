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


int checkWord(string curString, int idx) {
    vector<string> words{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    for (int i = 0; i < words.size(); i++) {
        bool flag = true;
        for (int j = words[i].size() - 1; j >= 0; j--) {
            if (idx - j < 0) {
                flag = false;
                break;
            }
            if (curString[idx - j] != words[i][words[i].size() - 1 - j]) {
                flag = false;
                break;
            }
        }
        if (flag) return i + 1;
    }
    return 0;

} 


int main(void)
{
    auto start = chrono::high_resolution_clock::now();


    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");

    string in;
    int sol = 0;

    while (file >> in) {
        int cur = 0;

        for (int i = 0; i < in.size(); i++) {
            if (isdigit(in[i])){
                cur = (in[i] - '0') * 10;
                break;
            }

            int temp = checkWord(in, i);
            if (temp) {
                cur = temp * 10;
                break;
            }
            
        }

        for (int i = in.size() - 1; i >= 0; i--) {
            if (isdigit(in[i])){
                cur += (in[i] - '0');
                break;
            }

            int temp = checkWord(in, i);
            if (temp) {
                cur += temp;
                break;
            }
        }

        cout << cur << endl;

        sol += cur;
    }

    cout << sol << endl;



    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "time in seconds " << duration.count() << endl;    
}
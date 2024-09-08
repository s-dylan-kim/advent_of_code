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
    int sol = 0;

    vector<int> cardCount;
    cardCount.push_back(0);

    int curCard = 1;
    while (getline(file, in)) {
        if (curCard >= cardCount.size()) {
            cardCount.push_back(1);
        } else {
            cardCount[curCard]++;
        }

        int numWins = 0;
        int cardScore = 0;

        stringstream s(in);
        string trash;
        s >> trash >> trash;

        vector<int> winningNums;

        int num;
        while (s >> num) {
            winningNums.push_back(num);
        }

        s.clear();

        s >> trash;

        vector<int> nums;
        while (s >> num) {
            nums.push_back(num);

            for (int i = 0; i < winningNums.size(); i++) {
                if (winningNums[i] == num) {
                    numWins++;
                    if (cardScore) cardScore *= 2;
                    else cardScore = 1;
                    break;
                }
            }
        }

        // cout << "card " << curCard << ": " << numWins << endl;
        for (int i = 1; i <= numWins; i++) {
            if (curCard + i < cardCount.size()) {
                cardCount[curCard + i] += cardCount[curCard];
            }
            else {
                cardCount.push_back(cardCount[curCard]);
            }
        }

        // cout << cardScore << endl;
        sol += cardScore;
        curCard++;
    }

    int sol2 = 0;
    for (int i = 0; i < cardCount.size(); i++) {
        // cout << "card " << i << ": " << cardCount[i] << endl;
        sol2 += cardCount[i];
    }

    cout << sol << endl;
    cout << sol2 << endl;



    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "time in seconds " << duration.count() << endl;    
}
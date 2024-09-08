#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
using namespace std;

bool sortCards(const tuple<vector<int>, int, int>& a,  
               const tuple<vector<int>, int, int>& b) 
{ 
    if (get<2>(a) != get<2>(b)) {
        return get<2>(a) < get<2>(b);
    } else {
        for (int i = 0; i < get<0>(a).size(); i++) {
            if (get<0>(a)[i] != get<0>(b)[i]) {
                return get<0>(a)[i] < get<0>(b)[i];
            }
        }
    }
    return 0;
} 

int main(void)
{
    auto start = chrono::high_resolution_clock::now();


    ifstream file("/mnt/c/Users/sdyla/Advent/input_long.txt");

    string hand;
    int val;
    long sol = 0;

    vector<tuple<vector<int>, int, int>> hands;

    while (file >> hand >> val) {
        vector<int> handArray;
        for (int i = 0; i < 5; i++) {
            switch (hand[i]) {
                case 'A':
                    handArray.push_back(14);
                    break;
                case 'K':
                    handArray.push_back(13);
                    break;
                case 'Q':
                    handArray.push_back(12);
                    break;
                case 'J':
                    handArray.push_back(11);
                    break;
                case 'T':
                    handArray.push_back(10);
                    break;
                default:
                    handArray.push_back(hand[i] - '0');
                    break;
            }
        }
        
        int handRank = 0;
        int pairCnt = 0;
        int largestMatch = 1;
        int curMatch = 0;
        char currentChar = 0;

        string handCopy = hand;
        sort(handCopy.begin(), handCopy.end());


        for (int i = 1; i < handCopy.size(); i++) {
            if (handCopy[i] == handCopy[i-1]) {
                if (handCopy[i] == currentChar) {
                    curMatch++;
                } else {
                    curMatch = 2;
                    pairCnt++;
                    currentChar = handCopy[i];
                }
                if (curMatch > largestMatch) {
                    largestMatch = curMatch;
                }
            }
        }

        switch (largestMatch) {
            case 5:
                handRank = 6;
                break;
            case 4:
                handRank = 5;
                break;
            case 3:
                handRank = pairCnt == 2 ? 4 : 3;
                break;
            case 2:
                handRank = pairCnt == 2 ? 2 : 1;
                break;
            default:
                handRank = 0; 
        }
        hands.push_back(make_tuple(handArray, val, handRank));
    }

    sort(hands.begin(), hands.end(), sortCards);

    for (int i = 0; i < hands.size(); i++) {
        sol += (long)get<1>(hands[i]) * (i + 1);
    }

    cout << sol << endl;



    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "time in seconds " << duration.count() << endl;    
}
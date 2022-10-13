/*
 * File: word-chain.cpp
 * --------------------
 * Evana Pradhan
 * Consulted Roxy
 *
 * Assignment 2: word chain
 */

#include <iostream>
#include <vector>
#include <queue>
#include "util.h"
using namespace std;

int main()
{
    string start, end;

    while (true)
    {
        start = getLine("Enter start word: (RETURN to quit): ");
        if (start.empty())
            break;
        end = getLine("Enter end word: (RETURN to quit): ");
        if (end.empty())
            break;

        // boolean value to determine if solution is found 
        bool solFound = false;

        // Importing EnglishWords.txt and breaking if target word does not exist in the list of english words
        Lexicon wordsList("EnglishWords.txt");

        // Initialization of queue for BFS
        queue<vector<string>> chains;

        // Pushing the starting word into the queue<vector<string>> chains
        vector<string> init;
        init.push_back(start);
        chains.push(init);

        // Vector to store all used words
        Lexicon usedWords;
        usedWords.add(start);

        // Empty vector to store around solution
        vector<string> sol;

        while (!chains.empty()) {
            vector<string> copy = chains.front();
            chains.pop();

            string lastWord = copy[copy.size() - 1];

            if (lastWord == end) {
                solFound = true;
                sol = copy;
                for (int i = 0; i < sol.size(); i++) {
                    if (i != 0) cout << " -> ";
                    cout << sol[i];
                }
                cout << endl;
                break;
            }

            for (int i = 0; i <= lastWord.size() - 1; i++) {
                for (char c = 'a'; c <= 'z'; c++) {
                    string copyTwo = lastWord;
                    copyTwo[i] = c;
                    if (wordsList.contains(copyTwo) && (!usedWords.contains(copyTwo))) {
                        vector<string> copyThree = copy;
                        copyThree.push_back(copyTwo);
                        usedWords.add(copyTwo);
                        chains.push(copyThree);
                    }
                }
            }
        }

        if (!solFound) {
            cout << "No word chains found!" << endl;
        }
    }
    cout << "Goodbye." << endl;
}

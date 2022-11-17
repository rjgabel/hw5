// For debugging
#include <iostream>
// For std::remove
#include "dict-eng.h"
#include "wordle.h"
#include <algorithm>
#include <map>
#include <set>
using namespace std;

void wordle_helper(string& word, string floating, const set<string>& dict,
                   set<string>& words, size_t n);

// Definition of primary wordle function
std::set<std::string> wordle(const std::string& in, const std::string& floating,
                             const std::set<std::string>& dict) {
    set<string> words;
    string word = in;
    wordle_helper(word, floating, dict, words, 0);
    return words;
}

void wordle_helper(string& word, string floating, const set<string>& dict,
                   set<string>& words, size_t n) {
    if (word.size() <= n) {
        // Check whether the word is valid
        if (floating.empty() && dict.count(word)) {
            words.insert(word);
        }
    } else {
        if (word[n] == '-') {
            if (word.size() <= n + floating.size()) {
                for (size_t i = 0; i < floating.size(); i++) {
                    word[n] = floating[i];
                    string new_floating = floating;
                    new_floating.replace(i, 1, "");
                    wordle_helper(word, new_floating, dict, words, n + 1);
                }
            } else {
                for (char c = 'a'; c <= 'z'; c++) {
                    word[n] = c;
                    auto i = floating.find(c);
                    if (i != string::npos) {
                        floating.replace(i, 1, "");
                        wordle_helper(word, floating, dict, words, n + 1);
                        floating.push_back(c);
                    } else {
                        wordle_helper(word, floating, dict, words, n + 1);
                    }
                }
            }
            word[n] = '-';
        } else {
            wordle_helper(word, floating, dict, words, n + 1);
        }
    }
}

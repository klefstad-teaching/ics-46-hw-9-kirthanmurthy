#include "ladder.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <string>

using namespace std;

void error(string word1, string word2, string msg) {
    cerr << "Error with '" << word1 << "' and '" << word2 << "': " << msg << endl;
}


bool one_sub(const string& a, const string& b) {
    int diff = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) {
            ++diff;
            if (diff > 1)
                return false;
        }
    }
    return diff == 1;
}

bool one_insert(const string& short_str, const string& long_str) {
    size_t i = 0;
    size_t j = 0;
    bool found = false;
    while (i < short_str.size() && j < long_str.size()) {
        if (short_str[i] != long_str[j]) {
            if (found) {
                return false;
            }
            found = true;
            ++j; 
        } 
        else {
            ++i;
            ++j;
        }
    }
    return true;
}

bool one_edit(const string& s1, const string& s2) {
    if (s1.size() == s2.size()) {
        return one_sub(s1, s2);
    }
    else if (s1.size() + 1 == s2.size()) {
        return one_insert(s1, s2);
    }
    else if (s1.size() == s2.size() + 1) {
        return one_insert(s2, s1);
    }
    else {
        return false;
    }
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    if (d == 0) {
        return str1 == str2;
    }
    if (d == 1) {
        return one_edit(str1, str2);
    }
    return false;
}

bool is_adjacent(const string& word1, const string& word2) {
    if (word1 == word2) {
        return false;
    }
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        error(begin_word, end_word, "start and end words are the same");
        return {};
    }
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        for (const string& word : word_list) {
            if (is_adjacent(last_word, word)) {
                if (visited.find(word) == visited.end()) {
                    visited.insert(word);  
                    vector<string> new_ladder = ladder;  
                    new_ladder.push_back(word);       
                    if (word == end_word) {
                        return new_ladder;
                    }
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    return {};
}


void load_words(set<string>& word_list, const string& file_name) {
    ifstream f(file_name);
    if (!f) {
        cerr << "can't open file: " << file_name << endl;
        return;
    }
    string word;
    while (f >> word) {
        for (auto& c : word) {
            c = tolower(c);
        }
        word_list.insert(word);
    }
    f.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found.\n";
    } else {
        cout << "Word ladder found: ";
        for (const string& w : ladder) {
            cout << w << " ";
        }
        cout << "\n";
    }
}
#include "ladder.h"
#include <iostream>
#include <string>
#include <set>
using namespace std;

int main() {
    string start_word, end_word;
    cout << "start word: ";
    cin >> start_word;
    cout << "end word: ";
    cin >> end_word;

    for (char& c : start_word) {
        c = tolower(c);
    }

    for (char& c : end_word) {
        c = tolower(c);
    }

    if (start_word == end_word) {
        error(start_word, end_word, "start and end words are the same.");
        return 1;
    }

    set<string> word_list;
    load_words(word_list, "src/words.txt");

    if (word_list.find(end_word) == word_list.end()) {
        error(start_word, end_word, "end word not in dictionary");
        return 1;
    }

    vector<string> ladder = generate_word_ladder(start_word, end_word, word_list);

    if (ladder.empty()) {
        cout << "no word ladder found." << endl;
    } 
    else {
        print_word_ladder(ladder);
    }

    return 0;
}
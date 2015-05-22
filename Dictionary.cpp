#include "Dictionary.h"

#include <istream>
#include <cctype>

unsigned inline Dictionary::index(char c) {
  return c - FIRST;
}

bool Dictionary::processWord(std::string* word) {
  for (char& c : *word) {
    if (!isalpha(c)) return false;

    c = tolower(c);
  }

  return true;
}

Dictionary::Dictionary(std::istream& is) {
  readFromStream(is);
}

void Dictionary::readFromStream(std::istream& is) {
  std::string word;

  NextWord:
  while (is >> word) {
    if (processWord(&word)) insert(word);
  }
}

unsigned Dictionary::insert(const std::string& str) {
  Node* cur = &root_;

  for (char c : str) {
    Node** next = &cur->children[index(c)];

    if (*next == nullptr) {
      *next = new Node();
    }

    cur = *next;
  }

  return ++(cur->count);
}

unsigned Dictionary::count(const std::string& str) const {
  const Node* cur = &root_;

  for (char c : str) {
    cur = cur->children[index(c)];
    
    if (cur == nullptr) return false;
  }

  return cur->count;
}

// Test code

#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
  using namespace std;

  string input;
  Dictionary dict;
  
  if (argc == 2) { // read from file
    std::ifstream file(argv[1]);

    cout << "Reading in " << argv[1] << "... ";
    dict.readFromStream(file);
    cout << "Done!" << endl;

    while (getline(cin, input)) {
      if (Dictionary::processWord(&input)) {
        cout << input << " is in there " << dict.count(input) << " times" << endl;
      }
    }
  }
  else { // read from prompt
    do {
      getline(cin, input);

      if (Dictionary::processWord(&input)) {
        cout << input << " added, now in there " << dict.insert(input) << " times" << endl;
      }
    }
    while (input != "done");

    do {
      getline(cin, input);

      if (Dictionary::processWord(&input)) {
        cout << input << " is in there " << dict.count(input) << " times" << endl;
      }
    }
    while (input != "quit");
  }
}

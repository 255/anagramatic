#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>

#include <stack>

/*  A trie to store words. Store and look up words.
 *  This is not memory-friendly; each node stack-allocates an array of 26 pointers.
 */
class Dictionary {
  static const unsigned CHARS = 26;
  static const char FIRST = 'a';

  /* A letter in the trie.
   * Deleting a node deletes all of its children.
   */
  struct Node {
    unsigned count;
    Node* children[CHARS];

    Node() : count(0), children{nullptr} {}

    ~Node() {
      for (Node* child : children) {
        delete child;
      }
    }
  };

  Node root_;

  /*
   * Read in words from an input stream.
   * Words are whitespace-separated and words with 'special' characters are ignored.
   */
  static unsigned inline index(char c);

public:
  class Iterator;

  Iterator iterator() const;

  class Iterator {
    std::stack<const Node*> history_;
    std::string word_;

    Iterator(const Node* root);

    // give Dictionary access to the private constructor
    friend Dictionary::Iterator Dictionary::iterator() const;

  public:
    /* Advance to the next character in the trie.
     * If it cannot advance, it returns false and does nothing.
     */
    bool move(char c);
    bool back();

    const std::string& word() const {
      return word_;
    }

    bool isWord() const {
      return history_.top()->count > 0;
    }
  };

  /* Prepare a word for insertion. Returns false if invalid. */
  static bool processWord(std::string* word);

  Dictionary() {}

  Dictionary(std::istream& is);

  void readFromFile(std::istream& is);

  /* Insert a word into the trie.
   * Only characters a-z should be used.
   * No bounds checking is performed on the characters!
   */
  unsigned insert(const std::string& str);

  unsigned count(const std::string& str) const;

  bool contains(const std::string& str) const {
    return count(str) > 0;
  }
};

#endif

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>

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
  /* Prepare a word for insertion. Returns false if invalid. */
  static bool processWord(std::string* word);

  Dictionary() {}

  Dictionary(std::istream& is);

  void readFromStream(std::istream& is);

  /* Insert a word into the trie.
   * Only characters a-z should be used.
   * No bounds checking is performed on the characters!
   */
  unsigned insert(const std::string& str);

  unsigned count(const std::string& str) const;
};

#endif

#ifndef CHARCOUNTER_H
#define CHARCOUNTER_H

#include <ostream>
#include <string>

/*
 * Keep track of the counts of characters in a string.
 * Stores a string of the unique characters and their counts.
 * This was designed for use with a permutation-finder function.
 */
class CharCounter {
  static const unsigned CHARS = 26;
  static const char FIRST = 'a';

  // the unique characters present in the counter
  // these are stored in the order they were added
  char contents[CHARS] = {'\0'};
  unsigned unique_chars = 0;

  // the counts of each character present
  int counts[CHARS] = {0};
  unsigned total = 0;

public:
  CharCounter() {};

  CharCounter(const std::string& str);

  void add(char ch);

  void remove(unsigned index);

  /* Restore the character that was removed from this index into the list of unique chars.
   * This replaces the character to the unique chars list if needed
   * This is for use in permutation-finding.
   */
  void restore(char ch, unsigned index);

  // accessors

  unsigned count(char ch) const {
    return counts[ch - FIRST];
  }

  unsigned unique() const {
    return unique_chars;
  }

  unsigned size() const {
    return total;
  }

  bool empty() const {
    return total == 0;
  }

  char operator[](unsigned index) const {
    return contents[index];
  }
  
  // iterators
  typedef const char* const_iterator;

  const_iterator begin() const { return contents; }
  const_iterator cbegin() const { return contents; }
  const_iterator end() const { return &contents[unique_chars]; }
  const_iterator cend() const { return &contents[unique_chars]; }
};

std::ostream& operator<<(std::ostream& os, const CharCounter& counter);

#endif

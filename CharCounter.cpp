#include "CharCounter.h"

CharCounter::CharCounter(const std::string& str) {
  for (char ch : str) {
    add(ch);
  }
}

void CharCounter::add(char ch) {
  if (counts[ch - FIRST]++ == 0) {
    contents[unique_chars++] = ch;
  }

  total += 1;
}

void CharCounter::remove(unsigned index) {
  if (--counts[contents[index] - FIRST] == 0) {
    std::swap(contents[index], contents[unique_chars-1]);
    unique_chars -= 1;
  }

  total -= 1;
}

void CharCounter::restore(char ch, unsigned index) {
  if (counts[ch - FIRST]++ == 0) {
    //if (contents[unique_chars] != ch) {
    //  std::cerr << "BAD THINGS HAVE HAPPENED! " << std::endl;
    //}

    contents[unique_chars++] = contents[index];
    contents[index] = ch;
  }

  total += 1;
}

std::ostream& operator<<(std::ostream& os, const CharCounter& counter) {
  os << "{ ";
  for (char c : counter) {
    os << c << '=' << counter.count(c) << ' ';
  }
  os << '}';

  return os;
}



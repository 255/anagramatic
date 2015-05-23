#ifndef PERMUTATOR_H
#define PERMUTATOR_H

#include <string>

#include "CharCounter.h"

#include <iostream>
#include <iomanip>
void output(std::string& result) {
  static unsigned long count = 0;
  std::cout << std::setw(10) << ++count << ": " << result << std::endl;
}

void permutations(std::string* remaining) {
  static std::string working;

  if (remaining->size() == 0) {
    output(working);
    return;
  }

  for (int i = 0; i < remaining->size(); ++i) {
    char ch = (*remaining)[i];
    working.push_back(ch);

    remaining->erase(i, 1);

    permutations(remaining);

    working.pop_back();
    remaining->insert(i, 1, ch);
  }
}

void uniquePermutations(CharCounter* counter) {
  static std::string working;

  if (counter->empty()) {
    output(working);
    return;
  }

  for (int i = 0; i < counter->unique(); ++i) {
    char ch = (*counter)[i];
    working.push_back(ch);

    counter->remove(i);

    uniquePermutations(counter);

    working.pop_back();
    counter->restore(ch, i);
  }
}

void permutations(const std::string& str) {
  std::string remaining(str);
  permutations(&remaining);
}

void uniquePermutations(const std::string& str) {
  CharCounter counter(str);
  uniquePermutations(&counter);
}

#endif

int main(int argc, char* argv[]) {
  for (int i = 1; i < argc; ++i) {
    //permutations(argv[1]);
    uniquePermutations(argv[1]);
  }
}

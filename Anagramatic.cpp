#include <string>
#include <iostream>
#include <iomanip>

#include "CharCounter.h"
#include "Dictionary.h"

void output(const std::string& result) {
  static unsigned long count = 0;
  std::cout << std::setw(10) << ++count << ": " << result << std::endl;
}

void findAnagrams(Dictionary::Iterator* it, CharCounter* counter) {
  if (counter->empty() && it->isWord()) {
    output(it->word());
    return;
  }

  for (unsigned i = 0; i < counter->unique(); ++i) {
    char ch = (*counter)[i];

    if (it->move(ch)) {
      counter->remove(i);

      findAnagrams(it, counter);

      counter->restore(ch, i);
      it->back();
    }
  }
}

#include <fstream>

int main(int argc, char* argv[]) {
  std::ifstream wordlist("american-english");
  Dictionary dict(wordlist);

  for (int i = 1; i < argc; ++i) {
    CharCounter counter(argv[i]);
    std::cout << argv[i] << ": " << counter << std::endl;

    Dictionary::Iterator it(dict.iterator());

    findAnagrams(&it, &counter);
  }
}

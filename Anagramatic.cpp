#include <string>
#include <vector>

#include <iostream>
#include <iomanip>

#include "CharCounter.h"
#include "Dictionary.h"

static Dictionary dict;

void output(const std::string& result, const std::vector<std::string>& prefixes = {}) {
  static unsigned long count = 0;
  std::cout << std::setw(10) << ++count << ": ";

  for (const std::string& prefix : prefixes) {
    std::cout << prefix << " ";
  }
  
   std::cout << result << std::endl;
}

void findAnagrams(Dictionary::Iterator* it, CharCounter* counter) {
  if (counter->empty()) {
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

void findMultiwordAnagrams(Dictionary::Iterator* it, CharCounter* counter, std::vector<std::string>* prefixes) {
  if (counter->empty() && it->isWord()) {
    output(it->word(), *prefixes);
    return;
  }

  for (unsigned i = 0; i < counter->unique(); ++i) {
    char ch = (*counter)[i];

    if (it->move(ch)) {
      counter->remove(i);

      if (it->isWord()) {
        Dictionary::Iterator new_it(dict.iterator());
        
        prefixes->emplace_back(it->word());

        findMultiwordAnagrams(&new_it, counter, prefixes);

        prefixes->pop_back();
      }

      findMultiwordAnagrams(it, counter, prefixes);

      counter->restore(ch, i);
      it->back();
    }
  }
}

#include <fstream>

int main(int argc, char* argv[]) {
  std::ifstream wordlist("good_dictionary");
  dict.readFromFile(wordlist);

  for (int i = 1; i < argc; ++i) {
    CharCounter counter(argv[i]);
    std::cout << argv[i] << ": " << counter << std::endl;

    Dictionary::Iterator it(dict.iterator());

    //findAnagrams(&it, &counter);
    std::vector<std::string> prefixes;
    findMultiwordAnagrams(&it, &counter, &prefixes);
  }
}

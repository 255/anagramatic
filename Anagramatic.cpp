#include "CharCounter.h"
#include "Dictionary.h"

#include <string>
#include <vector>
#include <iostream>

#include <fstream>

static Dictionary dict;

void output(const std::string& result, const std::vector<std::string>& prefixes = {}) {
  for (const std::string& prefix : prefixes) {
    std::cout << prefix << " ";
  }
  
   std::cout << result << std::endl;
}

void findAnagrams(Dictionary::Iterator* it, CharCounter* counter) {
  if (counter->empty()) {
    if (it->isWord()) output(it->word());
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
  if (counter->empty()) {
    if (it->isWord()) output(it->word(), *prefixes);
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

void printUsage(const char* prog_name) {
  std::cerr << "Find all anagrams of a word or phrase. The anagrams are output one per line.\n"
            << "\n"
            << "Usage:\n"
            << "\t" << prog_name << " [-s] [-d DICTIONARY_FILE] PHRASE...\n"
               "\n"
               "\tPHRASE\tThe word or words of which to find anagrams.\n"
               "\n"
               "\t-d\tSpecify which dictionary file to use. Default: \"dictionary\"\n"
               "\t-h\tDisplay this message. In case you forgot something?\n"
               "\t-s\tOnly find single-word anagrams.\n"
            << std::endl;
}

template<typename T>
bool parseOptions(int argc, char* argv[], T* settings) {
  for (int i = 1; i < argc; ++i) {
    if (argv[i][0] == '-') {
      for (char *c = &argv[i][1]; *c != '\0'; ++c) {
        switch (*c) {
        case 'd':
          if (i < (argc-1)){
            settings->dictionary = argv[++i];
          }
          else {
            printf("No value provided for -%c option.\n", *c);
            return false;
          }
          break;
        case 'h': printUsage(argv[0]); return false;
        case 's': settings->single_word = true; break;
        default:
          printf("Unknown option \"%s\".\n", argv[i]);
          printUsage(argv[0]);
          return false;
        }
      }
    }
    else {
      settings->phrase += argv[i];
    }
  }

  return true;
}

int main(int argc, char* argv[]) {
  using namespace std;

  struct {
    bool single_word = false;
    std::string dictionary = "dictionary";
    std::string phrase;
  } settings;

  if (!parseOptions(argc, argv, &settings)) {
    return 1;
  }

  if (!Dictionary::processWord(&settings.phrase)) {
    cerr << "Illegal character in " << settings.phrase
         << ". Only the 26 characters of the Latin alphabet are allowed." << endl;
    return 1;
  }

  std::ifstream wordlist(settings.dictionary);

  if (!wordlist.is_open()) {
    cerr << "Cannot find dictionary file \"" << settings.dictionary << "\"." << endl;
    return 1;
  }

  dict.readFromFile(wordlist);

  CharCounter counter(settings.phrase);
  Dictionary::Iterator it(dict.iterator());
if (settings.single_word) {
    findAnagrams(&it, &counter);
  }
  else {
    std::vector<std::string> prefixes;
    findMultiwordAnagrams(&it, &counter, &prefixes);
  }

  return 0;
}

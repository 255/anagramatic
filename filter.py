#!/usr/bin/python3.4

import string

letters = set(string.ascii_lowercase)
banned_words = {
  'fer',
  'hep',
  'len',
  'lin',
  'fahd',
  'rte',
}

min_length = 4
valid_two_letter = {
  'a', 'i',
  'ab', 'ad', 'ah', 'ai', 'am', 'an', 'as', 'at', 'aw', 'ax',
  'be', 'by',
  'do',
  'eh', 'em', 'en', 'er', 'ex',
  'go',
  'ha', 'hi', 'ho',
  'if', 'in', 'is', 'it',
  'ma', 'me', 'my'
  'no',
  'of', 'oh', 'on', 'or', 'ow', 'ox', 'oy',
  'pa', 'pi',
  'so',
  'to',
  'uh', 'um', 'up', 'us',
  'we', 'wo',
  'ye', 'yo',
}

vowels = {'a', 'e', 'i', 'o', 'u', 'y'}

def valid_short_word(word):
  if len(word) <= 2:
    return word in valid_two_letter

  # check for at least one vowel for words longer than 2 letters
  for letter in word:
    if letter in vowels:
      return True
  else:
    return False

# filter a list of words to make it more sensible
def filter(file):
  valid_words = set()

  for word in file.read().split():
    word = word.lower()

    if word in banned_words:
      continue

    if len(word) < min_length and not valid_short_word(word):
      continue

    for char in word:
      if char not in letters:
        break
    else:
      valid_words.add(word)

  return sorted(valid_words)
 

if __name__ == '__main__':
  import sys

  for word in filter(sys.stdin):
    print(word)

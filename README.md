# Anagramatic
Find all anagrams of a word or phrase. The anagrams are output one per line.

```
Usage:
	./test [-s] [-d DICTIONARY_FILE] PHRASE...

	PHRASE	The word or words of which to find anagrams.

	-d	Specify which dictionary file to use. Default: "dictionary"
	-h	Display this message. In case you forgot something?
	-s	Only find single-word anagrams.
```

## Compiling
Build with `make` or with something like `g++ -std=c++11 -O3 *.cpp -o Anagramatic`.

## Examples
```
$ ./Anagramatic -s mountaineers
mountaineers
enumerations
```

```
$ ./Anagramatic git hub
hit bug
hug bit
hut big
ugh bit
big hut
bit ugh
bit hug
bug hit
```

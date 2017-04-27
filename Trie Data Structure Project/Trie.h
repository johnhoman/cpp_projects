#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <map>
#include "TrieNode.h"
#include "ArrayStack.h"
class Trie{

private:
	TrieNode* root;
	ArrayStack A;
public:
	Trie(void);

	void deleteString(std::string str, TrieNode* node);

	void insertString(std::string str,TrieNode* node);

	bool stringExists(std::string str,TrieNode* node);

	void printStrings(TrieNode* node);

	void printStrings();

	TrieNode* getRoot();
};
#endif

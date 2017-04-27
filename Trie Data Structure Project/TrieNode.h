#ifndef TRIENODE_H
#define TRIENODE_H
#include <vector>
class TrieNode{
private:
	bool root;

	TrieNode* parent;

	bool strInTrie;

	//std::vector<TrieNode*> children;
	TrieNode* children[26];

public:
	TrieNode(void);

	TrieNode(TrieNode* parent);

	bool isExternal;

	void setRoot(bool val);

	bool isRoot();

	void getParent();

	TrieNode* getChild(char i);

	void setChild(char i,TrieNode* node);

	bool isStrInTrie();

	void setStringInTrie(bool val);
};

#endif

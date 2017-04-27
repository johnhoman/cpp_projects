#include "TrieNode.h"
#include <iostream>
#include <stdexcept>

TrieNode::TrieNode(TrieNode* parent){
	this->parent = parent;
	this->root = false;
	this->strInTrie = false;
	this->isExternal = true;
}
TrieNode::TrieNode(){
	this->parent = NULL;
	this->root = false;
	this->strInTrie = false;
	this->isExternal = true;
}
void TrieNode::setChild(char i,TrieNode* node){
	if (i - 'a' >= 0 && i - 'a' < 26){
		children[i - 'a'] = node;
		this->isExternal = false;
	}
	else
		throw std::out_of_range("Error::Cannot set node, index out of range");
}
TrieNode* TrieNode::getChild(char i){
	if (i - 'a' >= 0 && i - 'a' < 26)
		return children[i - 'a'];
	else
		throw std::out_of_range("Error::Invalid child request");
}
void TrieNode::setStringInTrie(bool val){
	this->strInTrie = val;
}
bool TrieNode::isStrInTrie(){
	return strInTrie;
}
void TrieNode::setRoot(bool val){
	this->root = val;
}
bool TrieNode::isRoot(){
	return root;
}

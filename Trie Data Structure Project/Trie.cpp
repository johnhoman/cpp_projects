#include "Trie.h"
#include "ArrayStack.h"
#include <iostream>
#include <string>

Trie::Trie(){
	this->root = new TrieNode();
	this->root->setRoot(true);
	this->A = ArrayStack(10);
}

void Trie::insertString(std::string str,TrieNode* node){
	if (str.length() >= 1 && !node->getChild(str.at(0))){
		node->setChild(str.at(0), new TrieNode(node));
	}
	if(str.length() == 1){
		node->getChild(str.at(0))->setStringInTrie(true);
	}
	else{
		insertString(str.substr(1), node->getChild(str.at(0)));
	}
}

bool Trie::stringExists(std::string str,TrieNode* node){
	bool val = false;
	if (!node->isExternal){
		if (str.length() == 1){
			if (node->getChild(str.at(0))){
				val = true;
			}
		}
		else{
			val = stringExists(str.substr(1), node->getChild(str.at(0)));
		}
	}
	return val;
}

void Trie::printStrings(){
	/* PreOrder Traversal without recursion??

	1. Push root onto stack
	2. WHILE stack not empty DO
	3.	node,string <- pop()
	4.		IF ! external
	5.			IF string in tree
	6.				print that string
	7.				
	8.			i <- 26
	9.			WHILE (i >= 0) DO
	10.				IF node->children[i] exists DO
	11.					stackObject = StackObject(node->children[i],string.insert(i))
	12.					push(stackObject)
	13.				i <- i - 1
	14.		ELSE is External
	15.			IF string in tree
	16.				print that string
	*/
	A.push(this->root);
	while (!A.isEmpty()){
		ArrayStack::stack_object obj = A.pop();
		TrieNode* node = obj.node;
		std::string str = obj.str;
		if (!node->isExternal){
			if (node->isStrInTrie()){
				std::cout << obj.str << '\n';
			}
			for (char i = 25 + 'a'; i >= 0 + 'a'; i--){
				TrieNode* child = node->getChild(i);
				if (child != NULL){
					// store parent char + my own in str;
					// make a copy and don't modify parent
					std::string str_c = str;
					str_c.push_back(i);
					ArrayStack::stack_object child_obj(child,str_c);
					A.push(child_obj);
				}
			}
		}
		else{
			if (node->isStrInTrie()){
				std::cout << obj.str << '\n';
			}
		}
	}
}

void Trie::printStrings(TrieNode* node){
	//preorder traversal
	if (!node->isExternal){
		if (node->isStrInTrie()){
			//print string
			std::string str;
			while (!A.isEmpty()){
				str.insert(str.begin(), A.pop().c);
			}
			std::cout << str << '\n';
			for (unsigned int i = 0; i < str.size(); i++){
				A.push(str.at(i));
			}
		}
		for (char i = 0 + 'a'; i < 26 +'a'; i++){
			TrieNode* child = node->getChild(i);
			if (child){
				A.push(i);
				printStrings(child);
			}
		}
	}
	else if (node->isExternal){
		if (node->isStrInTrie()){
			std::string str;
			while (!A.isEmpty()){
				str.insert(str.begin(), A.pop().c);
			}
			std::cout << str << '\n';
			for (unsigned int i = 0; i < str.size(); i++){
				A.push(str.at(i));
			}
		}
	}
	if (!A.isEmpty())
		A.pop();
}

TrieNode* Trie::getRoot(){
	return this->root;
}

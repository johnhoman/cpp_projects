/*
 * main.cpp
 *
 *  Created on: Feb 24, 2017
 *      Author: jackhoman
 */
#include "Trie.h"
#include <vector>
#include <string>
#include <iostream>

int main(){
	std::string test_cases[] =  {"ant","cat","zoo","zone","bat","band",
											"bean","fish","fishing","banana","catch",
											"cannot","can","find","fix","any","zone","zoos","zoo"};
	unsigned int test_cases_size = sizeof(test_cases)/sizeof(test_cases[0]);
	std::string str_in_trie[] = {"fin","find","baton","bat","ban","catching","ant","zones","can"};
	Trie tree = Trie();
	for (unsigned int i = 0; i < test_cases_size; i++)
		tree.insertString(test_cases[i], tree.getRoot());
	for (unsigned int i = 0; i < sizeof(str_in_trie)/sizeof(str_in_trie[0]);i++){
		if (tree.stringExists(str_in_trie[i],tree.getRoot())){
			std::cout << "String " << str_in_trie[i] << " is in the trie" << '\n';
		}
		else{
			std::cout << "String " << str_in_trie[i] << " is not in the trie" << '\n';
		}
	}
	std::cout << '\n';
	std::cout << "Iterative printStrings function:" << '\n';
	tree.printStrings();
	std::cout << '\n';
	std::cout << "Recursive printStrings function:" << '\n';
	tree.printStrings(tree.getRoot());
	return(0);
};


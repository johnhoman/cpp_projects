#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

#include "TrieNode.h"
#include <vector>
#include <string>

class ArrayStack {
private:
	int index;
	int size;
public:

	struct stack_object{
		std::string str;
		TrieNode* node;
		char c;

		stack_object(TrieNode* node);
		stack_object(std::string str);
		stack_object(char c);
		stack_object(TrieNode* node, std::string str);
		stack_object();
	};

	std::vector<stack_object> A;

	ArrayStack();

	ArrayStack(int sz);

	bool isEmpty();

	stack_object pop();

	stack_object top();

	void push(stack_object obj);

	void push(char c);

	void push(TrieNode* node);

	void push(std::string str);



};

#endif

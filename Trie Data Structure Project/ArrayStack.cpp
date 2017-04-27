#include "ArrayStack.h"
#include <iostream>
#include <stdexcept>

ArrayStack::ArrayStack(){
	this->index = -1;
	this->size = 0;
}
ArrayStack::ArrayStack(int sz){
	A.reserve(sz);
	this->index = -1;
	this->size = 0;
}
ArrayStack::stack_object::stack_object(TrieNode* node){
	this->node = node;
}
ArrayStack::stack_object::stack_object(std::string str){
	this->str = str;
}
ArrayStack::stack_object::stack_object(char c){
	this->c = c;
}
ArrayStack::stack_object::stack_object(TrieNode* node, std::string str){
	this->node = node;
	this->str = str;
}
ArrayStack::stack_object::stack_object(){
}
void ArrayStack::push(stack_object obj){
	if (this->index + 1 < this->size){
		//push
		this->A[++this->index] = obj;
	}
	else{
		this->A.resize(size+5);
		this->size += 5;
		std::cout << "Increasing stack size from {size= " << this->size - 5 << "} to {size=" << this->size << "}" << '\n';
		push(obj);
	}
}
void ArrayStack::push(char c){
	if (this->index + 1 < this->size){
		//push
		ArrayStack::stack_object obj(c);
		A[++index] = obj;
	}
	else{
		this->A.resize(size + 5);
		this->size += 5;
		ArrayStack::stack_object obj(c);
		std::cout << "Increasing stack size from {size= " << this->size - 5 << "} to {size=" << this->size << "}" << '\n';
		push(obj);
	}
}

void ArrayStack::push(TrieNode* node){
	if (this->index + 1 < this->size){
		//push
		ArrayStack::stack_object obj(node);
		A[++index] = obj;
	}
	else{
		this->A.resize(size + 5);
		this->size += 5;
		ArrayStack::stack_object obj(node);
		std::cout << "Increasing stack size from {size= " << this->size - 5 << "} to {size=" << this->size << "}" << '\n';
		push(obj);
	}
}
void ArrayStack::push(std::string str){
	if (this->index + 1 < this->size){
		//push
		ArrayStack::stack_object obj(str);
		A[++index] = obj;
	}
	else{
		this->A.resize(size + 5);
		this->size += 5;
		ArrayStack::stack_object obj(str);
		std::cout << "Increasing stack size from {size= " << this->size - 5 << "} to {size=" << this->size << "}" << '\n';
		push(obj);
	}
}
bool ArrayStack::isEmpty(){
	if (this->index < 0){
		return true;
	}
	else
		return false;
}
ArrayStack::stack_object ArrayStack::pop(){
	if (this-> index >= 0){
		return this->A[this->index--];
	}
	else{
		throw std::out_of_range("error :: cannot pop from an empty stack!");
	}
}

ArrayStack::stack_object ArrayStack::top(){
	if (this->index >= 0){
		return this->A[this->index];
	}
	else{
		throw std::out_of_range("error :: cannot stack empty!");
	}
}

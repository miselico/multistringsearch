/*
 * ExactMatcher.cpp
 *
 *  Created on: Apr 5, 2015
 *      Author: michael
 */

#include "ExactMatcher.h"
#include <iostream>
#include <exception>
#include <fstream>

namespace exactMatcher {
namespace Patricia {

class InternalNode: public Node {
public:
	InternalNode();
	bool contains(uint8_t * start, uint_fast8_t count);
	Node * insert(uint8_t * start, uint_fast8_t count);

private:
	Node * next[256];
};

class TerminalNode: public Node {

public:
	TerminalNode() {
	}
	;
	bool contains(uint8_t * start, uint_fast8_t count) {
		if (count != 0) {
			throw new std::exception();
		}
		return true;
	}
	Node *insert(uint8_t * start, uint_fast8_t count) {
		if (count != 0) {
			throw new std::exception();
		}
		return this;
	}
};

TerminalNode terminalNode;

class LeafNode: public Node {
public:
	LeafNode(uint8_t * start) :
			rest(start) {

	}

	bool contains(uint8_t * start, uint_fast8_t count) {
		for (uint_fast8_t i = 0; i < count; i++) {
			if (start[i] != rest[i]) {
				return false;
			}
		}
		return true;
	}

	Node * insert(uint8_t * start, uint_fast8_t count) {
//		if (count == 1) {
//			return this;
//		}
		if (count == 0) {
			std::cerr << "WTF";
			throw new std::exception();
		}
		//This has to become an InternalNode
		Node * b = new InternalNode();
		b = b->insert(start, count);
		b->insert(rest, count);
		return b;
	}

private:
	uint8_t * rest;
};

InternalNode::InternalNode() {
	for (int i = 0; i < 256; i++) {
		//std::cout << int(i) << std::endl;
		this->next[i] = 0;
	}
}
bool InternalNode::contains(uint8_t * start, uint_fast8_t count = depth) {
	exactMatcher::Patricia::Node* child = this->next[start[0]];
	if (child == 0) {
		//no such child
		return false;
	} else {
		//ask child
		return child->contains(start + 1, count - 1);
	}
}

Node * InternalNode::insert(uint8_t * start, uint_fast8_t count) {
	if (count == 1) {
		this->next[start[0]] = &terminalNode;
	}
	exactMatcher::Patricia::Node* child = this->next[start[0]];
	if (child == 0) {
		//put a leaf
		this->next[start[0]] = new LeafNode(start + 1);
	} else {
		//insert into the child. The child structure might change => re-assign
		this->next[start[0]] = child->insert(start + 1, count - 1);
	}
	return this;
}

/*
 struct Node{
 uint8_t * rest;
 Node * next[256];
 };

 class Trie{
 Node root;
 public:
 Trie(Node r): root(r){
 }

 bool contains (uint8_t * start){
 exactMatcher::Patricia::Node currentNode = this->root;
 //check up till 8 char deep
 for (uint_fast8_t i = 0; i < 8; i++){
 if (currentNode.rest != 0){
 //filled, this shortcut
 for(uint_fast8_t j = 0 ; i < 8; i++, j++){
 if(currentNode.rest[j] != start[i]){
 return false;
 }
 }
 return true;
 }
 currentNode = currentNode.rest[start[i]];
 if(currentNode == 0){
 return false;
 }

 }
 //		if (current)

 return (*currentNode.rest) == start[7];
 }
 };

 */

}

Builder * Builder::add(uint8_t * start) {
	this->patterns.push_back(start);
	return this;
}

ExactMatcher Builder::build(void * memory) {
	Patricia::InternalNode * root = new Patricia::InternalNode();
	for (std::vector<uint8_t *>::iterator a = this->patterns.begin(); a != this->patterns.end(); a++) {
		uint8_t * word = *a;
		root->insert(word, depth);
	}
	ExactMatcher m(root, memory);
	std::cerr << "Currently no compacting happens in the tree. A fair bit of memory could be saved by doing do. The compacted form would only be marginally slower or perhaps even faster because of locality." << std::endl;
	return m;
}

ExactMatcher Builder::build() {
	return this->build(0);
}

bool ExactMatcher::contains(uint8_t * start) {
	return this->root->contains(start, depth);
}

ExactMatcher readFromFile(std::string filename) {
	//stackoverflow 18816126
	std::ifstream file(filename, std::ios::binary);
	file.seekg(0, std::ios::end);
	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);
	//std::vector<char> buffer(size);
	char* memory = (char *) malloc(size * sizeof(char));
	if (!(file.read(memory, size))) {
		throw std::exception();
	}
	uint8_t* addr = (uint8_t*) memory;
	unsigned int patterns = size / (sizeof(uint8_t) * 8);

	Builder b;

	uint8_t * patternStart = addr;
	for (unsigned int i = 0; i < patterns; i += 1) {
		patternStart += 8;
		b.add(patternStart);
	}
	return b.build(memory);
}

}

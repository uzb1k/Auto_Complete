#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
const int ALPHABET_SIZE = 26;


struct TrieNode {
	TrieNode* childrens[ALPHABET_SIZE];
	
	bool isEndOfWord;

	TrieNode();

};

class Trie{
public:
	Trie();

	void SetDictionary(); 
	TrieNode* getNewNode(void);
	TrieNode* search(string& prefix);
	void insert(string key);
	void collectWords(TrieNode* node, string& prefix, vector<string>& result);
	void autoComplete(string& prefix);

private:
	TrieNode* root;
	vector <string> dictionary;
	string line;

};

#include "Correction.h"

//Конструкторы
TrieNode::TrieNode() : isEndOfWord(false) {
	for (int i = 0; i < ALPHABET_SIZE; ++i) {
		childrens[i] = nullptr;
	}
}

Trie::Trie() {
	root = getNewNode();
}

//Функция вставляет ключ в дерево
void Trie::insert(string key) {
	TrieNode* node = root;

	for (int i = 0; i < key.length(); ++i) {
		int index = key[i] - 'a';
		if (!node->childrens[index]) {
			node->childrens[index] = getNewNode();
		}

		node = node->childrens[index];
	}

	node->isEndOfWord = true;
}



//Функция считывания и сохранения словаря в Trie
void Trie::SetDictionary() {
	ifstream in("popular.txt"); //Открываем текстовый файл
	if (in.is_open()) {

		while (getline(in, line)) {
			dictionary.push_back(line); //Считываем в вектор

		}
		for (int i = 0; i < dictionary.size(); ++i) {
			insert(dictionary[i]); //Вставляем слова в Trie
		}

	}
	in.close();
}


// Возвращет новый узел с пустыми детьми
TrieNode* Trie::getNewNode(void)
{

	TrieNode* pNode = new TrieNode;

	pNode->isEndOfWord = false;

	for (int i = 0; i < ALPHABET_SIZE; i++)
		pNode->childrens[i] = nullptr;

	return pNode;
}

// Возврашает ключ если ключ есть в дереве, иначе nullptr 
TrieNode* Trie::search(string& prefix) {
	TrieNode* node = root;

	for (int i = 0; i < prefix.length(); ++i) {
		int index = prefix[i] - 'a';

		if (!node->childrens[index]) {
			return nullptr;
		}

		node = node->childrens[index];
	}

	return node;
}


//Собирает все слова с таким же префиксом методом рекурсии
void Trie::collectWords(TrieNode* node, string& prefix, vector<std::string>& result) {
	if (node->isEndOfWord) {
		result.push_back(prefix);
	}

	for (int i = 0; i < ALPHABET_SIZE; ++i) {
		if (node->childrens[i]) {
			string newPrefix = prefix + char('a' + i);
			collectWords(node->childrens[i], newPrefix, result);
		}
	}
}

//Проверяет и выводит все подходящие слова
void Trie::autoComplete(string& prefix) {
	vector <string> result;

	TrieNode* node = search(prefix);

	if (node) {
		collectWords(node, prefix, result);
		cout << "Maybe you meant: " << endl;
	}

	else {
		cout << "No results";
	}
	
	for (int i = 0; i < result.size(); ++i) {
		cout << result[i] << endl;
	}
}

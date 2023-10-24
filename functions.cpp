#include "header.h"

TrieNode* getNewTrieNode()
{
	TrieNode* pNode = new TrieNode;

	pNode->isEndOfWord = false;
	for (int i = 0; i < ALPHABET_SIZE; i++)
		pNode->children[i] = nullptr;

	return pNode;
}


void getAllWords(TrieNode* node, std::string prefix, std::vector<std::string>& words)
{
	if (node == nullptr) {
		return;
	}

	if (node->isEndOfWord) {
		words.push_back(prefix);
	}

	for (char c = 'a'; c <= 'z'; c++) {
		int index = c - 'a';
		getAllWords(node->children[index], prefix + c, words);
	}
}

void addWord(TrieNode* root, const std::string& key)
{
	TrieNode* node = root;
	for (char c : key)
	{
		int index = c - 'a';
		if (!node->children[index])
			node->children[index] = getNewTrieNode();
		node = node->children[index];
	}

	node->isEndOfWord = true;
}

TrieNode* removeWord(TrieNode* root, const std::string& key, int depth)
{
	if (!root)
		return nullptr;

	if (depth == key.size())
	{
		if (root->isEndOfWord)
			root->isEndOfWord = false;

		if (isTrieEmpty(root))
		{
			delete root;
			root = nullptr;
		}

		return root;
	}

	int index = key[depth] - 'a';
	root->children[index] = removeWord(root->children[index], key, depth + 1);
	if (isTrieEmpty(root) && root->isEndOfWord == false)
	{
		delete root;
		root = nullptr;
	}

	return root;
}

bool isTrieEmpty(TrieNode* root)
{
	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		if (root->children[i])
			return false;
	}
	return true;
}

bool search(TrieNode* root, const std::string& key)
{
	TrieNode* node = root;
	for (char c : key)
	{
		int index = c - 'a';
		if (!node->children[index])
			return false;
		node = node->children[index];
	}

	return (node != nullptr && node->isEndOfWord);
}

void fillVector(TrieNode* root, std::vector<std::string>& result, char buf[], int ind)
{
	if (root->isEndOfWord)
	{
		buf[ind] = '\0';
		result.push_back(std::string(buf));
	}

	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		if (root->children[i])
		{
			buf[ind] = i + 'a';
			fillVector(root->children[i], result, buf, ind + 1);
		}
	}
}

std::vector<std::string> getAllWordsByPrefix(TrieNode* root, const std::string& prefix)
{
	std::vector<std::string> result;
	if (!root)
		return result;

	TrieNode* node = root;
	char buf[ALPHABET_SIZE] = {};
	int ind = 0;

	for (int i = 0; i < prefix.length(); i++)
	{
		int index = prefix[i] - 'a';
		buf[ind] = prefix[i];
		ind++;
		if (!node->children[index])
			return result;

		node = node->children[index];
	}

	fillVector(node, result, buf, ind);

	return result;
}
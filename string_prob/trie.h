#pragma once
#include<string>
#include<unordered_map>
#include<vector>
#include<utility>

class trie_node {
public:
	trie_node() = default;
	trie_node(bool is_word) :is_word(is_word) {}
	bool add(char key, const trie_node &node);
	trie_node& get(char key);
	bool contains(char key);
	void set_as_word() { is_word = true; }
	bool word() { return is_word; }
private:
	bool is_word;
	std::unordered_map<char, trie_node> sub_node;
};

class trie
{
public:
	trie();
	~trie();
	explicit trie(const std::vector<std::string> &words);
	explicit trie(const std::string &word);
	void insert(std::string word);
	bool search(std::string word);
	bool start_with(std::string word);
private:
	trie_node root;
	std::pair<size_t, trie_node*> locate(const std::string &str);
};

#include "pch.h"
#include "trie.h"

using std::unordered_map;
using std::string;

trie::trie() :root(trie_node(false))
{
}


trie::~trie()
{
}

trie::trie(const std::vector<std::string>& words) :root(trie_node(false))
{
	for (const auto &word : words)
		insert(word);
}

trie::trie(const std::string & word) :root(trie_node(false))
{
	insert(word);
}

void trie::insert(std::string word)
{
	auto last_location = locate(word);
	auto be = word.cbegin() + last_location.first, ed = word.cend();
	auto current_node = last_location.second;
	// 插入剩余节点
	while (be != ed) {
		current_node->add(*be, trie_node(be + 1 == ed));
		current_node = &(current_node->get(*be++));
	}
	current_node->set_as_word();
}

bool trie::search(std::string word)
{
	auto last_location = locate(word);
	return  last_location.first == word.size() && last_location.second->word();
}

bool trie::start_with(std::string word)
{
	auto last_location = locate(word);
	return  last_location.first == word.size();
}
// 定位当前串在前缀树中可识别的程度 并返回指向最后一个节点的指针
std::pair<size_t, trie_node*> trie::locate(const string & str)
{
	auto current_node = &root;
	size_t deep = 0;
	auto be = str.cbegin(), ed = str.cend();
	while (be != ed && current_node->contains(*be)) {
		current_node = &(current_node->get(*be++));
		++deep;
	}
	return { deep,current_node };
}

bool trie_node::add(char key, const trie_node & node)
{
	auto tmp = sub_node.insert({ key,node });
	return tmp.second;
}
// 使用前必须检查是否contains 
trie_node & trie_node::get(char key)
{
	if (!contains(key))
		throw "sample implementation, do not care this";
	return sub_node[key];
}

bool trie_node::contains(char key)
{
	return sub_node.find(key) != sub_node.cend();
}

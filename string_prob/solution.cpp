#include "pch.h"
#include "solution.h"
#include"trie.h"

#include<cctype>
#include<algorithm>
#include<cassert>
#include<optional>
#include<unordered_map>
#include<unordered_set>
#include<list>
#include<utility>

using std::pair;
using std::unordered_set;
using std::list;
using std::unordered_map;
using std::optional;
using std::isalnum;
using std::isdigit;
using std::vector;
using std::string;

/*
*	使用stl写出来的代码虽然简洁，但和其他人手写的效率会差很多
*/

/**************************************************************************************/

// 只要当前迭代器指向非字符或非数字就递增 直到达到末尾，最后返回是否指向某个字符
template<typename T>
inline bool forward_if(T& iter, T& end) {
	while (iter != end && !isalnum(*iter))++iter;
	if (iter != end && isalpha(*iter) && isupper(*iter))
		*iter = tolower(*iter);
	return iter == end ? false : true;
}
#define EMPTY_RETURE(S) {	\
	if(S.empty())		\
		return true;	\
}

inline void remove_not_ch_digit(string& s) {
	auto tmp = std::remove_if(s.begin(), s.end(), [](char s) {return !isalnum(s); });
	s.erase(tmp, s.end());
}

template<typename T>
T mid_iter(T begin, T end) {
	string::size_type size = end - begin;
	string::size_type mid = ((size) % 2 == 0) ? size / 2 : size / 2 + 1;
	return begin + mid;
}
// 回文串判断 会改变原串
bool solution::is_palindrome(std::string s)
{
	// 使用stl的写法
	remove_not_ch_digit(s);
	EMPTY_RETURE(s);
	std::transform(s.begin(), s.end(), s.begin(), tolower);
	return std::equal(s.begin(), mid_iter(s.begin(), s.end()), s.rbegin(), mid_iter(s.rbegin(), s.rend()));

	/*auto forward = s.begin(), en = s.end();
	auto back = s.rbegin(), ren = s.rend();
	while (forward != en && back != ren) {
		if (forward_if(forward, en) && forward_if(back, ren)) {
			if (!(*forward++ == *back++))
				return false;
		}
	}*/
	//return true;
}

/*****************************************************************************************/

#define IS_ODD(num) num%2==1
// 将长度未len的序列 分为[0,first_end),(second_end,second_start]
void sperate(
	size_t len,
	size_t& first_end,
	size_t& second_end)
{
	assert(len != 0);
	if (IS_ODD(len)) {
		first_end = second_end = len / 2;
	}
	else
	{
		first_end = len / 2;
		second_end = len / 2 - 1;
	}
}

using str_size_t = string::size_type;
inline bool seq_eqaul(
	const std::string::const_iterator& start,
	const std::string::const_iterator& end,
	str_size_t forward_end,
	str_size_t back_end)
{
	auto len = end - start;
	str_size_t forward_diff = 0, back_diff = len - 1;
	assert(forward_end - forward_diff == back_diff - back_end);
	while (forward_diff != forward_end) {
		if (*(start + forward_diff++) != *(start + back_diff--)) return false;
	}
	assert(back_diff == back_end);
	return true;
}
// 判断回文串 关注所有字符
bool solution::is_palindrome(
	const std::string::const_iterator& start,
	const std::string::const_iterator& end)
{
	if (start == end)return true;
	str_size_t forward_end, back_end; //两个子序列的末尾
	sperate(end - start, forward_end, back_end);	//分割为子序列
	return seq_eqaul(start, end, forward_end, back_end);	//子序列相等判断
}

/***************************************************************************************/

// 添加串本身和所有长度为1的子串
/*
inline void pre_add(vector<vector<string>> &result, string &data) {
	result.emplace_back(data);
	if (data.size() == 1)return;
	vector<string> ones;
	std::transform(data.cbegin(), data.cend(), std::back_inserter(ones), [](char a) {return string(1, a); });
}

vector<vector<string>> solution::partition(string s)
{
	vector<vector<string>> result;
	if (s.empty()) { return result; }
	pre_add(result, s);

	return vector<vector<string>>();
}*/

/*
// 下面实现状态机
enum state { unfinished, end };

class str_node {
public:
	str_node(state s) :s(s) {}
	optional<int> move(char ch) {
		if (this->transfer.find(ch) != this->transfer.end()) {
			return transfer[ch];
		}
		return {};
	}
	bool add_rule(std::pair<char, int> rule) {
		return transfer.insert(rule).second;
	}
	bool is_end_state() { return this->s == state::end; }
private:
	state s;
	unordered_map<char, int> transfer;
};
// 通过word_dict构建自动机
class fsm {
public:
	fsm(vector<string>& word_dict);
private:
	vector<str_node> state_gragh;
};
fsm::fsm(vector<string>& word_dict) {

}
*/

class str_node {
public:
	str_node() = default;
	str_node(const string& word) :word(word) {}
	void add_son(const str_node& son) {
		this->son.push_back(son);
	}
	string get_word() { return word; }
	vector<str_node>& get_son() { return son; }
	bool has_son() { return son.size() != 0; }
private:
	string word;
	vector<str_node> son;
};

class tree {
public:
	tree(str_node root) :root(root) {}
	vector<vector<string>> to_sentence();	//将tree转换为结果
	bool empty() { return root.has_son(); }
private:
	str_node root;
};

vector<vector<string>> tree::to_sentence()
{
	return vector<vector<string>>();
}
// 递归法求解 每一层从当前串的范围寻找所有可能匹配单词，

bool prefix(
	string::const_iterator start,
	string::const_iterator end,
	string::const_iterator origin_start,
	string::const_iterator origin_end
) {
	if (end - start > origin_end - origin_start)
		return false;
	while (start != end && *start == *origin_start)(++start, ++origin_start);
	return start == end;
}
inline void find_feasible(
	vector<string> &word_dict,
	vector<string> &feasible_str,
	string::const_iterator begin,
	string::const_iterator end)
{
	for (const auto& word : word_dict) {
		if (prefix(word.cbegin(), word.cend(), begin, end))
			feasible_str.push_back(word);
	}
}

bool do_search(
	string::const_iterator start,
	string::const_iterator end,
	str_node& father,
	vector<string>& word_dict)
{
	if (start == end)return true;
	vector<string> current_feasible;
	find_feasible(word_dict, current_feasible, start, end);	//找出当前所有可能的分割单词
	if (current_feasible.size() == 0)return false;
	for (const auto& word : current_feasible) {
		str_node possible_son(word);
		if (do_search(start + word.size(), end, possible_son, word_dict))
		{
			father.add_son(possible_son);
			break;
		}
	}
	return father.has_son() ? true : false;
	return false;
}

void word_ch_count(vector<string>& word_dict, char* ch_count) {
	for (const auto &word : word_dict) {
		for (auto ch : word) {
			ch_count[ch - 'a']++;
		}
	}
}
bool can_combine(const string &data, char *chs) {
	for (auto ch : data)
		if (!chs[ch - 'a'])
			return false;
	return true;
}
bool solution::word_break_bf(
	string s,
	vector<string>& word_dict)
{
	if (s.empty() || word_dict.empty())return false;
	char chs[26]{ 0 };
	word_ch_count(word_dict, chs);
	if (!can_combine(s, chs))return false;

	str_node root;
	do_search(s.cbegin(), s.cend(), root, word_dict);
	//tree result(root);
	return root.has_son() ? true : false;
}

// 动态规划法求解单词分割
// 核心想法： 判断一个串能否被分解，可以考虑每个原串的每个可分解的字串，串的剩余部分若在word_dict中则可分解
vector<bool> do_break(
	const string& s,	//源串
	const vector<string> &word_dict)
{
	vector<bool> sub_break(s.size() + 1, false);
	sub_break[0] = true;
	std::unordered_set<string> word_set(word_dict.cbegin(), word_dict.cend());	//优化
	auto max_len = std::max_element(word_dict.cbegin(), word_dict.cend(),
		[](const string &a, const string&b) {return a.size() < b.size(); })->size();
	for (size_t i = 0; i < s.size(); i++)
		for (size_t j = 0; j < std::min(max_len, i + 1); j++) {
			// 这里可以优化
			if (sub_break[i - j] && word_set.find(s.substr(i - j, j + 1)) != word_set.cend()) {
				sub_break[i + 1] = true;
				break;
			}
		}
	return sub_break;
}
bool solution::word_break(
	std::string s,
	std::vector<std::string>& word_dict)
{
	if (s.empty() || word_dict.empty())return false;
	auto sub_break = do_break(s, word_dict);
	return sub_break.back();
}
// 将动态规划的计算结果合并 
// 基本想法: 
void gen_sentence(
	size_t back,
	string current_sentence,
	const string &origin,
	vector<string> &result,
	const vector<size_t> &break_index,
	const vector<string> &word_dict
) {
	if (back == 0) {
		result.push_back(current_sentence);
		return;
	}
	auto curr = back;
	while (curr-- != 0) {
		auto sub = origin.substr(break_index[curr], break_index[back] - break_index[curr]);
		if (std::find(word_dict.cbegin(), word_dict.cend(), sub) != word_dict.cend()) {
			gen_sentence(curr, sub + " " + current_sentence, origin, result, break_index, word_dict);
		}
	}
}
void item_to_index(
	vector<bool>& items,
	vector<size_t>& index)
{
	auto be = items.cbegin();
	while (be != items.cend()) {
		be = std::find(be, items.cend(), true);
		if (be != items.cend())
			index.push_back(be++ - items.cbegin());
	}
}
vector<string> solution::word_break_sentence(
	std::string s,
	std::vector<std::string>& word_dict)
{
	if (s.empty() || word_dict.empty())return vector<string>();
	auto sub_break = do_break(s, word_dict);
	vector<string> result;
	if (!sub_break.back())return result;
	vector<size_t> break_index;
	item_to_index(sub_break, break_index);

	gen_sentence(break_index.size() - 1, string(), s, result, break_index, word_dict);
	std::transform(result.begin(), result.end(), result.begin(), [](string a)->string { a.pop_back(); return a; });
	return result;
}

// 回文串分割
std::vector<std::vector<std::string>> solution::partition(std::string s)
{
	vector<vector<string>> result;
	if (s.empty())return result;
	do_partition(s.cbegin(), s.cend(), vector<string>(), result);
	return result;
}
// 深搜
void solution::do_partition(
	string::const_iterator be,
	string::const_iterator end,
	vector<string> current_partition,
	vector<vector<string>>& result
) {
	if (be == end)
		result.push_back(current_partition);
	auto curr = be;
	while (curr != end) {
		if (is_palindrome(be, ++curr)) {
			current_partition.emplace_back(be, curr);
			do_partition(curr, end, current_partition, result);
			current_partition.pop_back();
		}
	}
}
inline bool equal(int *be, int *end, int val) {
	while (be != end) {
		if (*be++ != val)
			return false;
	}
	return true;
}
bool solution::is_anagram(std::string s, std::string t)
{
	if (s.size() != t.size())return false;
	// 利用stl 暴力求解	
	/*std::sort(s.begin(), s.end());
	std::sort(t.begin(), t.end());
	return std::equal(s.cbegin(), s.cend(), t.cbegin());*/
	int count[26]{ 0 };	//假定不会出现绕回
	size_t len = s.size(), i = 0;
	while (i != len) {
		++count[s[i] - 'a'];
		--count[t[i] - 'a'];
		i++;
	}
	//return std::all_of(count, count + 26, [](int a) {return a == 0; });
	return equal(count, count + 26, 0);
}

int solution::first_uniq_char(string s)
{
	pair<size_t, size_t> count_pos[26]{ {0,0} };
	for (int i = 0; i < s.size(); i++) {
		count_pos[s[i] - 'a'].first++;
		count_pos[s[i] - 'a'].second = i;
	}
	size_t index = s.size();
	for (int i = 0; i < 26; i++) {
		if (count_pos[i].first == 1 && index > count_pos[i].second)
			index = count_pos[i].second;
	}
	return index == s.size() ? -1 : index;
}
inline void swap(char &a, char &b) {
	char buf;
	buf = a, a = b, b = buf;
}
void solution::reverse_string(std::vector<char>& s)
{
	if (s.size() == 0 || s.size() == 1)return;
	size_t forward_end, back_end;
	sperate(s.size(), forward_end, back_end);
	size_t f_be = 0, b_be = s.size() - 1;
	assert(forward_end - f_be == b_be - back_end);
	char buf;
	while (f_be != forward_end) {
		swap(s[f_be++], s[b_be--]);
	}
}

using pos_t = std::pair<size_t, size_t>;
/*
class trip_node {
public:
	trip_node(bool is_word) :is_word(is_word) {}
	trip_node() = default;
	void add(char ke, const trip_node& _son) {
		if (!has_key(ke))
			son[ke] = _son;
	}
	trip_node& get(char key) {
		if (!has_key(key)) {
			throw "err";
		}
		return son[key];
	}
	bool has_key(char ke) {
		return son.find(ke) != son.cend();
	}
	bool word() {
		return this->is_word;
	}

private:
	bool is_word;
	unordered_map<char, trip_node> son;
};
// 前缀树的实现还存在问题 实现前缀树后 搜索算法会更搞笑
class trip {
public:
	trip(const vector<string> &data) :root(false) {
		construct(data);
	}
	void add_sentence(const string &str) {
		do_add(root, str.cbegin(), str.cend());
	}
	bool is_prefix(const string &str) {
		auto result = move(str);
		return result.first;
	}
	bool is_word(const string &str) {
		auto result = move(str);
		return result.first && result.second.word();
	}

private:
	trip_node root;
	pair<bool, trip_node> move(const string &str) {
		auto st = str.cbegin(), ed = str.cend();
		auto current_node = root;
		while (st != ed) {
			if (!current_node.has_key(*st))return { false,{} };
			current_node = current_node.get(*st++);
		}
		return { true,current_node };
	}
	void construct(const vector<string> &data) {
		for (const auto &str : data)
			add_sentence(str);
	}
	void do_add(trip_node &node, string::const_iterator be, string::const_iterator ed) {
		if (be == ed)return;
		char ch = *be;
		if (!node.has_key(ch)) {
			node.add(ch, trip_node(be + 1 == ed));
		}
		do_add(node.get(ch), ++be, ed);
	}

};
*/
inline bool in_range(int a, int b, int c) {
	return b >= a && b < c;
}
// 接受一个坐标和一个坐标范围，返回坐标可能移动至的点
vector<pos_t> feasible_ch(pos_t pos, pos_t range) {
	// 传入的坐标为无符号数 需要做一些处理
	using pair_int = pair<int, int>;
	pair_int pos_int{ pos.first,pos.second }, range_int{ range.first,range.second };//假设可以直接转换
	pair_int move[4]{ {1,0},{0,1},{-1,0},{0,-1} };
	vector<pos_t> result;
	for (const auto &ne : move) {
		auto x = pos_int.first + ne.first, y = pos_int.second + ne.second;
		if (in_range(0, x, range_int.first)
			&& in_range(0, y, range_int.second))
			result.emplace_back((size_t)x, (size_t)y);
	}
	return result;
}
inline char index(const vector<vector<char>> &board, const pos_t &pos) {
	return board[pos.first][pos.second];
}

inline bool is_any_prefix(const unordered_set<string>& words, const string& word) {
	auto be = word.cbegin(), end = word.cend();
	for (const auto &w : words) {
		if (prefix(be, end, w.cbegin(), w.cend())) {
			return true;
		}
	}
	return false;
}

void do_find(
	pos_t entry,
	string current_str,
	size_t deep,
	vector<pos_t> path,
	unordered_set<string> &result,
	const vector<vector<char>> &board,
	trie &words
) {
	current_str.push_back(index(board, entry));
	if (!words.start_with(current_str))return;
	if (words.search(current_str) && result.find(current_str) == result.cend())
		result.insert(current_str);
	/*if (!is_any_prefix(words, current_str))
		return;
	if (words.find(current_str) != words.cend() && result.find(current_str) == result.cend())
		result.insert(current_str);*/
		// 到达最底层 不进行搜索
	if (deep-- == 1) {
		return;
	}
	auto feasible = feasible_ch(entry, { board.size(),board[0].size() });
	for (const auto &pos : feasible) {
		if (std::find(path.cbegin(), path.cend(), pos) == path.cend()) {
			path.push_back(pos);
			do_find(pos, current_str, deep, path, result, board, words);
			path.pop_back();
		}
	}
}

void fist_ch(size_t *map, const vector<string> &data) {
	for (const auto& str : data)
		map[str[0] - 'a']++;
}

std::vector<std::string> solution::find_words(
	std::vector<std::vector<char>>& board,
	std::vector<std::string>& words)
{

	if (board.empty() || board[0].empty() || words.empty())return {};

	unordered_set<string> result;
	unordered_set<string> words_set(words.cbegin(), words.cend());
	auto max_len = std::max_element(words.cbegin(), words.cend(),
		[](const string &a, const string &b) {return a.size() < b.size(); })->size();
	vector<pos_t> path;
	trie trip_tree(words);

	for (size_t i = 0; i < board.size(); i++) {
		for (size_t j = 0; j < board[0].size(); j++) {
			pos_t pos{ i,j };
			//if (!ch_map[index(board, pos) - 'a'])continue;
			path.push_back(pos);
			do_find(pos, string(), max_len, path, result, board, trip_tree);
			path.pop_back();
		}
	}
	return vector<string>(result.cbegin(), result.cend());
}

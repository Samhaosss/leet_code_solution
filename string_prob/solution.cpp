#include "pch.h"
#include "solution.h"
#include<cctype>
#include<algorithm>
#include<cassert>
#include<optional>
#include<unordered_map>
#include<list>

using std::list;
using std::unordered_map;
using std::optional;
using std::isalnum;
using std::isdigit;
using std::vector;
using std::string;

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
void sperate(size_t len, size_t& first_end, size_t& second_end) {
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
	// 第一步构建自动机
	// 第二步识别
	// 自动机识别会导致状态爆炸
	char chs[26]{ 0 };
	word_ch_count(word_dict, chs);
	if (!can_combine(s, chs))return false;

	if (s.empty() || word_dict.empty())return false;
	str_node root;
	do_search(s.cbegin(), s.cend(), root, word_dict);
	//tree result(root);
	return root.has_son() ? true : false;
}

// 动态规划法求解单词分割
// 核心想法： 判断一个串能否被分解，可以考虑每个原串的每个可分解的字串，串的剩余部分若在word_dict中则可分解
bool solution::word_break(std::string s, std::vector<std::string>& word_dict)
{
	vector<bool> sub_break(s.size() + 1, false);
	sub_break[0] = true;
	for (int i = 1; i <= s.size(); i++)
		for (int j = 0; j < i; j++) {
			// 这里可以优化
			if (sub_break[j] && std::find(word_dict.cbegin(), word_dict.cend(), string(s.cbegin() + j, s.cbegin() + i)) != word_dict.cend()) {
				sub_break[i] = true;
				break;
			}
		}
	return sub_break.back();
}

vector<string> solution::word_break_sentence(std::string s, std::vector<std::string>& wordDict)
{
	return vector<string>();
}

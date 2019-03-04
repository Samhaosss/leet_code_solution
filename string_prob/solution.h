#pragma once
#include<string>
#include<vector>

class solution
{
public:
	solution() = default;
	~solution() = default;
	bool is_palindrome(std::string s);// 回文串 只考虑数字和英文字母
	bool is_palindrome(const std::string::const_iterator & start,
		const std::string::const_iterator & end);	//迭代器形式，考虑所有符号	
	std::vector<std::vector<std::string>> partition(std::string s);	// 未完成
	bool word_break_bf(std::string s, std::vector<std::string> &word_dict);// 很显然暴搜失败 会超时
	bool word_break(std::string s, std::vector<std::string> &word_dict);	// 使用dp分割单词
	std::vector<std::string> word_break_sentence(std::string s, std::vector<std::string>& wordDict);	// 分割单词，且返回所有可能的结果

};

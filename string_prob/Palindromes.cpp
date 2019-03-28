#include "pch.h"
#include "Palindromes.h"
#include<algorithm>

using std::string;
using std::vector;

Palindromes::Palindromes()
{
}


Palindromes::~Palindromes()
{
}

bool Palindromes::isPalindrome(std::string::const_iterator start, std::string::const_iterator end)
{
	auto len = end - start;
	if (len == 0 || len == 1)return true;	// 如果串为空 会导致下面的比较assert failed
	auto mid = end - len / 2, back_start = start + len - 1;
	while (start != mid)
		if (*start++ != *back_start--)return false;
	return true;
}

/*bool Palindromes::isPalindrome(std::string::const_iterator start, std::string::const_iterator end)
{
	if (start == end)return true;
	string::const_iterator half = start + (end-start) / 2;
	return std::equal(start, half, str.crbegin());
}*/

bool Palindromes::isPalindrome(const std::string &str)
{
	/*if (str.empty() || str.size() == 1)return true;
	string::const_iterator half = str.cbegin() + str.size() / 2;
	return std::equal(str.cbegin(), half, str.crbegin());*/
	return Palindromes::isPalindrome(str.cbegin(), str.cend());
}


vector<string> _pali_search_path;

void Palindromes::do_partition(
	string::const_iterator start,
	string::const_iterator end,
	vector<vector<string>> &result
) {
	if (start == end && !_pali_search_path.empty()) {
		result.push_back(_pali_search_path);
		return;
	}
	string::const_iterator curr = start;
	while (curr != end) {
		// 在这里移动curr是因为可以确定curr不为end 直接在条件里判断可能会移动尾后指针
		if (Palindromes::isPalindrome(start, ++curr)) {
			_pali_search_path.emplace_back(start, curr);
			do_partition(curr, end, result);
			_pali_search_path.pop_back();
		}
	}
}
//使用深度暴搜进行回文串分割
std::vector<std::vector<std::string>> Palindromes::partition(const std::string &str)
{
	vector<vector<string>> result;
	do_partition(str.cbegin(), str.cend(), result);
	return result;
}

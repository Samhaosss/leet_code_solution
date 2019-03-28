#pragma once
#include<string>
#include<vector>

class Palindromes
{
public:
	Palindromes();
	~Palindromes();
	bool isPalindrome(std::string::const_iterator, std::string::const_iterator);
	bool isPalindrome(const std::string&);
	std::vector<std::vector<std::string>> partition(const std::string&);
private:
	void do_partition(
		std::string::const_iterator,
		std::string::const_iterator,
		std::vector<std::vector<std::string>>&);
};

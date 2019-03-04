
#include "pch.h"
#include <iostream>
#include"solution.h"
#include<vector>
#include<cassert>

using std::vector;
using std::string;

solution test_instance;//所有测试使用该实例
/*
static const auto io_sync_off = []()
{
	// turn off sync
	std::ios::sync_with_stdio(false);
	// untie in/out streams
	std::cin.tie(nullptr);
	return nullptr;
}();*/
// 测试回文判断算法
void test_palindrome() {
	vector<string> samples{ "A man, a plan, a canal: Panama",
							"race a car" ,"  ","    " };
	assert(test_instance.is_palindrome(samples[0]));
	assert(!test_instance.is_palindrome(samples[1]));
	assert(test_instance.is_palindrome(samples[2]));
	assert(test_instance.is_palindrome(samples[3]));
	// 迭代器版本
	assert(test_instance.is_palindrome(samples[3].cbegin(), samples[3].cend()));
	assert(test_instance.is_palindrome(samples[2].cbegin(), samples[2].cend()));

}

void test_word_break_bf() {
	string sentence = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaab";
	vector<string> word_dict{ "a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa" };
	assert(!test_instance.word_break_bf(sentence, word_dict));

	string sentence2 = "acaaaaabbbdbcccdcdaadcdccacbcccabbbbcdaaaaaadb";
	vector<string> word_dict2{ "abbcbda","cbdaaa","b","dadaaad","dccbbbc","dccadd","ccbdbc","bbca",
		"bacbcdd","a","bacb","cbc","adc","c","cbdbcad","cdbab","db","abbcdbd","bcb","bbdab","aa","bcadb",
		"bacbcb","ca","dbdabdb","ccd","acbb","bdc","acbccd","d","cccdcda","dcbd","cbccacd","ac","cca","aaddc",
		"dccac","ccdc","bbbbcda","ba","adbcadb","dca","abd","bdbb","ddadbad","badb","ab","aaaaa","acba","abbb" };
	assert(test_instance.word_break_bf(sentence2, word_dict2));
}

void test_word_break() {
	string sentence0 = "applepenapple";
	vector<string> word_dict0{ "apple","pen" };
	assert(test_instance.word_break(sentence0, word_dict0));

	string sentence = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab";
	vector<string> word_dict{ "a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa" };
	assert(!test_instance.word_break(sentence, word_dict));

	string sentence2 = "acaaaaabbbdbcccdcdaadcdccacbcccabbbbcdaaaaaadb";
	vector<string> word_dict2{ "abbcbda","cbdaaa","b","dadaaad","dccbbbc","dccadd","ccbdbc","bbca",
		"bacbcdd","a","bacb","cbc","adc","c","cbdbcad","cdbab","db","abbcdbd","bcb","bbdab","aa","bcadb",
		"bacbcb","ca","dbdabdb","ccd","acbb","bdc","acbccd","d","cccdcda","dcbd","cbccacd","ac","cca","aaddc",
		"dccac","ccdc","bbbbcda","ba","adbcadb","dca","abd","bdbb","ddadbad","badb","ab","aaaaa","acba","abbb" };
	assert(test_instance.word_break(sentence2, word_dict2));

	string sentence3 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
		"aaaaaaaaaaaaaaabaabaaaaaaaaaaaa"
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaa"
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	vector<string> word_dict3{ "aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa","ba" };
	assert(!test_instance.word_break(sentence3, word_dict3));
}

void test_word_break_sentence() {
	string sentence2 = "acaaaaabbbdbcccdcdaadcdccacbcccabbbbcdaaaaaadb";
	vector<string> word_dict2{ "abbcbda","cbdaaa","b","dadaaad","dccbbbc","dccadd","ccbdbc","bbca",
		"bacbcdd","a","bacb","cbc","adc","c","cbdbcad","cdbab","db","abbcdbd","bcb","bbdab","aa","bcadb",
		"bacbcb","ca","dbdabdb","ccd","acbb","bdc","acbccd","d","cccdcda","dcbd","cbccacd","ac","cca","aaddc",
		"dccac","ccdc","bbbbcda","ba","adbcadb","dca","abd","bdbb","ddadbad","badb","ab","aaaaa","acba","abbb" };
	string s = "pineapplepenapple";
	vector<string> word_dict{ "apple", "pen", "applepen", "pine", "pineapple" };
	auto result = test_instance.word_break_sentence(s, word_dict);
	for (const auto &sen : result)
		std::cout << sen << std::endl;

}
int main() {

	std::cout << "start testing" << std::endl;
	//test_palindrome();
	//test_word_break_bf();
	//test_instance.partition(string(10, 'n'));
	//test_word_break();
	test_word_break_sentence();
}


#include "pch.h"
#include <iostream>
#include"trie.h"
#include"solution.h"
#include<vector>
#include<cassert>
#include<algorithm>

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

void test_reverse_string() {
	vector<char> test1{ 'h','e','l','l','o' };
	vector<char> test1_result{ 'o','l','l','e','h' };
	test_instance.reverse_string(test1);
	assert(test1_result == test1);
}

void test_partition() {
	string sentence = "aab";
	vector<vector<string>> correct_result = { {"aa", "b"},{"a", "a", "b" } };
	vector<vector<string>> cal_result;
	cal_result = test_instance.partition(sentence);
	for (const auto& d : cal_result)
		for (const auto& st : d)
			std::cout << st << " ";
	std::sort(correct_result.begin(), correct_result.end());
	std::sort(cal_result.begin(), cal_result.end());
	assert(cal_result == correct_result);
}

void test_is_anagram() {
	string s = "anagram";
	string t = "nagaram";
	assert(test_instance.is_anagram(s, t));

	string s1 = "rat";
	string s2 = "cat";
	assert(!test_instance.is_anagram(s1, s2));
}

void test_first_uniq_char() {
	string test1 = "leetcode";
	string test2 = "loveleetcode";
	std::cout << test_instance.first_uniq_char(test1) << std::endl;
	assert(test_instance.first_uniq_char(test1) == 0);
	assert(test_instance.first_uniq_char(test2) == 2);
}

void test_find_words() {
	vector<vector<char>> board = {
		{'b','a','a','b','a','b'},
		{'a','b','a','a','a','a'},
		{'a','b','a','a','a','b'},
		{'a','b','a','b','b','a'},
		{'a','a','b','b','a','b'},
		{'a','a','b','b','b','a'},
		{'a','a','b','a','a','b'}
	};
	vector<string> words = { "bbaabaabaaaaabaababaaaaababb",
		"aabbaaabaaabaabaaaaaabbaaaba",
		"babbabbbbaabbabaaaaaabbbaaab","bbbababbbbbbbababbabbbbbabaa",
		"babababbababaabbbbabbbbabbba","abbbbbbaabaaabaaababaabbabba",
		"aabaabababbbbbbababbbababbaa","aabbbbabbaababaaaabababbaaba",
		"ababaababaaabbabbaabbaabbaba","abaabbbaaaaababbbaaaaabbbaab",
		"aabbabaabaabbabababaaabbbaab","baaabaaaabbabaaabaabababaaaa",
		"aaabbabaaaababbabbaabbaabbaa","abbababbbaababaabbababababbb",
		"aaabaaaaabaabbabaabbbbaabaaa","abbaabbaaaabbaababababbaabbb",
		"baabaababbbbaaaabaaabbababbb","aabaababbaababbaaabaabababab",
		"abbaaabbaabaabaabbbbaabbbbbb","aaababaabbaaabbbaaabbabbabab",
		"bbababbbabbbbabbbbabbbbbabaa","abbbaabbbaaababbbababbababba",
		"bbbbbbbabbbababbabaabababaab","aaaababaabbbbabaaaaabaaaaabb",
		"bbaaabbbbabbaaabbaabbabbaaba","aabaabbbbaabaabbabaabababaaa",
		"aabbbabbaaaababbbbabbababbbb","babbbaabababbbbbbbbbaabbabaa"
	};
	auto result = test_instance.find_words(board, words);
	for (const auto& str : result)
		std::cout << str << " ";
}

void test_trie() {
	trie test;

	test.insert("apple");
	assert(test.search("apple"));   // 返回 true
	assert(!test.search("app"));     // 返回 false
	assert(test.start_with("app")); // 返回 true
	test.insert("app");
	assert(test.search("app"));     // 返回 true

}
int main() {

	std::cout << "start testing" << std::endl;
	//test_palindrome();
	//test_word_break_bf();
	//test_instance.partition(string(10, 'n'));
	//test_word_break();
	//test_word_break_sentence();
	//test_partition();
	//test_is_anagram();
	//test_first_uniq_char();
	//test_reverse_string();
	test_find_words();
	//test_trie();
}

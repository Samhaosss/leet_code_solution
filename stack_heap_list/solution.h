#pragma once
#include<vector>
#include<string>

using std::vector;
using std::string;
class solution
{
public:
	solution();
	~solution();
	vector<int> max_sliding_window(vector<int>& nums, int k);
	int calculate(string s);
	// 获取序列中第K大元素
	int find_kth_largest(vector<int>& nums, int k);
	// 返回序列中前K高频率的元素
	vector<int> topK_frequent(vector<int>& nums, int k);
	//计算逆波兰表达式
	int eval_RPN(vector<string>& tokens);
};

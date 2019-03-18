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
	int find_kth_largest(vector<int>& nums, int k);
};

#pragma once
#include<vector>
using std::vector;
class single_number
{
public:
	single_number() = default;
	~single_number() = default;
	// 仅出现单次的数字
	int singleNumber(vector<int>& nums);
	// 超过出现n/2次的数字
	int majorityElement(vector<int>& nums);
	// 矩阵搜索
	bool searchMatrix(vector<vector<int>>& matrix, int target);
	// merge
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n);
};

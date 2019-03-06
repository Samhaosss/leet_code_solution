#include "pch.h"
#include "single_number.h"
#include<unordered_set>
#include<unordered_map>
#include<cassert>
#include<algorithm>
#include<numeric>
#include<functional>
#include<utility>
#include<iterator>

using std::back_inserter;
using std::pair;
using std::unordered_map;
using std::unordered_set;

// 一行代码找出只有出现了一次的数字
int single_number::singleNumber(vector<int>& nums)
{
	/*	unordered_set<int> data;
		std::for_each(nums.cbegin(),nums.cend(), [&data](const int& num) {
			data.find(num) == data.cend() ? (data.insert(num), 0) : (data.erase(num), 0);
		});*/
	return std::accumulate(nums.cbegin(), nums.cend(), 0, std::bit_xor<int>());
}
inline int majorityElement_1(vector<int>& nums) {
	int same = nums[0], sum(0);
	for (const auto & num : nums) {
		if (sum == 0) {
			same = num;
		}
		if (same == num) {
			sum++;
		}
		else {
			sum--;
		}
	}
	return same;
}
// 众数查找 两个方案
int single_number::majorityElement(vector<int>& nums)
{
	return majorityElement_1(nums);
	//return majorityElement_2(nums);
}
// 利用大于n/2的性质

// 暴力求解
inline int majorityElement_2(vector<int>& nums) {
	using cmap = const pair<int, size_t>&;
	unordered_map<int, size_t> count;
	std::for_each(nums.rbegin(), nums.rend(), [&](int num) {(count[num])++; });
	auto result = std::max_element(count.cbegin(), count.cend(), [](const cmap& a, const cmap& b) {return a.second > b.second; });
	return result->first;
}
// 搜索二维矩阵， 利用递增特性减少搜索空间
bool single_number::searchMatrix(vector<vector<int>>& matrix, int target)
{
	auto rn(matrix.size()), cn(matrix[0].size());
	auto tmp = 0;
	for (int r = 0, c = cn - 1; r < rn&&cn >= 0;) {
		tmp = matrix[r][c];
		if (tmp > target) {
			--r;
		}
		else if (tmp < target) {
			++c;
		}
		else {
			return true;
		}
	}
	return false;
}
// 合并序列， 利用序列1后部的未使用值，无需重新申请空间
void single_number::merge(vector<int>& nums1, int m, vector<int>& nums2, int n)
{
	// use stl	暴力法
	/*vector<int>  result;
	std::merge(nums1.cbegin(), nums1.cbegin() + m, nums2.cbegin(), nums2.cend(), back_inserter(result));
	std::move(result.begin(), result.end(), nums1.begin());*/
	//std::move(nums2.begin(), nums2.end(), nums1.begin() + m);
	//std::sort(nums1.begin(), nums1.end());
	int nums1_len = nums1.size();
	if (nums1_len < m + n || n == 0) {
		return;
	}
	if (m == 0)
		nums1.swap(nums2);
	int mi = m - 1;
	int ni = n - 1;
	int li = nums1.size() - 1;
	while (mi >= 0 && ni >= 0) {
		if (nums1[mi] > nums2[ni])
			nums1[li--] = nums1[mi--];
		else
			nums1[li--] = nums2[ni--];
	}
	if (ni != 0) {
		std::move(nums2.begin(), nums2.begin() + ni + 1, nums1.begin());
	}
}

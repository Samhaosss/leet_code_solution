#pragma once
#include<vector>
#include<random>


class solution
{
public:
	solution();
	~solution();
	//int max_product(std::vector<int>& nums);
	// 将数据整体后移  可以使用数组翻转
	void rotate(std::vector<int>& nums, int k);
	// 使用unordered_set辅助 空间换时间
	bool contains_duplicate(std::vector<int>& nums);
	// 使用标准库remove 将0移动到最后
	void move_zeroes(std::vector<int>& nums);
	// 使用unordered_map 转换数据结构 实现o(n)的交集求解 
	// 还可以考虑先将两个数组排序 进而控制
	std::vector<int> intersect(std::vector<int>& nums1, std::vector<int>& nums2);
	// 目前使用暴力算法 还未提交
	bool increasing_triplet(std::vector<int>& nums);
	// 矩阵搜索 满足左右、上下递增
	bool search_matrix(std::vector<std::vector<int>>& matrix, int target);
	// 除自身之外的数组乘机
	std::vector<int> product_except_self(std::vector<int>& nums);
	// 有序矩阵最小k元素查找
	int kth_smallest(std::vector<std::vector<int>>& matrix, int k);

};
// 打乱array 遍历每个元素 产生一个不超过数组大小的随机正整数，如果当前元素坐标不等于该数字，
// 则将该正整数指向的元素 与当前元素交换
class array_shuffle {
public:
	array_shuffle(std::vector<int> nums) :origin(nums), rand_e(0, nums.size() - 1), e() {}
	std::vector<int> reset() { return origin; };
	std::vector<int> shuffle();
private:
	std::vector<int> origin;
	std::uniform_int_distribution<int> rand_e;
	std::default_random_engine e;
	std::vector<int> gen_random_sequence();
};

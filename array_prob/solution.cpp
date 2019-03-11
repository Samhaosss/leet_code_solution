#include "pch.h"
#include "solution.h"
#include<string>
#include<iostream>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
#include<utility>

using std::pair;
using std::default_random_engine;
using std::unordered_set;
using std::unordered_map;
using std::string;
using std::cout;
using std::endl;
using std::vector;

solution::solution()
{
}


solution::~solution()
{
}
inline int next(int &index, int size, int step) {
	index = (index + step) % size;
	return index;
}
void solution::rotate(std::vector<int>& nums, int k)
{
	if (k == 0)return;
	k %= nums.size();
	std::reverse(nums.begin(), nums.end());
	std::reverse(nums.begin(), nums.begin() + k);
	std::reverse(nums.begin() + k, nums.end());
	/*
	int inc = nums.size() % k == 0 ? nums.size() % k : 1;
	int curr, tmp;
	for (int i = 0; i < inc; i++) {
		curr = nums[i];
		tmp = i;
		while (next(tmp, nums.size(), k) != i)
			std::swap(curr, nums[tmp]);
		std::swap(curr, nums[tmp]);
	}*/
}
bool solution::contains_duplicate(std::vector<int>& nums)
{
	if (nums.size() == 0)return false;
	unordered_set<int> count;
	for (auto d : nums) {
		if (count.find(d) == count.end())
			count.insert(d);
		else
			return true;
	}
	return false;
}

void solution::move_zeroes(std::vector<int>& nums)
{
	if (nums.size() <= 1)return;
	/*auto last = std::remove(nums.begin(), nums.end(), 0);
	while (last != nums.cend())
		*last++ = 0;*/
	vector<int>::size_type pos = 0, i;
	for (i = 0; i < nums.size(); i++)
		if (nums[i] != 0)
			nums[pos++] = nums[i];
	for (; pos < nums.size(); pos++)
		nums[pos] = 0;
}
std::vector<int> solution::intersect(std::vector<int>& nums1, std::vector<int>& nums2)
{
	if (!nums1.size() || !nums2.size())return{};
	unordered_map<int, size_t> nums_map;
	for (const int num : nums1)nums_map[num]++;
	vector<int> result;
	for (const int num : nums2) {
		if (nums_map.find(num) != nums_map.cend()) {
			result.push_back(num);
			if ((--nums_map[num]) == 0)nums_map.erase(num);
		}
	}
	return result;
}
// 垃圾写法 继续考虑
bool solution::increasing_triplet(vector<int>& nums)
{
	if (nums.size() < 3)return false;
	vector<pair<int, size_t>> sorted_pair;
	size_t index = 0;
	std::transform(nums.cbegin(), nums.cend(),
		[&](int n) {return pair<int, size_t>{n, index++}; }, sorted_pair.begin());
	std::sort(sorted_pair.begin(), sorted_pair.end(),
		[](const pair<int, size_t> &a, const pair<int, size_t> &b) {return a.first > b.first; });
	for (size_t i = 0; i < nums.size(); i++) {
		auto co = std::count(sorted_pair.cbegin(), sorted_pair.cend(),
			[&](const pair<int, size_t> &a) {return a.first > nums[i] && a.second > i; });
		if (co >= 3)return true;
	}
	return false;
}
/*
using vec_iter = vector<int>::const_iterator;
// 计算从 l_ed-> l_be
int forward_left(vec_iter l_be, vec_iter l_ed) {
	int result = -999999;
	int acumulate = 1;
	while (l_ed != l_be) {
		acumulate *= *l_ed--;
		if (acumulate > result)result = acumulate;
	}
	acumulate = (acumulate* (*l_ed) > result) ? acumulate * (*l_ed) : result;
	return acumulate;
}
int forward_right(vec_iter r_be, vec_iter r_ed) {
	int result = -999999;
	int acumulate = 1;
	while (r_be != r_ed) {
		acumulate *= *r_be++;
		if (acumulate > result)result = acumulate;
	}
	return acumulate;
}
inline void update(int ac, int &result) {
	if (result < ac) result = ac;
}
int forward_double(vec_iter be, vec_iter mid, vec_iter ed) {
	int acumulate = *mid;
	int result = -999999;
	vec_iter l_curr = mid - 1, r_curr = mid + 1;
#define L_CONDITION l_curr != be
#define R_CONDITION r_curr != ed
	while (L_CONDITION || R_CONDITION) {
		if (L_CONDITION) {
			acumulate *= *l_curr--;
			update(acumulate, result);
		}
		if (R_CONDITION) {
			acumulate *= *r_curr++;
			update(acumulate, result);
		}
	}
	return result;
}
inline int max_three(int a, int b, int c) {
	if (a < b)a = b;
	if (a < c)a = c;
	return a;
}
inline int mid_max(vec_iter be, vec_iter ed) {
	auto mid = (ed - be) / 2 + be;
	int right_max = forward_right(mid, ed);
	int left_max = forward_left(be, mid);
	int merge = forward_double(be, mid, ed);
	return max_three(right_max, left_max, merge);
}
int do_search(
	vec_iter be,
	vec_iter ed
) {
	if (be + 1 == ed)return *be;
	auto mid = (ed - be) / 2 + be;
	int left_max = do_search(be, mid);
	int right_max = do_search(mid, ed);
	int mid_m = mid_max(be, ed);
	return max_three(left_max, right_max, mid_m);
}

int solution::max_product(std::vector<int>& nums)
{
	return do_search(nums.cbegin(), nums.cend());
}
*/


vector<int> array_shuffle::shuffle()
{
	vector<int> new_array(origin.size(), 0);
	auto shuffle_index = gen_random_sequence();
	for (decltype(origin.size()) i = 0; i < origin.size(); i++) {
		new_array[i] = origin[shuffle_index[i]];
	}
	return new_array;
}

std::vector<int> array_shuffle::gen_random_sequence()
{
	unordered_set<int> result;
	int tmp;
	while (result.size() != origin.size()) {
		tmp = rand_e(e);
		result.insert(tmp);
	}

	return std::vector<int>(result.cbegin(), result.cend());
}

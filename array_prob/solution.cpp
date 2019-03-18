#include "pch.h"
#include "solution.h"
#include<string>
#include<iostream>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
#include<utility>
#include<climits>

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
	// 记录两个最小值
	if (nums.empty() || nums.size() < 3)return false;
	int num_low = INT_MAX, num_mid = INT_MAX;

	for (int num : nums) {
		if (num <= num_low)
			num_low = num;
		else if (num <= num_mid)
			num_mid = num;
		else
			return true;
	}
	return false;
}
bool solution::search_matrix(std::vector<std::vector<int>>& matrix, int target)
{
	if (matrix.size() == 0 || matrix[0].size() == 0)return false;
	int row = 0, col = matrix[0].size() - 1;
	while (row < matrix.size() && col >= 0) {
		if (matrix[row][col] > target) --col;
		else if (matrix[row][col] < target) ++row;
		else return true;
	}
	return false;
}
// 题目要求不实使用除法 O(n)复杂度
// 进阶考虑使用O(1)空间复杂度
int product(
	vector<int>::const_iterator be,
	vector<int>::const_iterator ed)
{
	int result = 1;
	if (be == ed)return result;
	while (be != ed)
		result *= (*be++);
	return result;

}
vector<int> product_except_self_bf(const std::vector<int> &nums) {
	vector<int> result;
	vector<int>::const_iterator f_begin = nums.cbegin(), f_end, s_begin, s_end = nums.cend();
	for (size_t i = 0; i < nums.size(); i++) {
		f_end = f_begin + i;	// 指在当前元素 从而不计算
		s_begin = f_end + 1;
		result.push_back(product(f_begin, f_end)*product(s_begin, s_end));
	}
	return result;
}
vector<int> product_except_self_da(const std::vector<int> &nums) {
	vector<int> left_product;
	vector<int> right_product(nums.size(), 0);
	vector<int> result;
	int pro = 1;
	// 以下代码抽象程度太低 
	for (int num : nums) {
		left_product.push_back(pro);
		pro *= num;
	}
	pro = 1;
	for (int i = nums.size() - 1; i >= 0; i--) {
		right_product[i] = pro;
		pro *= nums[i];
	}
	for (int i = 0; i < nums.size(); i++)
		result.push_back(left_product[i] * right_product[i]);
	return result;
}

std::vector<int> solution::product_except_self(std::vector<int>& nums)
{
	// 首先暴力求解 锻炼坐标控制
	//return product_except_self_bf(nums);
	return product_except_self_da(nums);
}
// 搜索矩阵中第k小元素 
// 算法设计思路：
// 利用递增矩阵性质， 矩阵(0,0) 元素必然为开始最小值，每次
struct key_hash {
	std::size_t operator() (const pair<size_t, size_t> &k) const {
		return std::hash<size_t>()(k.first) ^
			(std::hash<size_t>()(k.second));
	}
};
unordered_set<pair<size_t, size_t>, key_hash> es{ {0,0} };//记录边界 每次选择最小的边界 产生新边界		
void gen_bound(const vector<vector<int>> &data, unordered_set< pair<size_t, size_t>>::const_iterator c_iter) {
	auto c_pos = *c_iter;
	es.erase(c_iter);
	if (c_pos.first + 1 < data.size())
		es.insert({ c_pos.first + 1,c_pos.second });
	if (c_pos.second + 1 < data[0].size())
		es.insert({ c_pos.first,c_pos.second + 1 });
}
int find_current_min(const vector<vector<int>> &data) {

	// 思路很简单： es中存储着当前边界点 找出边界点中最小值，删除该点并添加由于删除该点而生成的新边界点
	// 返回该边界点在矩阵中的值
	auto min = std::min_element(es.cbegin(), es.cend(),
		[&](const pair<size_t, size_t> &a, const pair<size_t, size_t> &b)
	{return data[a.first][a.second] < data[b.first][b.second]; });
	int min_value = data[min->first][min->second];
	gen_bound(data, min);	//这样写可能会导致迭代器失效
	return min_value;
}
int solution::kth_smallest(std::vector<std::vector<int>>& matrix, int k)
{
	// 思路很简单，边界点集合P,初始只有(0,0)
	// 每次从边界点中选择对应最小的值，删除该点 生成新边界点
	// 重复以上过程k次
	int result;
	while (k-- > 1)
		result = find_current_min(matrix);
	return find_current_min(matrix);
}

// 删除左右两侧的0
inline void trip_zero(vector<int> &nums) {
	auto be = nums.begin(), end = nums.end();
	while (be != end && *be == 0)++be;
	nums.erase(nums.begin(), be);//到这里之前的迭代器已经不能安全使用
	if (nums.empty())return;
	auto r_be = nums.begin() + nums.size() - 1, r_end = nums.begin();
	while (r_be != r_end && *r_be == 0)--r_be;
	if (*r_be)r_be++;
	nums.erase(r_be, nums.end());
}
vector<vector<int>::const_iterator> inner_zero(vector<int> &nums) {
	vector<decltype(nums.cbegin())> zeros_iter;
	decltype(nums.cbegin()) fi = nums.cbegin();
	while (fi != nums.cend() &&
		(fi = std::find(fi, nums.cend(), 0)) != nums.cend())
		zeros_iter.push_back(fi++);
	zeros_iter.push_back(nums.cend());
	return zeros_iter;
}
// 到这里传入的子序列一定不包含0
// 所以可以这样考虑 如果最大乘积子序列位于序列中间，则左右剩余子序列各自乘积要么同号，要么异号
// 如果同号则与当前子序列是最大子序列矛盾 如果异号，则其中为正的部分一定可以为当前子序列乘积做
// 正贡献 因此最大子序列一定是否当前序列的某一侧开始的
int sequence_max_product(
	vector<int>::const_iterator be,
	vector<int>::const_iterator end
)
{
	auto be_cp = be, end_cp = end - 1;
	int max = INT_MIN;
	int accumulate = 1;
	while (be_cp != end) {
		accumulate *= *(be_cp++);
		if (accumulate > max)max = accumulate;
	}
	accumulate = 1;
	while (end_cp != be) {
		accumulate *= *(end_cp--);
		if (accumulate > max)max = accumulate;
	}
	accumulate *= *(end_cp);
	if (accumulate > max)max = accumulate;
	return max;
}
int solution::max_product(std::vector<int>& nums)
{
	// 一、去除边界0
	if (nums.empty())return 0;
	trip_zero(nums);
	// 二、找出内部0 从而将串分为多个字串
	auto zeros_iter = inner_zero(nums);
	// 三、计算每个字串的最大乘积
	auto last = nums.cbegin();
	int max = INT_MIN;
	int tmp;
	for (auto end : zeros_iter) {
		tmp = sequence_max_product(last, end);
		if (tmp > max)max = tmp;
		last = end;
	}
	if (nums.size() != 1 && max < 0)max = 0;
	return max;
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

#include "pch.h"
#include "solution.h"
#include<algorithm>
#include<stack>
#include<cassert>

using std::stack;

solution::solution()
{
}


solution::~solution()
{
}

vector<int> solution::max_sliding_window(vector<int>& nums, int k)
{
	if (!nums.size() || nums.size() < k)return{};
	auto be = nums.cbegin(), end = nums.cend();
	int moved = nums[0], last_min = *std::max_element(be, be + k);
	vector<int> result{ last_min };
	while (++be + k - 1 != end) {
		//(moved != last_min && *(be + k-1) <= last_min) ? last_min :
		last_min = *max_element(be, be + k);
		result.push_back(last_min);
		moved = *be;
	}
	return result;
}
enum relation { bigger, smaller };
relation judge(char current, char top) {
	if (top == '#' || current == '!')return relation::smaller;
	if (top == '*' || top == '/') {
		return smaller;
	}
	else
	{
		return current == '+' || current == '-' ? bigger : smaller;
	}
}
inline int cal(int n1, int n2, char op) {
	switch (op)
	{
	case '+':return n1 + n2;
	case '-':return n1 - n2;
	case '*':return n1 * n2;
	case '/':return n1 / n2;
	}
}
// 由于头疼 未完成
int solution::calculate(string s)
{
	s.push_back('!');
	stack<int> value_stack;
	stack<char> symbol_stack;
	symbol_stack.push('#');
	char top;
	int n;
	for (auto ch : s) {
		if (ch >= '0'&&ch <= '9')value_stack.push(ch - '0');
		else if (ch == ' ')continue;
		else
		{
			top = symbol_stack.top();
			switch (judge(ch, top))
			{
			case smaller:
				symbol_stack.pop();
				n = value_stack.top();
				value_stack.pop();
				n = cal(n, value_stack.top(), top);
				value_stack.pop();
				value_stack.push(n);
				break;
			case bigger:
				symbol_stack.push(ch);
				break;
			}
		}
	}

	return 0;
}

int partition(
	vector<int>::iterator begin,
	vector<int>::iterator end
) {
	if (begin == end) return -1;
	int sep = *begin;
	int curr_left = 0, curr_right = end - begin - 1;
	while (curr_left != curr_right) {
		while (curr_left != curr_right && *(begin + curr_right) >= sep)
			curr_right--;
		if (curr_left == curr_right)break;
		*(begin + curr_left++) = *(begin + curr_right);
		while (curr_left != curr_right && *(begin + curr_left) < sep)
			curr_left++;
		if (curr_left == curr_right)break;
		*(begin + curr_right--) = *(begin + curr_left);
	}
	*(begin + curr_left) = sep;
	return  curr_left;
}
int quick_sort_k(
	vector<int>::iterator begin,
	vector<int>::iterator end,
	int k
) {
	int curr = partition(begin, end);
	assert(curr != -1);
	auto begin_tmp = begin, end_tmp = end;	// 窗口
	auto target = begin + k;
	while (begin_tmp + curr != target) {
		if (begin_tmp + curr > target)//这里的正确性依赖于迭代器比较的语义 
		{
			end_tmp = begin_tmp + curr;
		}
		else
		{
			begin_tmp += curr + 1;
		}
		curr = partition(begin_tmp, end_tmp);
	}
	return *(begin + k);
}
int solution::find_kth_largest(vector<int>& nums, int k)
{
	assert(k >= 1 || nums.size() >= k);
	k = nums.size() - k;
	return quick_sort_k(nums.begin(), nums.end(), k);
}



template<typename IterType, typename ElementType>
vector < vector < ElementType>> sub_set(IterType begin, IterType end) {
	vector < vector < ElementType>> result{ {} };
	do_find_sub_set(begin, end, {}, result);
}

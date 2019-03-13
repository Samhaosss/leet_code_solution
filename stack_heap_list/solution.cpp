#include "pch.h"
#include "solution.h"
#include<algorithm>
#include<stack>

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
			case bigger_or_equal:
				symbol_stack.push(ch);
				break;
			}
		}
	}
	return 0;
}

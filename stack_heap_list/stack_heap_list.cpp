// stack_heap_list.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include"solution.h"
#include <iostream>
#include<cassert>
#include"MinStack.h"

using std::cout;
using std::endl;
solution test_instance;

void test_max_sliding_window() {
	vector<int> test_data{ 1,3,-1,-3,5,3,6,7 };
	vector<int> result = { 3,3,5,5,6,7 };
	assert(test_instance.max_sliding_window(test_data, 3) == result);
}
void print_subset(int *A, int n, int cur)
{
	if (cur == 0) cout << "kong";
	for (int i = 0; i < cur; i++)//输出当前子集
		cout << A[i] + 1 << " ";
	cout << endl;
	int s = cur ? A[cur - 1] + 1 : 0;//获取当前子集的最小值，当cur为0时防止出现A[-1]
	for (int i = s; i < n; i++)//每一次循环都存入一个不同的数进集合，此时变生成了不同的子集
	{
		A[cur] = i;
		print_subset(A, n, cur + 1);
	}
}

template<typename IterType, typename ElementType>
void do_find_sub_set(
	IterType begin,
	IterType end,
	vector<ElementType> father_set,
	vector<vector<ElementType>>& sub_sets)
{
	if (begin == end) return;
	while (begin != end) {
		father_set.push_back(*begin);
		sub_sets.push_back(father_set);
		do_find_sub_set(begin++ + 1, end, father_set, sub_sets);
		father_set.pop_back();
	}
}

template<typename IterType, typename ElementType>
void sub_set(IterType begin, IterType end, vector < vector < ElementType>> result) {

	do_find_sub_set(begin, end, {}, result);
}

void test_min_stack() {
	MinStack minStack;
	minStack.push(-2);
	minStack.push(0);
	minStack.push(-3);
	assert(minStack.getMin() == -3);
	minStack.pop();
	assert(minStack.top() == 0);
	assert(minStack.getMin() == -2);
}
void test_find_kth_largest() {
	vector<int> test_data{ 3,2,1,5,6,4 };
	assert(test_instance.find_kth_largest(test_data, 2) == 5);
	vector<int> test_data2{ 3,2,3,1,2,4,5,5,6 };
	assert(test_instance.find_kth_largest(test_data2, 4) == 4);
}
int main()
{
	std::cout << "start testing\n";
	//	test_max_sliding_window();

	/*int A[6]{ 0,1,2,3,4,5 };
	vector < vector <int>> result{ {} };
	sub_set(A, A + 6, result);
	print_subset(A, 5, 0);-*/
	//test_min_stack();
	test_find_kth_largest();
}

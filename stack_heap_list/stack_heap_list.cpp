// stack_heap_list.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include"solution.h"
#include <iostream>
#include<cassert>

solution test_instance;

void test_max_sliding_window() {
	vector<int> test_data{ 1,3,-1,-3,5,3,6,7 };
	vector<int> result = { 3,3,5,5,6,7 };
	assert(test_instance.max_sliding_window(test_data, 3) == result);
}

int main()
{
	std::cout << "start testing\n";
	test_max_sliding_window();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

// array_prob.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include"solution.h"
#include <iostream>
#include<vector>
#include<cassert>

using std::cout;
using std::endl;
using std::vector;

solution test_instance;
/*
void test_max_product() {
	vector<int> test_vec{ 2,3,-2,4 };
	assert(test_instance.max_product(test_vec) == 6);

	vector<int> test_vec2{ -2,0,-1 };
	assert(test_instance.max_product(test_vec2) == 0);

	vector<int> test_vec3{ -4,-3,-2 };
	assert(test_instance.max_product(test_vec3) == 12);

	vector<int> test_vec4{ -2,3,-4 };
	assert(test_instance.max_product(test_vec4) == 24);
}*/
template<typename T>
vector<vector<T>> sub_sequence(const vector<T> &set) {
	if (set.size() == 0)return{};
	vector<vector<T>> result;
	size_t start, curr;
	for (start = 0; start != set.size(); start++)
		for (curr = 1; start + curr <= set.size(); curr++) {
			result.push_back(vector<T>(set.begin() + start, set.begin() + start + curr));
		}
	return result;
}
template<typename T>
void print_vec(const vector<T> &dat) {
	for (const auto &d : dat)
		cout << d << " ";
	cout << endl;
}

void test_sub_sequence() {
	vector<int> test_vec{ 2,3,-2,4 };
	auto result = sub_sequence(test_vec);
	for (const auto &da : result)
		print_vec(da);
}

void test_rotate() {
	vector<int> data{ 1,2,3,4,5,6,7 };
	vector<int> result{ 5, 6, 7, 1, 2, 3, 4 };
	test_instance.rotate(data, 3);
	assert(data == result);

	vector<int> data2{ 1,2,3,4,5,6 };
	vector<int> result2{ 3,4,5,6,1,2 };
	test_instance.rotate(data2, 4);
	print_vec(data2);
	assert(data2 == result2);
}
void test_contains_duplicate() {
	vector<int> data{ 1,2,3,4,5,6,7 };
	assert(!test_instance.contains_duplicate(data));

	vector<int> data2{ 1,1,1,3,3,4,3,2,4,2 };
	assert(test_instance.contains_duplicate(data2));
}
void test_move_zeroes() {
	vector<int> data{ 0,1,0,3,12 };
	vector<int> result{ 1,3,12,0,0 };
	test_instance.move_zeroes(data);
	assert(data == result);
}

void test_shuffle() {
	vector<int> test{ 0,1,0,3,12 };
	array_shuffle shuffler(test);
	for (const auto i : test)
		print_vec(shuffler.shuffle());
}
#include<unordered_set>
using std::unordered_set;
#include<random>
using std::default_random_engine;

void gen_random_sequence()
{
	vector<int> origin{ 0,1,0,3,12 };
	std::uniform_int_distribution<int> rand_e(0, origin.size() - 1);
	std::default_random_engine e;
	unordered_set<int> result;
	int tmp;
	while (result.size() != origin.size()) {
		tmp = rand_e(e);
		result.insert(tmp);
	}
	auto r = std::vector<int>(result.cbegin(), result.cend());
	print_vec(r);
}

void test_intersect() {
	vector<int> nums1{ 4,9,5 };
	vector<int> nums2{ 9,4,9,8,4 };
	auto result = test_instance.intersect(nums1, nums2);
	print_vec(result);
}

void test_increasing_triplet() {
	vector<int> data1{ 1,2,3,4,5 };
	vector<int> data2{ 5,4,3,2,1 };
	assert(test_instance.increasing_triplet(data1));
	assert(!test_instance.increasing_triplet(data2));
}
int main()
{
	std::cout << "start testing\n" << std::endl;
	//test_max_product();
	//test_sub_sequence();
//	test_rotate();
	//test_contains_duplicate();
	//test_move_zeroes();
	//test_shuffle();
	//gen_random_sequence();
	//test_intersect();
	test_increasing_triplet();
}

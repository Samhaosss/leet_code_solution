#pragma once
#include<vector>
#include<memory>
#include<stack>
#include<queue>
#include<list>

class NestedInteger {
public:
	NestedInteger(int inner_data) :inner_data(inner_data), is_integer(true) {}
	NestedInteger(const std::vector<NestedInteger> &nested_data) :
		nested_data(nested_data), is_integer(false) {}
	bool isInteger() const { return is_integer; }
	int getInteger() const { return inner_data; };
	const std::vector<NestedInteger> &getList() const { return nested_data; };
private:
	std::vector<NestedInteger> nested_data;
	int inner_data;
	bool is_integer;
};
class NestedIterator
{
public:
	NestedIterator(const std::vector<NestedInteger> &nestedList) :
		nested_list(nestedList.begin(), nestedList.end()) {
		data_stack.push(nested_list.front());
		nested_list.pop_front();
	}
	~NestedIterator();
	int next();

	bool hasNext();
private:
	std::list<NestedInteger> nested_list;
	std::stack<NestedInteger> data_stack;
	void nestIntegerToStack(const NestedInteger &nt);
};

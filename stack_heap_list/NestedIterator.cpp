#include "pch.h"
#include "NestedIterator.h"

NestedIterator::~NestedIterator()
{
}

int NestedIterator::next()
{
	if (data_stack.empty())return -1;
	const auto top = data_stack.top();
	data_stack.pop();
	while (true) {
		if (top.isInteger()) {
			if (data_stack.empty() && !nested_list.empty()) {
				nestIntegerToStack(nested_list.front());
				nested_list.pop_front();
			}
			return top.getInteger();
		}
		else
		{
			nestIntegerToStack(top);
		}
	}
	return 0;
}

bool NestedIterator::hasNext()
{
	return !data_stack.empty();
}

void NestedIterator::nestIntegerToStack(const NestedInteger & nt)
{
	if (nt.isInteger())
		data_stack.push(nt);
	else {
		auto nt_list = nt.getList();
		for (auto iter = nt_list.crbegin(); iter != nt_list.crend(); iter++)
			data_stack.push(*iter);
	}

}

#include "pch.h"
#include "MinStack.h"
#include<cassert>
// 默认创建时会创建一个头节点，方便操作
MinStack::MinStack() :data_(1, 0)
{
}

MinStack::~MinStack()
{
}

void MinStack::push(int x)
{
	data_.emplace_back(x);
	pushVal();
}

void MinStack::pop()
{
	if (!empty())
	{
		this->delVal();	//需要先从优先队列删除，然后真正删除
		data_.pop_back();
	}
}

int MinStack::top()
{
	assert(!empty());
	return data_[data_.size() - 1].node_value;
}

int MinStack::getMin()
{
	assert(!empty());
	return data_[data_[head_].next].node_value;
}

void MinStack::pushVal()
{
	int input_index = data_.size() - 1, intput_val = data_[input_index].node_value;
	if (data_.size() == 2)	//
	{
		data_[0].next = data_[0].prev = 1;
		data_[1].next = data_[1].next = 0;
		return;
	}
	int curr = data_[head_].next;
	while (data_[curr].node_value < intput_val&&data_[curr].next)
		curr = data_[curr].next;
	if (data_[curr].node_value >= intput_val) {
		insertBefore(curr, input_index);
	}
	else
	{
		insertAfter(curr, input_index);
	}
}

void MinStack::delVal()
{
	if (!empty()) {
		int last_index = data_.size() - 1;
		data_[data_[last_index].prev].next = data_[last_index].next;
		data_[data_[last_index].next].prev = data_[last_index].prev;
	}
}

inline void MinStack::insertBefore(int ori, int ne)
{
	int pre = data_[ori].prev;
	data_[pre].next = ne;
	data_[ori].prev = ne;
	data_[ne].next = ori;
	data_[ne].prev = pre;
}

inline void MinStack::insertAfter(int ori, int ne)
{
	int next = data_[ori].next;
	data_[next].prev = ne;
	data_[ori].next = ne;
	data_[ne].prev = ori;
	data_[ne].next = next;
}

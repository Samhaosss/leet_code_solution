#pragma once
#include<vector>
#include<stack>


// 最小栈
// 设计方案，维护栈的同时维护一个优先队列，每次出入栈的同时更新优先队列
// emmmm 之前的设计方案存在很大的不足，实际上只需要再维护一个最小栈即可
class MinStack
{
public:
	MinStack();
	~MinStack();
	void push(int x);
	void pop();
	int top();
	int getMin();
	bool empty() { return data_.size() == 1; }
private:
	struct ListNode {
		int node_value = 0;
		int prev = 0;
		int next = 0;
		ListNode() = default;
		ListNode(int val) :node_value(val) {}
	};
	std::vector<ListNode> data_;
	int head_ = 0;	//指向双向队列队头
	// 由于添加和删除元素只在尾处，因此不许给下面两个过程传递参数
	void pushVal();
	void delVal();
	inline void insertBefore(int ori, int ne);
	inline void insertAfter(int ori, int ne);
};
//使用两个栈实现最小栈
class MinStackSS {
public:
	MinStackSS() = default;
	~MinStackSS() = default;
	void push(int x) {
		data_.push(x);
		if (min_.empty() || (!min_.empty() && min_.top() >= x))
			min_.push(x);
	}
	void pop() {
		if (min_.top() == data_.top())
			min_.pop();
		data_.pop();
	}
	int top() {
		data_.top();
	}
	int getMin() {
		min_.top();
	}
private:
	std::stack<int> data_;
	std::stack<int> min_;
};

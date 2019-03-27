#pragma once
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int val) :val(val) {}
	void set_next(ListNode *next) {
		this->next = next;
	}
};
class Solution
{
public:
	Solution();
	~Solution();
	ListNode* sort_list(ListNode* head);
	ListNode *get_intersectionNode(ListNode *headA, ListNode *headB);
};

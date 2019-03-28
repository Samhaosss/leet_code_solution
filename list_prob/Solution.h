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
	// 链表反转
	ListNode* reverse_list(ListNode* head);
	// 列表回文串
	bool is_palindrome(ListNode* head);
	// 奇偶链表
	ListNode* odd_even_list(ListNode* head);
};

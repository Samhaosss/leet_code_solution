#include "pch.h"
#include "Solution.h"
#include<unordered_set>
#include<unordered_map>

using std::unordered_map;
using std::unordered_set;


Solution::Solution()
{
}


Solution::~Solution()
{
}
void list_partition(
	ListNode *prev,
	ListNode *start,
	ListNode *end,
	ListNode *last)
{
	if (start == end) return;
	ListNode *first_end, *second_start;
	while (start != end) {

	}
}
ListNode * Solution::sort_list(ListNode * head)
{
	return nullptr;
}

ListNode* find_first(ListNode *head, const unordered_set<ListNode*> &data) {
	while (head != nullptr) {
		if (data.find(head) != data.cend())
			return head;
		head = head->next;
	}
	return nullptr;
}
#define LAST(ptr) while(ptr->next)ptr=ptr->next;	

ListNode* intersec_node_solution1(ListNode *headA, ListNode *headB) {
	if (headA == nullptr || headB == nullptr) return nullptr;
	unordered_set<ListNode*> head_a_data;
	ListNode *curr = headA;
	// 可以为listNode设计一个foreach抽象
	while (curr != nullptr) {
		head_a_data.insert(curr);
		curr = curr->next;
	}
	return find_first(headB, head_a_data);
}

inline int list_len(ListNode *head) {
	int len = 0;
	if (head == nullptr)return len;
	while (head)(++len, head = head->next);
	return len;
}
inline ListNode* list_move(ListNode *head, int step) {
	while (step--)head = head->next;
	return head;
}
ListNode* intersect_node_2(ListNode *headA, ListNode *headB) {
	int len_a = list_len(headA), len_b = list_len(headB);
	ListNode *longer = len_a > len_b ? headA : headB;
	ListNode *shorter = len_a > len_b ? headB : headA;
	if (len_a > len_b)std::swap(len_a, len_b);
	while (len_a-- != len_b)longer = longer->next;
	while (longer&&shorter) {
		if (longer->val == shorter->val)
			return longer;
		longer = longer->next;
		shorter = shorter->next;
	}
	return nullptr;
}
ListNode * Solution::get_intersectionNode(ListNode * headA, ListNode * headB)
{
	//return intersec_node_solution1(headA, headB);
	return intersect_node_2(headA, headB);

}

ListNode * Solution::reverse_list(ListNode * head)
{
	if (head == nullptr) return nullptr;
	ListNode *origin_left = head->next;
	ListNode *reversed_list = head;
	head->next = nullptr;
	while (origin_left) {
		auto tmp = origin_left->next;
		origin_left->next = reversed_list;
		reversed_list = origin_left;
		origin_left = tmp;
	}
	return reversed_list;
}
ListNode *list_mid(ListNode *head) {
	if (!head->next)return nullptr;
	ListNode *slow_ptr = head, *fast_ptr = head;
	while (fast_ptr->next&&fast_ptr->next->next) {
		fast_ptr = fast_ptr->next->next;
		slow_ptr = slow_ptr->next;
	}
	return slow_ptr->next;
}
bool Solution::is_palindrome(ListNode * head)
{
	if (!head || !head->next)return true;
	ListNode *mid = list_mid(head);
	mid = Solution::reverse_list(mid);
	while (mid) {
		if (head->val != mid->val)return false;
		head = head->next;
		mid = mid->next;
	}
	return false;
}

ListNode * Solution::odd_even_list(ListNode * head)
{
	if (!head || !head->next || !head->next->next)return head;
	ListNode *odd_head = head, *even_head = head->next;
	ListNode *odd_curr = odd_head, *even_curr = even_head;
	ListNode *original_list = head->next->next;
	while (original_list) {
		odd_curr->next = original_list;
		odd_curr = odd_curr->next;
		original_list = original_list->next;
		if (original_list) {
			even_curr->next = original_list;
			even_curr = even_curr->next;
			original_list = original_list->next;
		}
	}
	odd_curr->next = even_head;
	return odd_head;
}

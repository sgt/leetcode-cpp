#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-convert-member-functions-to-static"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <vector>
#include <numeric>
#include <optional>

#include "doctest.h"

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    explicit ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

vector<int> listNode_to_vector(const ListNode *node) {
    vector<int> v{};
    while (node) {
        v.push_back(node->val);
        node = node->next;
    }
    return v;
}

ListNode *vector_to_listNode(const vector<int> &v) {
    ListNode dummy{0};
    (void) accumulate(v.cbegin(), v.cend(), &dummy, [](ListNode *n, int v) {
        n->next = new ListNode(v);
        return n->next;
    });
    return dummy.next;
}

class Solution {

    // Returns (index, value) of minimal value among first elements of lists
    static optional<pair<int, int>> find_min(vector<ListNode *> &lists) {
        optional<pair<int, int>> result{};

        for (int i{}; i < lists.size(); i++) {
            auto node = lists[i];
            if (node) {
                if (!result || node->val < result.value().second) {
                    result = {i, node->val};
                }
            }
        }

        return result;
    }

public:
    static int add(int x, int y) { return x + y; }

    // 21. Merge Two Sorted Lists
    ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
        // TODO can be rewritten to make the merge in-place
        auto dummy = new ListNode();
        auto current = dummy;
        while (list1 || list2) {
            if (!list1) {
                current->next = list2;
                list2 = nullptr;
            } else if (!list2) {
                current->next = list1;
                list1 = nullptr;
            } else if (list1->val < list2->val) {
                current->next = new ListNode(list1->val);
                list1 = list1->next;
                current = current->next;
            } else {
                current->next = new ListNode(list2->val);
                list2 = list2->next;
                current = current->next;
            }
        }
        return dummy->next;
    }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

    // 23. Merge k Sorted Lists
    // TODO rewrite this by using a helper function which merges two lists
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        auto min_result = find_min(lists);
        if (min_result) {
            auto [min_i, min_val] = min_result.value();
            lists[min_i] = lists[min_i]->next;
            return new ListNode(min_val, mergeKLists(lists));
        }
        return nullptr;
    }

#pragma clang diagnostic pop

    // 206. Reverse Linked List
    ListNode *reverseList(ListNode *head) {
        if (!head) return head;
        auto curr = head;
        auto prev = nullptr;
        while (curr) {

            auto next = head->next;
        }
    }

    // 704. Binary Search
    int search(vector<int> &nums, int target) {

    }

    // 374. Guess Number Higher or Lower
    int guessNumber(int n) {

    }

    // 74. Search a 2D Matrix
    bool searchMatrix(vector<vector<int>> &matrix, int target) {

    }
};

TEST_CASE("Test all") {
    SUBCASE("Silly test") {
        CHECK(Solution::add(2, 3) == 5);
    }

    SUBCASE("Linked list to vector") {
        CHECK(listNode_to_vector(new ListNode(1, new ListNode(2, new ListNode(3)))) == vector<int>{1, 2, 3});
    }

    SUBCASE("Vector to linked list") {
        for (auto v: vector<vector<int>>{{},
                                         {1, 2, 3}}) {
            auto vln = vector_to_listNode(v);
            CHECK(listNode_to_vector(vln) == v);
        }
    }

    SUBCASE("Merge two lists") {
        Solution s{};
        CHECK(listNode_to_vector(s.mergeTwoLists(vector_to_listNode({2, 4}), vector_to_listNode({1, 3}))) ==
              vector<int>{1, 2, 3, 4});
    }

    SUBCASE("Merge K lists") {
        Solution s{};
        vector<ListNode *> lists = {vector_to_listNode({2, 4}), vector_to_listNode({4, 5}), vector_to_listNode({1, 3})};
        CHECK(listNode_to_vector(s.mergeKLists(lists)) == vector<int>{1, 2, 3, 4, 4, 5});
    }
}

#pragma clang diagnostic pop

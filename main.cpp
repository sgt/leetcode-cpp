#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-convert-member-functions-to-static"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <vector>
#include <numeric>
#include <optional>
#include <functional>

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
            auto node{lists[i]};
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

    // A companion function for guess-a-number.
    static function<int(int)> guess_fn(int pick) {
        return [=](int num) {
            if (num > pick) return -1;
            else if (num < pick) return 1;
            else return 0;
        };
    }

    // 21. Merge Two Sorted Lists
    ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
        // TODO can be rewritten to make the merge in-place
        auto dummy{new ListNode()};
        auto current{dummy};
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
        auto min_result{find_min(lists)};
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
        if (!head) return nullptr;
        auto curr{head};
        ListNode *prev{nullptr};
        while (curr) {
            auto next{curr->next};
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }

    // 704. Binary Search
    int search(vector<int> &nums, int target) {
        if (nums.empty()) return -1;
        int low{0}, high{static_cast<int>(nums.size() - 1)};
        while (low <= high) {
            int i{(low + high) / 2};
            if (nums[i] > target) {
                high = i - 1;
            } else if (nums[i] < target) {
                low = i + 1;
            } else {
                return i;
            }
        }
        return -1;
    }

    // 374. Guess Number Higher or Lower
    int guessNumber(int n, const function<int(int)> &guess) {
        int low{1}, high{n};
        while (low != high) {
            int g{(low + high) / 2};
            int r{guess(g)};
            if (r == -1) {
                high = g - 1;
            } else if (r == 1) {
                low = g + 1;
            } else {
                return g;
            }
        }
        return low;
    }

    // 74. Search a 2D Matrix
    bool searchMatrix(vector<vector<int>> &matrix, int target) {
        int m{static_cast<int>(matrix.size())}, n{static_cast<int>(matrix[0].size())};
        auto get_val{
                [=](size_t val) {
                    size_t nc{val % n}, mc{val / n};
                    return matrix[mc][nc];
                }
        };
        int low{0}, high{m * n - 1};
        while (low <= high) {
            int i{(low + high) / 2};
            int cur{get_val(i)};
            if (cur > target) {
                high = i - 1;
            } else if (cur < target) {
                low = i + 1;
            } else {
                return true;
            }
        }
        return false;
    }

    // 136. Single Number
    int singleNumber(vector<int> &nums) {
        return accumulate(nums.cbegin(), nums.cend(), 0, [](int acc, int i) { return acc ^ i; });
    }
};

TEST_CASE("Test all") {
    Solution s{};

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
        CHECK(listNode_to_vector(s.mergeTwoLists(vector_to_listNode({2, 4}), vector_to_listNode({1, 3}))) ==
              vector<int>{1, 2, 3, 4});
    }

    SUBCASE("Merge K lists") {
        vector<ListNode *> lists = {vector_to_listNode({2, 4}), vector_to_listNode({4, 5}), vector_to_listNode({1, 3})};
        CHECK(listNode_to_vector(s.mergeKLists(lists)) == vector<int>{1, 2, 3, 4, 4, 5});
    }

    SUBCASE("Reverse linked list") {
        CHECK(listNode_to_vector(s.reverseList(vector_to_listNode({1, 2, 3}))) == vector<int>{3, 2, 1});
        CHECK(listNode_to_vector(s.reverseList(vector_to_listNode({1, 2}))) == vector<int>{2, 1});
        CHECK(listNode_to_vector(s.reverseList(vector_to_listNode({}))) == vector<int>{});
        CHECK(listNode_to_vector(s.reverseList(vector_to_listNode({1}))) == vector<int>{1});
    }

    SUBCASE("Binary search") {
        vector<int> v{-1, 0, 3, 5, 9, 12};
        CHECK(s.search(v, 9) == 4);
        CHECK(s.search(v, 2) == -1);
        v = {5};
        CHECK(s.search(v, 5) == 0);
        CHECK(s.search(v, 10) == -1);
        CHECK(s.search(v, 0) == -1);
    }

    SUBCASE("Guess number") {
        CHECK(s.guessNumber(10, Solution::guess_fn(6)) == 6);
        CHECK(s.guessNumber(1, Solution::guess_fn(1)) == 1);
        CHECK(s.guessNumber(2, Solution::guess_fn(1)) == 1);
    }

    SUBCASE("Search a 2D matrix") {
        vector<vector<int>> v{{1,  3,  5,  7},
                              {10, 11, 16, 20},
                              {23, 30, 34, 60}};
        CHECK(s.searchMatrix(v, 3) == true);
        CHECK(s.searchMatrix(v, 13) == false);
        v = {{1},
             {2},
             {3},
             {4}};
        CHECK(s.searchMatrix(v, 3) == true);
        CHECK(s.searchMatrix(v, 13) == false);
        CHECK(s.searchMatrix(v, -1) == false);
    }

    SUBCASE("Single number") {
        vector<int> v{4, 1, 2, 1, 2};
        CHECK(s.singleNumber(v) == 4);
    }
}

#pragma clang diagnostic pop

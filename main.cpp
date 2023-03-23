#define CATCH_CONFIG_MAIN
#include <vector>

#include "catch2/catch.hpp"

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

vector<int> listNode_to_vector(ListNode* node) {
    if (!node) return {};
    vector<int> head = {node->val};
    vector<int> tail = listNode_to_vector(node->next);
    head.insert(head.end(), tail.begin(), tail.end());
    return head;
}

ListNode* vector_to_listNode(vector<int>& v) {
    if (v.empty()) return nullptr;
    ListNode dummy{0};
    accumulate(v.begin(), v.end(), &dummy, [](ListNode* n, int v) {
        n->next = new ListNode(v);
        return n->next;
    });
    return dummy.next;
}

class Solution {
    ListNode** find_min(vector<ListNode*>& lists) const {
        optional<int> min_val{};
        ListNode** result{};

        for (auto* node : lists) {
            if (node) {
                if (!min_val || node->val < min_val) {
                    min_val = node->val;
                    result = &node;
                }
            }
        }
        return result;
    }

   public:
    int add(int x, int y) { return x + y; }

    // 23. Merge k Sorted Lists
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode** min_node = find_min(lists);
        if (*min_node) {
            int val = (*min_node)->val;
            *min_node = (*min_node)->next;
            return new ListNode(val, mergeKLists(lists));
        }
        return nullptr;
    }
};

TEST_CASE("Test all", "[all]") {
    auto s = Solution{};
    REQUIRE(s.add(2, 3) == 5);

    REQUIRE(listNode_to_vector(new ListNode(
                1, new ListNode(2, new ListNode(3)))) == vector<int>{1, 2, 3});

    vector<int> v = {1, 2, 3};
    auto vln = vector_to_listNode(v);
    REQUIRE(listNode_to_vector(vln) == vector<int>{1, 2, 3});
}

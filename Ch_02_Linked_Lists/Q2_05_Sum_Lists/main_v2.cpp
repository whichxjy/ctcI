// [数位正向存放]
// 时间复杂度：O(N)
// 空间复杂度：O(N)

#include <memory>
#include <vector>
#include <algorithm>
#include <stack>
#include <cassert>

template <typename T>
struct Node {
    T value;
    std::shared_ptr<Node> next;

    Node() = default;
    Node(T value) : value(value), next(nullptr) {}
    Node(T value, std::shared_ptr<Node> next) : value(value), next(next) {}
};

struct List {
    std::shared_ptr<Node<int>> head;

    List() = default;
    List(std::shared_ptr<Node<int>> head) : head(head) {}
    List(std::initializer_list<int> init_list) {
        if (init_list.size() != 0) {
            head = std::make_shared<Node<int>>(*(init_list.begin()));
            std::shared_ptr<Node<int>> curr = head;
            for (auto iter = init_list.begin() + 1; iter != init_list.end(); iter++) {
                curr->next = std::make_shared<Node<int>>(*iter);
                curr = curr->next;
            }
        }
    }

    List operator+(const List& other) {
        std::stack<int> stk1;
        std::stack<int> stk2;

        std::shared_ptr<Node<int>> curr1 = this->head;
        while (curr1 != nullptr) {
            stk1.push(curr1->value);
            curr1 = curr1->next;
        }

        std::shared_ptr<Node<int>> curr2 = other.head;
        while (curr2 != nullptr) {
            stk2.push(curr2->value);
            curr2 = curr2->next;
        }


        std::shared_ptr<Node<int>> result_head = nullptr;

        int carry = 0;

        while (!stk1.empty() || !stk2.empty()) {
            int sum = carry;

            if (!stk1.empty()) {
                sum += stk1.top();
                stk1.pop();
            }

            if (!stk2.empty()) {
                sum += stk2.top();
                stk2.pop();
            }

            if (sum < 10) {
                carry = 0;
            }
            else {
                sum -= 10;
                carry = 1;
            }

            std::shared_ptr<Node<int>> new_head = std::make_shared<Node<int>>(sum);
            new_head->next = result_head;
            result_head = new_head;
        }

        if (carry == 1) {
            std::shared_ptr<Node<int>> new_head = std::make_shared<Node<int>>(1);
            new_head->next = result_head;
            result_head = new_head;
        }

        return List(result_head);
    }

    std::vector<int> to_vector() const {
        std::vector<int> vec;
        std::shared_ptr<Node<int>> curr = head;
        while (curr != nullptr) {
            vec.push_back(curr->value);
            curr = curr->next;
        }
        return vec;
    }
};

template <typename T>
void check_equal(const std::vector<T>& lhs, const std::vector<T>& rhs) {
    assert(std::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

void check_equal(const List& lhs, const std::vector<int>& rhs) {
    check_equal(lhs.to_vector(), rhs);
}

int main() {
    {
        List lst1 = {};
        List lst2 = { 1 };
        List result = lst1 + lst2;
        check_equal(result, { 1 });
    }
    {
        List lst1 = { 2, 1 };
        List lst2 = { 6, 5, 4 };
        List result = lst1 + lst2;
        check_equal(result, { 6, 7, 5 });
    }
    {
        List lst1 = { 6, 1, 7 };
        List lst2 = { 2, 9, 5 };
        List result = lst1 + lst2;
        check_equal(result, { 9, 1, 2 });
    }
    {
        List lst1 = { 9, 9, 9 };
        List lst2 = { 9, 9, 9 };
        List result = lst1 + lst2;
        check_equal(result, { 1, 9, 9, 8 });
    }
}
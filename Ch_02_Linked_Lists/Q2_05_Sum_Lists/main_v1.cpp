// [数位反向存放]
// 时间复杂度：O(N)
// 空间复杂度：O(1)

#include <memory>
#include <vector>
#include <algorithm>
#include <cmath>
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
        std::shared_ptr<Node<int>> lhs = this->head;
        std::shared_ptr<Node<int>> rhs = other.head;

        std::shared_ptr<Node<int>> result_head = nullptr;
        std::shared_ptr<Node<int>> result_curr = nullptr;

        int carry = 0;

        while (lhs != nullptr || rhs != nullptr) {
            int sum = carry;

            if (lhs != nullptr) {
                sum += lhs->value;
            }
            if (rhs != nullptr) {
                sum += rhs->value;
            }

            if (sum < 10) {
                carry = 0;
            }
            else {
                sum -= 10;
                carry = 1;
            }

            if (result_head == nullptr) {
                result_head = std::make_shared<Node<int>>(sum);
                result_curr = result_head;
            }
            else {
                result_curr->next = std::make_shared<Node<int>>(sum);
                result_curr = result_curr->next;
            }

            if (lhs != nullptr) {
                lhs = lhs->next;
            }
            if (rhs != nullptr) {
                rhs = rhs->next;
            }
        }

        if (carry == 1) {
            result_curr->next = std::make_shared<Node<int>>(1);
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
        List lst1 = { 1, 2 };
        List lst2 = { 4, 5, 6 };
        List result = lst1 + lst2;
        check_equal(result, { 5, 7, 6 });
    }
    {
        List lst1 = { 7, 1, 6 };
        List lst2 = { 5, 9, 2 };
        List result = lst1 + lst2;
        check_equal(result, { 2, 1, 9 });
    }
    {
        List lst1 = { 9, 9, 9 };
        List lst2 = { 9, 9, 9 };
        List result = lst1 + lst2;
        check_equal(result, { 8, 9, 9, 1 });
    }
}
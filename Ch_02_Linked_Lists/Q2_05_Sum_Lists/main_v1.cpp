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

    int operator+(const List& other) {
        std::shared_ptr<Node<int>> lhs = this->head;
        std::shared_ptr<Node<int>> rhs = other.head;

        int result = 0;
        int k = 0;
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

            result += (sum * std::pow(10, k));
            k += 1;

            if (lhs != nullptr) {
                lhs = lhs->next;
            }
            if (rhs != nullptr) {
                rhs = rhs->next;
            }
        }

        if (carry == 1) {
            result += std::pow(10, k);
        }

        return result;
    }
};

int main() {
    {
        List lst1 = {};
        List lst2 = { 1 };
        int result = lst1 + lst2;
        assert(result == 1);
    }
    {
        List lst1 = { 1, 2 };
        List lst2 = { 4, 5, 6 };
        int result = lst1 + lst2;
        assert(result == 675);
    }
    {
        List lst1 = { 7, 1, 6 };
        List lst2 = { 5, 9, 2 };
        int result = lst1 + lst2;
        assert(result == 912);
    }
    {
        List lst1 = { 9, 9, 9 };
        List lst2 = { 9, 9, 9 };
        int result = lst1 + lst2;
        assert(result == 1998);
    }
}
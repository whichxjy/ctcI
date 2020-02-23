// 时间复杂度：O(N)
// 空间复杂度：O(1)

#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <cassert>

template <typename T>
struct Node {
    T value;
    std::shared_ptr<Node> next;

    Node() = default;
    Node(T value) : value(value), next(nullptr) {}
    Node(T value, std::shared_ptr<Node> next) : value(value), next(next) {}
};

template <typename T>
struct List {
    std::shared_ptr<Node<T>> head;

    List() = default;
    List(std::shared_ptr<Node<T>> head) : head(head) {}
    List(std::initializer_list<T> init_list) {
        if (init_list.size() != 0) {
            head = std::make_shared<Node<T>>(*(init_list.begin()));
            std::shared_ptr<Node<T>> curr = head;
            for (auto iter = init_list.begin() + 1; iter != init_list.end(); iter++) {
                curr->next = std::make_shared<Node<T>>(*iter);
                curr = curr->next;
            }
        }
    }

    void partition(T x) {
        // store elements that smaller that x
        std::shared_ptr<Node<T>> small_begin = nullptr;
        std::shared_ptr<Node<T>> small_end = nullptr;
         // store elements that equal or larger that x
        std::shared_ptr<Node<T>> large_begin = nullptr;
        std::shared_ptr<Node<T>> large_end = nullptr;

        std::shared_ptr<Node<T>> curr = head;

        while (curr != nullptr) {
            if (curr->value < x) {
                // put in the smaller list
                if (small_begin == nullptr) {
                    // init
                    small_begin = curr;
                    small_end = curr;
                }
                else {
                    // append
                    small_end->next = curr;
                    small_end = small_end->next;
                }
            }
            else {
                // put in the larger list
                if (large_begin == nullptr) {
                    large_begin = curr;
                    large_end = curr;
                }
                else {
                    // append
                    large_end->next = curr;
                    large_end = large_end->next;
                }
            }

            curr = curr->next;
        }

        // merge the two lists
        if (small_begin == nullptr) {
            head = large_begin;
        }
        else {
            small_end->next = large_begin;
            head = small_begin;
        }
    }

     // display nodes
    void display() const {
        std::shared_ptr<Node<T>> curr = head;
        while (curr != nullptr) {
            std::cout << curr->value << " ";
            curr = curr->next;
        }
        std::cout << std::endl;
    }

    std::vector<T> to_vector() const {
        std::vector<T> vec;
        std::shared_ptr<Node<T>> curr = head;
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

template <typename T>
void check_equal(const List<T>& lhs, const std::vector<T>& rhs) {
    check_equal(lhs.to_vector(), rhs);
}

int main() {
    List<int> lst = { 33, 9, 2, 3, 10, 10389, 838, 874578, 5 };
    lst.partition(3);
    lst.display();
    check_equal(lst, { 2, 33, 9, 3, 10, 10389, 838, 874578, 5 });
}
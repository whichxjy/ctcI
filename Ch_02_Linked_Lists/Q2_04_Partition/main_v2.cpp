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
        // put the small elements to the head
        std::shared_ptr<Node<T>> store_head = nullptr;
        // put the large elements to the tail
        std::shared_ptr<Node<T>> store_tail = nullptr;

        std::shared_ptr<Node<T>> curr = head;

        while (curr != nullptr) {
            // store next
            std::shared_ptr<Node<T>> next = curr->next;

            if (curr->value < x) {
                // put to the head
                if (store_head == nullptr) {
                    store_head = curr;
                    store_tail = curr;
                }
                else {
                    curr->next = store_head;
                    store_head = curr;
                }
            }
            else {
                // put to the end
                if (store_tail == nullptr) {
                    store_head = curr;
                    store_tail = curr;
                }
                else {
                    store_tail->next = curr;
                    store_tail = curr;
                }
            }

            curr = next;
        }

        if (store_tail != nullptr) {
            store_tail->next = nullptr;
        }

        head = store_head;
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
    List<int> lst = { 3, 5, 8, 5, 10, 2, 1 };
    lst.partition(5);
    lst.display();
    check_equal(lst, { 1, 2, 3, 5, 8, 5, 10 });
}
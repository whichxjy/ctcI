// 时间复杂度：O(N)
// 空间复杂度：O(N)

#include <iostream>
#include <memory>
#include <vector>
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
    bool found;
    T result;

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

    T find_kth_to_last(int k) {
        found = false;
        count(head, k);
        if (found) {
            return result;
        }
        else {
            throw std::exception();
        }
    }

    // the number of nodes to the last
    int count(std::shared_ptr<Node<T>> curr, int k) {
        if (curr == nullptr) {
            return 0;
        }
        else {
            int curr_count = count(curr->next, k) + 1;
            if (curr_count == k) {
                found = true;
                result = curr->value;
            }
            return curr_count;
        }
    }
};

int main() {
    List<int> lst = { 1, 2, 3, 4, 5, 6 };
    assert(lst.find_kth_to_last(1) == 6);
    assert(lst.find_kth_to_last(2) == 5);
    assert(lst.find_kth_to_last(3) == 4);
    assert(lst.find_kth_to_last(4) == 3);
    assert(lst.find_kth_to_last(5) == 2);
    assert(lst.find_kth_to_last(6) == 1);
}
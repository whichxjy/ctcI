// 时间复杂度：O(N)
// 空间复杂度：O(N)

#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <unordered_set>
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

    void append(T value) {
        if (head == nullptr) {
            head = std::make_shared<Node<T>>(Node(value));
        }
        else {
            std::shared_ptr<Node<T>> curr = head;
            while (curr->next != nullptr) {
                curr = curr->next;
            }
            curr->next = std::make_shared<Node<T>>(value);
        }
    }

    void remove_dups() {
        std::unordered_set<T> visited;

        std::shared_ptr<Node<T>> prev = nullptr;
        std::shared_ptr<Node<T>> curr = head;

        while (curr != nullptr) {
            if (visited.find(curr->value) == visited.end()) {
                // not visited
                visited.insert(curr->value);
                prev = curr;
                curr = curr->next;
            }
            else {
                // already visited
                prev->next = curr->next;
                curr = prev->next;
            }
        }
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
    {
        List<int> lst;
        lst.remove_dups();
        check_equal(lst, {});
    }
    {
        List<int> lst;
        lst.append(1);
        lst.remove_dups();
        check_equal(lst, { 1 });
    }
    {
        List<int> lst;
        lst.append(1);
        lst.append(2);
        lst.append(3);
        lst.append(2);
        lst.append(4);
        lst.remove_dups();
        check_equal(lst, { 1, 2, 3, 4 });
    }
    {
        List<int> lst;
        lst.append(5);
        lst.append(5);
        lst.append(5);
        lst.append(5);
        lst.append(5);
        lst.remove_dups();
        check_equal(lst, { 5 });
    }
}
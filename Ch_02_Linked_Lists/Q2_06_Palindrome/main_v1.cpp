// 时间复杂度：O(N)
// 空间复杂度：O(N)

#include <memory>
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

    List<T> reverse_and_clone() {
        std::shared_ptr<Node<T>> new_head = nullptr;

        std::shared_ptr<Node<T>> curr = head;

        while (curr != nullptr) {
            if (new_head == nullptr) {
                // init
                new_head = std::make_shared<Node<T>>(curr->value);
            }
            else {
                auto new_node = std::make_shared<Node<T>>(curr->value);
                new_node->next = new_head;
                new_head = new_node;
            }

            curr = curr->next;
        }

        return List<T>(new_head);
    }

    bool operator==(const List& other) {
        auto lhs = head;
        auto rhs = other.head;

        while (lhs != nullptr && rhs != nullptr) {
            if (lhs->value != rhs->value) {
                return false;
            }
            else {
                lhs = lhs->next;
                rhs = rhs->next;
            }
        }

        if (lhs == nullptr && rhs == nullptr) {
            return true;
        }
        else {
            return false;
        }
    }

    bool is_palindrome() {
        return this->reverse_and_clone() == *this;
    }
};


int main() {
    {
        List<int> lst = { 0, 1, 2, 1, 0 };
        assert(lst.is_palindrome());
    }
    {
        List<int> lst = { 0, 1, 2, 3, 1, 0 };
        assert(!lst.is_palindrome());
    }
}
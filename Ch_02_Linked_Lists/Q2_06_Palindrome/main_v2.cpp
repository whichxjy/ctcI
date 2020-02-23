// 时间复杂度：O(N)
// 空间复杂度：O(1)

#include <memory>
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

    bool is_palindrome() {
        std::shared_ptr<Node<T>> slow = head;
        std::shared_ptr<Node<T>> fast = head;

        std::stack<T> stk;

        while (fast != nullptr && fast->next != nullptr) {
            stk.push(slow->value);
            slow = slow->next;
            fast = fast->next->next;
        }

        if (fast != nullptr) {
            slow = slow->next;
        }

        while (slow != nullptr) {
            if (slow->value != stk.top()) {
                return false;
            }
            else {
                stk.pop();
                slow = slow->next;
            }
        }

        return true;
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
    {
        List<int> lst = { 0, 1, 2, 3, 3, 2, 1, 0 };
        assert(lst.is_palindrome());
    }
}
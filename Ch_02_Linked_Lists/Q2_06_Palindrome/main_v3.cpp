// 时间复杂度：O(N)
// 空间复杂度：O(N)

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
    struct Result {
        bool result;
        std::shared_ptr<Node<T>> end_node;

        Result(bool result, std::shared_ptr<Node<T>> end_node)
        : result(result), end_node(end_node) {}
    };

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

    int getLength() {
        int length = 0;
        std::shared_ptr<Node<T>> curr = head;

        while (curr != nullptr) {
            length += 1;
            curr = curr->next;
        }

        return length;
    }

    bool is_palindrome() {
        Result res = is_palindrome(head, this->getLength());
        return res.result;
    }

    Result is_palindrome(std::shared_ptr<Node<T>> curr_head, int length) {
        if (curr_head == nullptr || length <= 0) {
            // even number of nodes
            return { true, curr_head };
        }
        else if (length == 1) {
            // odd number of nodes
            return { true, curr_head->next };
        }
        else {
            Result res = is_palindrome(curr_head->next, length - 2);

            if (res.result == false || res.end_node == nullptr) {
                return res;
            }
            else {
                res.result = (curr_head->value == res.end_node->value);
                res.end_node = res.end_node->next;
                return res;
            }
        }
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
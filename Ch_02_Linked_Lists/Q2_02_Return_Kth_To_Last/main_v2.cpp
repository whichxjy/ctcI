// 时间复杂度：O(N)
// 空间复杂度：O(1)

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
        std::shared_ptr<Node<T>> kth_node_to_last = find_kth_node_to_last(k);
        if (kth_node_to_last != nullptr) {
            return kth_node_to_last->value;
        }
        else {
            throw std::exception();
        }
    }

    std::shared_ptr<Node<T>> find_kth_node_to_last(int k) {
        // fast pointer
        std::shared_ptr<Node<T>> fast = head;
        // slow pointer
        std::shared_ptr<Node<T>> slow = head;

        // move fast pointer k steps first
        for (int i = 0; i < k; i++) {
            if (fast == nullptr) {
                return nullptr;
            }
            else {
                fast = fast->next;
            }
        }

        // move the two pointers together
        while (fast != nullptr) {
            fast = fast->next;
            slow = slow->next;
        }

        return slow;
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
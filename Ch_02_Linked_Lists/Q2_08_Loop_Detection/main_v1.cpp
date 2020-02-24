// 解法：用哈希表存储已访问的节点。
// 时间复杂度：O(N)
// 空间复杂度：O(N)

#include <memory>
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

    std::shared_ptr<Node<T>> find_loop_begin() {
        std::unordered_set<std::shared_ptr<Node<T>>> visited;
        auto curr = head;

        while (curr != nullptr) {
            if (visited.find(curr) != visited.end()) {
                // already visited
                return curr;
            }
            else {
                // not visited
                visited.insert(curr);
                curr = curr->next;
            }
        }

        return nullptr;
    }
};

int main() {
    {
        List<int> lst = { 1 };
        assert(lst.find_loop_begin() == nullptr);
    }
    {
        List<int> lst = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        assert(lst.find_loop_begin() == nullptr);
    }
    {
        List<int> lst = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        auto loop_begin = lst.head->next->next->next->next->next;
        auto curr = lst.head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = loop_begin;
        assert(lst.find_loop_begin() == loop_begin);
    }
}
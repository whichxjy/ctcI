// 时间复杂度：O(N)
// 空间复杂度：O(1)

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

// delete the target node
template <typename T>
bool delete_node(std::shared_ptr<Node<T>> target) {
    if (target == nullptr || target->next == nullptr) {
        return false;
    }
    else {
        std::shared_ptr<Node<T>> next = target->next;
        target->value = next->value;
        target->next = next->next;
        return true;
    }
}

template <typename T>
void check_equal(const std::vector<T>& lhs, const std::vector<T>& rhs) {
    assert(std::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <typename T>
void check_equal(const List<T>& lhs, const std::vector<T>& rhs) {
    check_equal(lhs.to_vector(), rhs);
}

int main() {
    List<int> lst = { 1, 2, 3, 4, 5 ,6 };
    std::shared_ptr<Node<int>> target = lst.head->next->next->next;
    bool result = delete_node(target);
    assert(result == true);
    check_equal(lst, { 1, 2, 3, 5, 6 });
}
// 时间复杂度：O(N)
// 空间复杂度：O(1)

#include <memory>
#include <stack>
#include <cmath>
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
    struct Info {
        std::shared_ptr<Node<T>> tail;
        int length;

        Info(std::shared_ptr<Node<T>> tail, int length)
        : tail(tail), length(length) {}
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

    Info get_tail_and_length() const {
        std::shared_ptr<Node<T>> prev = nullptr;
        std::shared_ptr<Node<T>> curr = head;
        int length = 0;

        while (curr != nullptr) {
            length += 1;
            prev = curr;
            curr = curr->next;
        }

        return { prev, length };
    }

    std::shared_ptr<Node<T>> find_intersection(const List<T>& other) const {
        Info info1 = this->get_tail_and_length();
        Info info2 = other.get_tail_and_length();

        // check if the two lists have the same tail
        if (info1.tail != info2.tail) {
            return nullptr;
        }
        else {
            auto shorter = (info1.length < info2.length) ? this->head : other.head;
            auto longer = (info1.length >= info2.length) ? this->head : other.head;

            // ignore some nodes in the longer list to let the two lists have the same length
            int step = std::abs(info1.length - info2.length);
            for (int i = 0; i < step; i++) {
                longer = longer->next;
            }

            // move to the intersection
            while (shorter != longer) {
                shorter = shorter->next;
                longer = longer->next;
            }

            return shorter;
        }
    }
};

int main() {
    {
        List<int> tail_list = { 7, 2, 1 };

        List<int> lst1 = { 3, 1, 5, 9 };
        auto curr1 = lst1.head;
        while (curr1->next != nullptr) {
            curr1 = curr1->next;
        }
        curr1->next = tail_list.head;


        List<int> lst2 = { 4, 6 };
        auto curr2 = lst2.head;
        while (curr2->next != nullptr) {
            curr2 = curr2->next;
        }
        curr2->next = tail_list.head;

        assert(lst1.find_intersection(lst2) == tail_list.head);
    }
    {
        List<int> lst1 = { 3, 1, 5, 9, 7, 2, 1 };
        List<int> lst2 = { 4, 6, 7, 2, 1 };

        assert(lst1.find_intersection(lst2) == nullptr);
    }
}
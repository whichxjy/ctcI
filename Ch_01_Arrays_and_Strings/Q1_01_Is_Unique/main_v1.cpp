// 解法：哈希表。
// 时间复杂度：O(N)
// 空间复杂度：O(N)

#include <string>
#include <unordered_set>
#include <cassert>

bool is_unique(const std::string& str) {
    std::unordered_set<char> st;

    for (char ch : str) {
        if (st.find(ch) != st.end()) {
            // the set contains the char
            return false;
        }
        else {
            st.insert(ch);
        }
    }

    return true;
}

int main() {
    assert(is_unique("") == true);
    assert(is_unique("abcdefg") == true);
    assert(is_unique("abcdefgaijk") == false);
}
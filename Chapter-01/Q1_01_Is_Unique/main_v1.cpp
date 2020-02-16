// 解法：哈希表。
// 时间复杂度：O(N)
// 空间复杂度：O(N)

#include <iostream>
#include <string>
#include <unordered_set>
#include <cassert>

bool isUnique(const std::string& str) {
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
    assert(isUnique("") == true);
    assert(isUnique("abcdefg") == true);
    assert(isUnique("abcdefgaijk") == false);
}
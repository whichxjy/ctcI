// 解法：哈希表计数。
// 时间复杂度：O(N)
// 空间复杂度：O(N)

#include <string>
#include <unordered_map>
#include <vector>
#include <array>
#include <cassert>

bool check_permutation(const std::string& str1, const std::string& str2) {
    if (str1.size() != str2.size()) {
        return false;
    }

    std::unordered_map<char, unsigned> count1;
    std::unordered_map<char, unsigned> count2;

    for (int i = 0; i < str1.size(); i++) {
        count1[str1[i]] += 1;
        count2[str2[i]] += 1;
    }

    for (const auto& [key, value] : count1) {
        if (count2[key] != value) {
            return false;
        }
    }

    return true;
}

int main() {
    std::vector<std::array<std::string, 2>> pairs = {
        { "apple", "papel" },
        { "carrot", "tarroc" },
        { "hello", "llloh" }
    };
    std::vector<bool> expect = { true, true, false };
    for (int i = 0; i < pairs.size(); i++) {
        assert(check_permutation(pairs[i][0], pairs[i][1]) == expect[i]);
    }
}
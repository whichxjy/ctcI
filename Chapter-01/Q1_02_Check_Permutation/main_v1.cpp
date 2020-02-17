// 解法：分别将两个字符串排序。
// 时间复杂度：O(N * logN)
// 空间复杂度：O(N)（如果可以就地排序，则为 O(1)）

#include <string>
#include <algorithm>
#include <vector>
#include <array>
#include <cassert>

bool checkPermutation(const std::string& str1, const std::string& str2) {
    std::string str1_sorted = str1;
    std::sort(str1_sorted.begin(), str1_sorted.end());

    std::string str2_sorted = str2;
    std::sort(str2_sorted.begin(), str2_sorted.end());

    return str1_sorted == str2_sorted;
}

int main() {
    std::vector<std::array<std::string, 2>> pairs = {
        { "apple", "papel" },
        { "carrot", "tarroc" },
        { "hello", "llloh" }
    };
    std::vector<bool> expect = { true, true, false };
    for (int i = 0; i < pairs.size(); i++) {
        assert(checkPermutation(pairs[i][0], pairs[i][1]) == expect[i]);
    }
}
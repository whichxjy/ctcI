// 时间复杂度：O(N)
// 空间复杂度：O(N)

#include <string>
#include <vector>
#include <array>
#include <cassert>

bool is_substring(const std::string& big, const std::string& small) {
    if (big.find(small) != std::string::npos) {
        return true;
    }
    else {
        return false;
    }
}

bool is_rotation(const std::string& str1, const std::string& str2) {
    if (str1.size() != str2.size() || str1.size() == 0) {
        return false;
    }

    const std::string str1str1 = str1 + str1;
    return is_substring(str1str1, str2);
}

int main() {
    std::vector<std::array<std::string, 2>> pairs = {
        { "", "" },
        { "a", "a" },
        { "apple", "pleap" },
        { "waterbottle", "erbottlewat" },
        { "camera", "macera" }
    };

    std::vector<bool> expect = { false, true, true, true, false };

    for (int i = 0; i < pairs.size(); i++) {
        assert(is_rotation(pairs[i][0], pairs[i][1]) == expect[i]);
    }
}
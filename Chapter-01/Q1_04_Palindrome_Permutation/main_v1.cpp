// 时间复杂度：O(N)
// 空间复杂度：O(N)

#include <unordered_map>
#include <string>
#include <cctype>
#include <vector>
#include <cassert>

bool isPalindromePermutation(const std::string& str) {
    std::unordered_map<char, unsigned> count;

    for (const char ch : str) {
        if (ch != ' ') {
            count[tolower(ch)] += 1;
        }
    }

    bool already_had_odd = false;

    for (const auto& kv : count) {
        if (kv.second % 2 != 0) {
            if (already_had_odd) {
                return false;
            }
            else {
                already_had_odd = true;
            }
        }
    }

    return true;
}

int main() {
    std::vector<std::string> strs = {
        "Rats live on no evil star",
		"A man, a plan, a canal, panama",
		"Lleve",
		"Tacotac",
		"asda"
    };
    std::vector<bool> expect = { true, false, true, true, false };

    for (int i = 0; i < strs.size(); i++) {
        assert(isPalindromePermutation(strs[i]) == expect[i]);
    }
}
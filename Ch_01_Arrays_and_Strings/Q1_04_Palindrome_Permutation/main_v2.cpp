// 时间复杂度：O(N)
// 空间复杂度：O(1)

#include <string>
#include <cctype>
#include <vector>
#include <cassert>

bool is_palindrome_permutation(const std::string& str) {
    // 0: even
    // 1: odd
    unsigned bitfield = 0;

    for (const char ch : str) {
        if (ch != ' ') {
            int index = static_cast<unsigned>(tolower(ch));
            bitfield ^= (1 << index);
        }
    }

    bool already_had_odd = false;

    while (bitfield != 0) {
        if ((bitfield & 1) == 1) {
            if (already_had_odd) {
                return false;
            }
            else {
                already_had_odd = true;
            }
        }
        bitfield >>= 1;
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
        assert(is_palindrome_permutation(strs[i]) == expect[i]);
    }
}
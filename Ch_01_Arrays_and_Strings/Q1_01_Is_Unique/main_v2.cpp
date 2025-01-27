// 解法：位运算。
// 时间复杂度：O(N)
// 空间复杂度：O(1)

#include <string>
#include <cassert>

bool is_unique(const std::string& str) {
    unsigned bitfield = 0;

    for (char ch : str) {
        int index = static_cast<int>(ch);
        if (((1 << index) & bitfield) != 0) {
            // the char already exists
            return false;
        }
        else {
            bitfield |= (1 << index);
        }
    }

    return true;
}

int main() {
    assert(is_unique("") == true);
    assert(is_unique("abcdefg") == true);
    assert(is_unique("abcdefgaijk") == false);
}
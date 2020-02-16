#include <iostream>
#include <string>
#include <cassert>

bool isUnique(const std::string& str) {
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
    assert(isUnique("") == true);
    assert(isUnique("abcdefg") == true);
    assert(isUnique("abcdefgaijk") == false);
}
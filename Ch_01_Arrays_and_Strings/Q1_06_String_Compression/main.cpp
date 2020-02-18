#include <string>
#include <cassert>

std::string compress(const std::string& str) {
    if (str.size() == 0) {
        return "";
    }

    std::string compressed_str(1, str[0]);
    int count = 1;

    for (int i = 1; i < str.size(); i++) {
        if (str[i] == compressed_str.back()) {
            count += 1;
        }
        else {
            compressed_str += std::to_string(count);
            compressed_str += str[i];
            count = 1;
        }
    }

    compressed_str += std::to_string(count);

    return (compressed_str.size() < str.size()) ? compressed_str : str;
}

int main() {
    assert(compress("") == "");
    assert(compress("a") == "a");
    assert(compress("aaaaabbbbaaaabbddc") == "a5b4a4b2d2c1");
}
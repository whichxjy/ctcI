#include <string>
#include <cmath>
#include <vector>
#include <array>
#include <cassert>

bool oneEditInsertOrDelete(const std::string& str1, const std::string& str2) {
    if (std::abs(static_cast<int>(str1.size() - str2.size())) != 1) {
        return false;
    }

    int index1 = 0;
    int index2 = 0;
    bool found_diff = false;

    while (index1 < str1.size() && index2 < str2.size()) {
        if (str1[index1] == str2[index2]) {
            index1 += 1;
            index2 += 1;
        }
        else if (found_diff) {
            return false;
        }
        else if (str1.size() < str2.size()) {
            index2 += 1;
            found_diff = true;
        }
        else {
            index1 += 1;
            found_diff = true;
        }
    }

    return true;
}

bool oneEditUpdate(const std::string& str1, const std::string& str2) {
    if (str1.size() != str2.size()) {
        return false;
    }

    int index1 = 0;
    int index2 = 0;
    bool found_diff = false;

    for (int i = 0; i < str1.size(); i++) {
        if (str1[i] == str2[i]) {
            continue;
        }
        else if (found_diff) {
            return false;
        }
        else {
            found_diff = true;
        }
    }

    return true;
}

bool oneEdit(const std::string& str1, const std::string& str2) {
    return oneEditInsertOrDelete(str1, str2) || oneEditUpdate(str1, str2);
}

int main() {
    std::vector<std::array<std::string, 2>> tests = {
        { "", "d" },
        { "d", "de" },
        { "pale", "pse" },
        { "acdsfdsfadsf", "acdsgdsfadsf" },
        { "acdsfdsfadsf", "acdsfdfadsf" },
        { "acdsfdsfadsf", "acdsfdsfads" },
        { "acdsfdsfadsf", "cdsfdsfadsf" },
        { "adfdsfadsf", "acdfdsfdsf" },
        { "adfdsfadsf", "bdfdsfadsg" },
        { "adfdsfadsf", "affdsfads" },
        { "pale", "pkle" },
    };
    std::vector<bool> expect = {
        true,
        true,
        false,
        true,
        true,
        true,
        true,
        false,
        false,
        false,
        true
    };

    for (int i = 0; i < tests.size(); i++) {
        assert(oneEdit(tests[i][0], tests[i][1]) == expect[i]);
    }
}
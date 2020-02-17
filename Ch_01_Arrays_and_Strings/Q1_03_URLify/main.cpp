// 时间复杂度：O(N)
// 空间复杂度：O(1)

#include <string>
#include <cassert>

// urlify the text inplace
void urlify(std::string& text, int true_length) {
    // number of spaces in the true string
    int space_num = 0;
    for (int i = 0; i < true_length; i++) {
        if (text[i] == ' ') {
            space_num += 1;
        }
    }

    // the length of the urlified string
    // = the-number-of-non-space-char-in-the-true-string + 3 * space-num
    int extend_length = true_length + 2 * space_num;
    // the position to start replacing
    int replace_index =  extend_length - 1;


    for (int i = true_length - 1; i >= 0; i--) {
        if (text[i] != ' ') {
            // replace directly
            text[replace_index] = text[i];
            replace_index -= 1;
        }
        else {
            // replace the space with "%20"
            text[replace_index] = '0';
            text[replace_index - 1] = '2';
            text[replace_index - 2] = '%';
            replace_index -= 3;
        }
    }
}

int main() {
    std::string text = "Mr John Smith    ";
    // the length of "Mr John Smith" is 13
    urlify(text, 13);
    assert(text == "Mr%20John%20Smith");
}
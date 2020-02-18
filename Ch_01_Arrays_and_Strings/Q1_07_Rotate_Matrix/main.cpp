// 时间复杂度：O(N ^ 2)
// 空间复杂度：O(1)

#include <iostream>
#include <vector>
#include <cassert>

// width == height
using Matrix = std::vector<std::vector<int>>;

bool rotate(Matrix& matrix) {
    if (matrix.size() == 0 || matrix.size() != matrix[0].size()) {
        return false;
    }

    int N = matrix.size();

    for (int layer = 0; layer < N / 2; layer++) {
        int first = layer;
        int last = N - layer - 1;

        for (int i = first; i < last; i++) {
            // save top
            int top = matrix[first][i];

            int offset = i - first;

            // left -> top
            matrix[first][i] = matrix[last - offset][first];

            // bottom -> left
            matrix[last - offset][first] = matrix[last][last - offset];

            // right -> bottom
            matrix[last][last - offset] = matrix[i][last];

            // // top -> right
            matrix[i][last] = top;
        }
    }

    return true;
}


int main() {
    Matrix matrix = {
        { 1, 2, 3 },
        { 4, 5, 6 },
        { 7, 8, 9 }
    };

    Matrix expect = {
        { 7, 4, 1 },
        { 8, 5, 2 },
        { 9, 6, 3 }
    };

    bool rotated = rotate(matrix);
    assert(rotated == true);

    int N = 3;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            assert(matrix[i][j] == expect[i][j]);
        }
    }
}
// 时间复杂度：O(N ^ 2)
// 空间复杂度：O(N)

#include <vector>
#include <cassert>

using Matrix = std::vector<std::vector<int>>;

void reset_row(Matrix& matrix, int row_index) {
    int col = matrix[0].size();

    for (int i = 0; i < col; i++) {
        matrix[row_index][i] = 0;
    }
}

void reset_col(Matrix& matrix, int col_index) {
    int row = matrix.size();

    for (int i = 0; i < row; i++) {
        matrix[i][col_index] = 0;
    }
}

void set_zeros(Matrix& matrix) {
    int row = matrix.size();
    int col = matrix[0].size();

    std::vector<bool> clear_row(row, false);
    std::vector<bool> clear_col(col, false);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (matrix[i][j] == 0) {
                clear_row[i] = true;
                clear_col[j] = true;
            }
        }
    }

    for (int i = 0; i < row; i++) {
        if (clear_row[i]) {
            reset_row(matrix, i);
        }
    }

    for (int i = 0; i < col; i++) {
        if (clear_col[i]) {
            reset_col(matrix, i);
        }
    }
}

int main() {
    Matrix matrix = {
        { 1, 2, 0, 4, 5 },
        { 0, 2, 3, 4, 0 },
        { 1, 2, 3, 4, 5 },
        { 1, 2, 3, 4, 5 },
        { 0, 2, 0, 3, 0 }
    };

    Matrix expect = {
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 },
        { 0, 2, 0, 4, 0 },
        { 0, 2, 0, 4, 0 },
        { 0, 0, 0, 0, 0 }
    };

    set_zeros(matrix);

    int row = matrix.size();
    int col = matrix[0].size();

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            assert(matrix[i][j] == expect[i][j]);
        }
    }
}
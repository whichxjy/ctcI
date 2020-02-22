// 解法：用第一行和第一列存储状态。
// 时间复杂度：O(N ^ 2)
// 空间复杂度：O(1)

#include <vector>
#include <cassert>

using Matrix = std::vector<std::vector<int>>;

void clear_row(Matrix& matrix, int row_index) {
    int col = matrix[0].size();

    for (int i = 0; i < col; i++) {
        matrix[row_index][i] = 0;
    }
}

void clear_col(Matrix& matrix, int col_index) {
    int row = matrix.size();

    for (int i = 0; i < row; i++) {
        matrix[i][col_index] = 0;
    }
}

void set_zeros(Matrix& matrix) {
    int row = matrix.size();
    int col = matrix[0].size();

    // check if the first row has a zero
    bool first_row_has_zero = false;

    for (int i = 0; i < col; i++) {
        if (matrix[0][i] == 0) {
            first_row_has_zero = true;
            break;
        }
    }

    // check if the first column has a zero
    bool first_col_has_zero = false;

    for (int i = 0; i < row; i++) {
        if (matrix[i][0] == 0) {
            first_col_has_zero = true;
            break;
        }
    }

    // check if the rest of the matrix has zeros
    for (int i = 1; i < row; i++) {
        for (int j = 1; j < col; j++) {
            if (matrix[i][j] == 0) {
                matrix[i][0] = 0;
                matrix[0][j] = 0;
            }
        }
    }

    // clear rows
    for (int i = 1; i < row; i++) {
        if (matrix[i][0] == 0) {
            clear_row(matrix, i);
        }
    }

    // clear columns
    for (int i = 1; i < col; i++) {
        if (matrix[0][i] == 0) {
            clear_col(matrix, i);
        }
    }

    // clear the first row
    clear_row(matrix, 0);

    // clear the first column
    clear_col(matrix, 0);
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
#include "hw1.h"
#include <vector>
#include <iostream>
#include <random>
#include <stdexcept>
#include <iomanip>
#include <cmath>
#include <utility>

namespace algebra {
    using std::vector; using std::cout;
    using std::endl;

    Matrix zeros(size_t n, size_t m) {
        Matrix result{n, vector<double>(m, 0.0)};
        return result;
    }
    
    Matrix ones(size_t n, size_t m) {
        Matrix result{n, vector<double>(m, 1.0)};
        return result;
    }

    Matrix random(size_t n, size_t m, double min, double max) {
        if (min > max) {
            throw std::logic_error("min cannot be greater than max");
        }
        Matrix result = zeros(n, m);
        std::uniform_real_distribution<double> unif(min, max);
        std::default_random_engine re;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                result[i][j] = unif(re);
            }
        }
        return result;
    }

    void show(const Matrix& matrix) {
        int row = matrix.size(); int col = (row >= 1) ?  matrix[0].size() : 0;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                cout << std::left << std::setw(10) << std::fixed << std::setprecision(2) << matrix[i][j];
            }
            cout << endl;
        } 
    }

    Matrix multiply(const Matrix& matrix, double c) {
        Matrix result{matrix};
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[i].size(); j++) {
                result[i][j] *= c;
            }
        }
        return result;
    }

    Matrix multiply(const Matrix& matrix1, const Matrix& matrix2) {
        if (matrix1.empty() && matrix2.empty()) return {};
        if (matrix1.empty() || matrix2.empty()) throw std::logic_error("matrices with wrong dimensions");
        if (matrix1[0].size() != matrix2.size()) throw std::logic_error("matrices with wrong dimensions");
        int row = matrix1.size(); int col = matrix2[0].size();
        Matrix result = zeros(row, col);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                double sum = 0;
                for (int k = 0; k < matrix1[0].size(); k++) {
                    sum += (matrix1[i][k] * matrix2[k][j]);
                }
                result[i][j] = sum;
            }
        }
        return result;
    }

    Matrix sum(const Matrix& matrix, double c) {
        if (matrix.empty()) return {};
        Matrix result{matrix};
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[0].size(); j++) {
                result[i][j] += c;
            }
        }
        return result;
    }

    Matrix sum(const Matrix& matrix1, const Matrix& matrix2) {
        if (matrix1.empty() && matrix2.empty()) return {};
        if (matrix1.empty() || matrix2.empty()) throw std::logic_error("wrong dimensions");
        if (matrix1.size() != matrix2.size() || matrix1[0].size() != matrix2[0].size()) {
            throw std::logic_error("wrong dimensions");
        }
        int row = matrix1.size(); int col = matrix1[0].size();
        Matrix result{matrix1};
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                result[i][j] += matrix2[i][j];
            }
        }
        return result;
    }

    Matrix transpose(const Matrix& matrix) {
        if (matrix.empty()) return {};
        if (matrix[0].empty()) return {};
        int row = matrix.size(); int col = matrix[0].size();
        Matrix result{zeros(col, row)};
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                result[j][i] = matrix[i][j];
            }
        }
        return result;
    }

    Matrix minor(const Matrix& matrix, size_t n, size_t m) {
        int row = matrix.size(); int col = matrix[0].size();
        Matrix result{zeros(row-1, col-1)};
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (i < n && j < m) {
                    result[i][j] = matrix[i][j];
                } else if (i > n && j < m) {
                    result[i-1][j] = matrix[i][j];
                } else if (i < n && j > m) {
                    result[i][j-1] = matrix[i][j];
                } else if (i > n && j > m) {
                    result[i-1][j-1] = matrix[i][j];
                }
            }
        }
        return result;
    }

    double determinant(const Matrix& matrix) {
        if (matrix.empty()) return 1;
        if (matrix[0].empty()) return 1;
        int row = matrix.size(); int col = matrix[0].size();
        if (row != col) throw std::logic_error("non-square matrices have no determinant");
        if (row == 1 && col == 1) return matrix[0][0];
        double det = 0.0;
        for (int j = 0; j < col; j++) {
            det += pow(-1, j)*matrix[0][j]*determinant(minor(matrix, 0, j));
        }
        return det;
    }

    Matrix adj(const Matrix& matrix) {
        if (matrix.empty()) return {};
        if (matrix.size() != matrix[0].size()) throw std::logic_error("non-square matrices have no adj Matrix");
        int row = matrix.size(); int col = matrix[0].size();
        if (row != col) throw std::logic_error("non-square matrices have no adj Matrix");
        if (row == 1 && col == 1) return matrix;
        Matrix result{zeros(row, col)};
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                result[i][j] = pow(-1, (i+j)) * determinant(minor(matrix, i, j));
            }
        }
        return transpose(result);
    }

    Matrix inverse(const Matrix& matrix){
        if (matrix.empty()) return {};
        if (matrix.size() != matrix[0].size()) throw std::logic_error("non-square matrices have no inverse");
        if (determinant(matrix) == 0) throw std::logic_error("singular matrices have no inverse");
        return multiply(adj(matrix), 1 / determinant(matrix));
    }

    Matrix concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis) {
        int row1 = matrix1.size(); int col1 = matrix1[0].size();
        int row2 = matrix2.size(); int col2 = matrix2[0].size();
        if (axis == 0) {
            if (col1 != col2) throw std::logic_error("matrices with wrong dimensions cannot be concatenated");
            Matrix result{zeros(row1 + row2, col1)};
            for (int i = 0; i < row1 + row2; i++) {
                for (int j = 0; j < col1; j++) {
                    if (i < row1) {
                        result[i][j] = matrix1[i][j];
                    } else {
                        result[i][j] = matrix2[i-row1][j];
                    }
                }
            }
            return result;
        } else if (axis == 1) {
            if (row1 != row2) throw std::logic_error("matrices with wrong dimensions cannot be concatenated");
            Matrix result{zeros(row1, col1+col2)};
            for (int i = 0; i < row1; i++) {
                for (int j = 0; j < col1 + col2; j++) {
                    if (j < col1) {
                        result[i][j] = matrix1[i][j];
                    } else {
                        result[i][j] = matrix2[i][j-col1];
                    }
                }
            }
            return result;
        } else {
            throw std::logic_error("the axis argument can only be 0 or 1");
        }
    }

    Matrix ero_swap(const Matrix& matrix, size_t r1, size_t r2) {
        if (r1 >= matrix.size() || r2 >= matrix.size()) throw std::logic_error("r1 or r2 inputs are out of range");
        Matrix result{matrix};
        std::swap(result[r1], result[r2]);
        return result;
    }

    Matrix ero_multiply(const Matrix& matrix, size_t r, double c) {
        Matrix result{matrix};
        for (int j = 0; j < matrix[0].size(); j++) {
            result[r][j] *= c;
        }
        return result;
    }

    Matrix ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2) {
        Matrix result{matrix};
        for (int j = 0; j < matrix[0].size(); j++) {
            result[r2][j] += result[r1][j]*c;
        }
        return result;
    }

    Matrix upper_triangular(const Matrix& matrix) {
        if (matrix.empty()) return {};
        if (matrix.size() != matrix[0].size()) throw std::logic_error("non-square matrices have no upper triangular form");
        Matrix result{matrix};
        int size = matrix.size();
        for (int k = 0; k < size; k++) {  // k 是对角线上主元index
            bool iszero = (result[k][k] == 0) ? true : false;
            if (iszero) {
                for (int i = k + 1; i < size; i++) {
                    if (result[i][k] != 0) {
                        result = ero_swap(result, k, i);
                        break;
                    }
                }
            }
            for (int i = k+1; i < size; i++) {
                double scale = - (result[i][k]/result[k][k]);
                result = ero_sum(result, k, scale, i);
            }
        }
        return result;
    }
}
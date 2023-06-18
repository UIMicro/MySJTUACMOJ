#include <iostream>
#include "matrix.h"

using sjtu::Matrix;

template <typename T>
void printMatrix(const Matrix<T>& m) {
    std::cout << "[ ";
    for (int i = 1; i <= m.height(); ++i) {
        for (int j = 1; j <= m.width(); ++j) {
            std::cout << m(i, j);
            if (j != m.width()) std::cout << " ";
        }
        if (i != m.height()) std::cout << " ; ";
    }
    std::cout << " ]" << std::endl;
}

int main() {
    std::cout << "testcase 1" << std::endl;
    int seq[4] = { 1, 2, 3, 4 };
    Matrix<int> a(2, 2, seq);
    Matrix<int> b(1, 2);
    printMatrix(a);
    printMatrix(b);
    std::cout << std::endl;

    std::cout << "testcase 2" << std::endl;
    Matrix<int> c(a);
    printMatrix(c);
    std::cout << std::endl;

    std::cout << "testcase 3" << std::endl;
    b = b;
    c = b;
    printMatrix(b);
    printMatrix(c);
    std::cout << std::endl;

    Matrix<int> tmp1(a);
    const Matrix<int> tmp2(a);

    std::cout << "testcase 4" << std::endl;
    tmp1(2, 2) = 1;
    std::cout << tmp2(1, 2) << std::endl;
    printMatrix(tmp1);
    std::cout << std::endl;

    Matrix<int> tmp3(1, 4, seq);
    Matrix<int> tmp4(4, 1, seq);

    std::cout << "testcase 5" << std::endl;
    printMatrix(tmp3 + tmp3);
    printMatrix(tmp3 + tmp4);
    std::cout << std::endl;

    std::cout << "testcase 6" << std::endl;
    printMatrix(a * a);
    printMatrix(tmp3 * tmp4);
    std::cout << std::endl;

    std::cout << "testcase 7" << std::endl;
    try {
        Matrix<int> tmp = a * b;
    }
    catch (sjtu::MatrixSizeError& e) {
        std::cout << e.what() << std::endl;
    }
    catch (...) {
        std::cout << "unexpected error" << std::endl;
    }

    try {
        Matrix<int> tmp = tmp3 + tmp4;
    }
    catch (sjtu::MatrixSizeError& e) {
        std::cout << e.what() << std::endl;
    }
    catch (...) {
        std::cout << "unexpected error" << std::endl;
    }

    try {
        int tmp = a(0, 2);
    }
    catch (sjtu::MatrixIndexingError& e) {
        std::cout << e.what() << std::endl;
    }
    catch (...) {
        std::cout << "unexpected error" << std::endl;
    }

    return 0;
}

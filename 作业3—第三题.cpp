#include <iostream>
using namespace std;

struct ColNode {
    int col;//列索引
    int value;
    ColNode* nextCol;//指向下一个列节点
    ColNode(int c, int v) : col(c), value(v), nextCol(nullptr) {}
};

struct RowNode {
    int row;//行索引
    ColNode* colHead;//指向列链表头节点
    RowNode* nextRow;//下一个行节点
    RowNode(int r) : row(r), colHead(nullptr), nextRow(nullptr) {}
};

class linkedMatrix {
private:
    int rows, cols;
    RowNode* rowHead;//指向行链表头节点

public:
    linkedMatrix(int r, int c) : rows(r), cols(c), rowHead(nullptr) {}

    void insert(int row, int col, int value) {
        //if (value == 0) return;

        RowNode* currentRow = rowHead;//行链表头
        while (currentRow && currentRow->row != row) {
            currentRow = currentRow->nextRow;
        }//找指定行节点

        if (!currentRow) {//如果当前没有对应行节点
            RowNode* newRow = new RowNode(row);//新建
            newRow->nextRow = rowHead;//插入行链表头
            rowHead = newRow;
            currentRow = newRow;//当前行节点为新行
        }

        ColNode* currentCol = currentRow->colHead;//找该行中对应列
        while (currentCol && currentCol->col != col) {
            currentCol = currentCol->nextCol;
        }

        if (!currentCol) {//没找到
            ColNode* newCol = new ColNode(col, value);//创建新列
            newCol->nextCol = currentRow->colHead;//新列节点插入列链表头
            currentRow->colHead = newCol;
        } else {
            currentCol->value = value;//找到
        }
    }

    int get(int row, int col) const {
        RowNode* currentRow = rowHead;
        while (currentRow && currentRow->row != row) {
            currentRow = currentRow->nextRow;
        }

        if (!currentRow) return 0;

        ColNode* currentCol = currentRow->colHead;
        while (currentCol && currentCol->col != col) {
            currentCol = currentCol->nextCol;
        }

        return currentCol->value;
    }

    linkedMatrix operator+(const linkedMatrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw invalid_argument("Matrix dimensions must match for addition.");
        }//行列数不同异常

        linkedMatrix res(rows, cols);
        RowNode* currentRow = rowHead;
        while (currentRow) {
            ColNode* currentCol = currentRow->colHead;
            while (currentCol) {
                res.insert(currentRow->row, currentCol->col, currentCol->value);
                currentCol = currentCol->nextCol;
            }
            currentRow = currentRow->nextRow;
        }

        currentRow = other.rowHead;
        while (currentRow) {
            ColNode* currentCol = currentRow->colHead;
            while (currentCol) {
                int value = res.get(currentRow->row, currentCol->col) + currentCol->value;
                res.insert(currentRow->row, currentCol->col, value);
                currentCol = currentCol->nextCol;
            }
            currentRow = currentRow->nextRow;
        }

        return res;
    }

    linkedMatrix operator-(const linkedMatrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw invalid_argument("Matrix dimensions must match for subtraction.");
        }//

        linkedMatrix res(rows, cols);
        RowNode* currentRow = rowHead;
        while (currentRow) {
            ColNode* currentCol = currentRow->colHead;
            while (currentCol) {
                res.insert(currentRow->row, currentCol->col, currentCol->value);
                currentCol = currentCol->nextCol;
            }
            currentRow = currentRow->nextRow;
        }

        currentRow = other.rowHead;
        while (currentRow) {
            ColNode* currentCol = currentRow->colHead;
            while (currentCol) {
                int value = res.get(currentRow->row, currentCol->col) - currentCol->value;
                res.insert(currentRow->row, currentCol->col, value);
                currentCol = currentCol->nextCol;
            }
            currentRow = currentRow->nextRow;
        }

        return res;
    }

    linkedMatrix operator*(const linkedMatrix& other) const {
        if (cols != other.rows) {
            throw invalid_argument("Matrix dimensions do not match for multiplication.");
        }//

        linkedMatrix res(rows, other.cols);
        RowNode* currentRow = rowHead;
        while (currentRow) {
            ColNode* currentCol = currentRow->colHead;
            while (currentCol) {
                RowNode* otherRow = other.rowHead;
                while (otherRow && otherRow->row != currentCol->col) {
                    otherRow = otherRow->nextRow;
                }

                if (otherRow) {
                    ColNode* otherCol = otherRow->colHead;
                    while (otherCol) {
                        int value = res.get(currentRow->row, otherCol->col) + currentCol->value * otherCol->value;
                        res.insert(currentRow->row, otherCol->col, value);
                        otherCol = otherCol->nextCol;
                    }
                }

                currentCol = currentCol->nextCol;
            }
            currentRow = currentRow->nextRow;
        }

        return res;
    }

    friend ostream& operator<<(ostream& out, const linkedMatrix& matrix) {
        RowNode* currentRow = matrix.rowHead;
        out << "Non-zero elements in matrix:" << endl;
        while (currentRow) {
            ColNode* currentCol = currentRow->colHead;
            while (currentCol) {
                out << "a(" << currentRow->row << ", " << currentCol->col << ") = " << currentCol->value << endl;
                currentCol = currentCol->nextCol;
            }
            currentRow = currentRow->nextRow;
        }
        return out;
    }

    friend istream& operator>>(istream& in, linkedMatrix& matrix) {
        int terms;
        cout << "non-zero terms:";
        in >> terms;
        cout << "row,col,value:" << endl;

        for (int i = 0; i < terms; ++i) {
            int row, col, value;
            in >> row >> col >> value;
            matrix.insert(row, col, value);
        }
        return in;
    }

    ~linkedMatrix() {
        RowNode* currentRow = rowHead;
        while (currentRow) {
            ColNode* currentCol = currentRow->colHead;
            while (currentCol) {
                ColNode* tempCol = currentCol;
                currentCol = currentCol->nextCol;
                delete tempCol;
            }
            RowNode* tempRow = currentRow;
            currentRow = currentRow->nextRow;
            delete tempRow;
        }
    }
};

int main() {
    int n1=2, n2=2, m1=2, m2=2;
    
    
    linkedMatrix matrix1(n1, m1), matrix2(n2, m2);
    cout << "Enter values for matrix 1:" << endl;
    cin >> matrix1;
    cout << "Enter values for matrix 2:" << endl;
    cin >> matrix2;

    cout << "Matrix 1:" << endl << matrix1;
    cout << "Matrix 2:" << endl << matrix2;

    cout << "+:" << endl << (matrix1 + matrix2);
    cout << "-:" << endl << (matrix1 - matrix2);
    cout << "*:" << endl << (matrix1 * matrix2);

    return 0;
}

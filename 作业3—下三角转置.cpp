#include<iostream>
using namespace std;
class matrix {
public:
	int row;
	int col;
	int* element;
	matrix(int n, int a[]) {
		row = n;
		col = n;
		element = new int[(row * row + row) / 2];
		for (int i = 0; i < (row * row + row) / 2; i++) {
			element[i] = a[i];
		}

	}
	int oindex(int i, int j) {
		return (i * (i + 1) / 2) + j;
	}
	int tindex(int i, int j) {
		return(((2 * row) - i + 1) * i / 2) + j - i;
	}

	void transpose() {
		int* t = new int[(row * row + row) / 2];
		for (int i = 0; i < row; i++) {
			for (int j = 0; j <= i; j++) {
				t[tindex(j, i)] = element[oindex(i, j)];
			}
		}
		for (int i = 0; i < (row * row + row) / 2; i++) {
			cout << t[i] << ' ';
		}
		delete[]t;
	}
	~matrix() {
		delete[]element;
	}
};



int main() {
	int b[6] = { 1,2,3,4,5,6 };
	matrix t(3, b);
	t.transpose();

	return 0;
}
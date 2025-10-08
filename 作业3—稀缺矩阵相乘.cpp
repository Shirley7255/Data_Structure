#include<iostream>
#include<vector>
using namespace std;
struct tri{
	int r;
	int c;
	int value;
};
class matrix {
public:
	int row;
	int col;
	vector < tri > element;
	matrix(int m, int n) {
		row = m;
		col = n;
	}
	void insert(int m, int n, int x) {
		element.push_back({ m,n,x });
	}
	matrix mul(matrix& B) {
		matrix C(row,B.col);
		
		for (int i = 0; i < element.size(); i++) {
			tri a = element[i];
			for (int j = 0; j < B.element.size(); j++) {
				tri b = B.element[j];//行号列号相等
				if (a.c== b.r) {//一个个对上后相乘
					int cr = a.r;
					int cc = b.c;
					int cv = a.value*b.value;

					bool found = false;
					for (int k = 0; k < C.element.size(); k++) {
						if (C.element[k].r == cr && C.element[k].c == cc) {
							C.element[k].value += cv;//加进结果矩阵的空里
							found = true;
							break;
						}
					}
					if (!found) {
						C.insert(cr, cc, cv);
					}

				}
			}
		}
		return C;

	}
	void print() {
		for (int i = 0; i < element.size(); i++) {
			cout << element[i].r << ' ' << element[i].c << ' ' << element[i].value << endl;
		}
	}
};
int main() {
	/*
	0 0 2
	0 1 0
	0 0 1
	2 0 0

	1 0
	0 0
	0 2

	0 4
	0 0
	0 2
	2 0
	
	*/
	matrix a(4, 3);
	a.insert(0, 2, 2);
	a.insert(1, 1, 1);
	a.insert(2, 2, 1);
	a.insert(3, 0, 2);
	matrix b(3, 2);
	b.insert(0, 0, 1);
	b.insert(2, 1, 2);
	a.mul(b).print();
	


	return 0;
}
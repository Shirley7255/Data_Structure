#include<iostream>
using namespace std;
int main() {
	int a[7] = { 26,33,35,29,19,12,22 };
	int r[7] = { 0 };
	for (int i = 0; i <=5; i++) {//ÿ�ֱ�����
		for (int j = i+1; j <=6; j++) {//ÿ�αȵ���
			if (a[j] <=a[i]) {
				r[i]++;
			}
			else { r[j]++; }
		}
	}
	for (int i = 0; i <7; i++) {
		cout << r[i] << ' ';
			 
	}


	return 0;
}

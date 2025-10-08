#include<iostream>
using namespace std;
void subset(int n, int* B, int cur)
{
    if (cur == n + 1)//最高位占满
    {
        for (int i = 1; i <= n; i++)
        {
            if (B[i]) {
                cout << char('a' + i - 1);
            }
        }
        cout << endl;
        return;
    }
    B[cur] = 1;
    subset(n, B, cur + 1);
    B[cur] = 0;
    subset(n, B, cur + 1);
}





int main() {
	int n;
    int b[26];
	cin >> n;
	if (n < 1 || n>26) {
		cout << "WRONG";
	}
	else {
        subset(n, b, 1);
	}



	return 0;
}
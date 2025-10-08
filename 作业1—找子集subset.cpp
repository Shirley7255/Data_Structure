#include <iostream>


using namespace std;
void subset(int n, int index,bool b[]){
    if (index == n) {
        for (int i = 0; i < n; i++) {
            if (b[i] == true) {
                cout << char('a' + i)<<' ';
            }
        }
        cout << endl;
        return;
    }
    
    b[index] = true;
    subset(n, index+1, b);
    b[index] = false;
    subset(n, index+1, b);
}



int main() {
    
    int n;
    cin >> n;

    if (n < 1 || n > 26) {
        cout << "WRONG" << endl;
        return 0;
    }
    else {
        int index = 0;
        bool b[26];
        subset(n, index, b);
    }
    

    return 0;
}
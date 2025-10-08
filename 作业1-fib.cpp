

#include <iostream>
using namespace std;

long long f[91];  

void first() {
   
    for (int i = 0; i <= 90; i++) {
        f[i] = -1;
    }
    f[0] = 0;  
    f[1] = 1;  
}

long long fib(int n) {
   
    if (f[n] != -1) {
        return f[n];
    }
    else {
        f[n] = fib(n - 1) + fib(n - 2);
        return f[n];
    }

    
    
}

int main() {
    
    int n;
    cin >> n;

    
    if (n < 0 || n > 90) {
        cout << "WRONG" << endl << ' ';  
    }
    else {
        first();  
        cout << fib(n) << endl << ' ';   
    }

    return 0;
}


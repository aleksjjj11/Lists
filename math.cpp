#include <iostream>
#include <string>

using namespace std;

void foo(int a, int b, int c, int n){
    if (n <= 0) return;
    foo(a,c,b,n-1);
    cout << a << "->" << b << endl;
    foo(c,b,a,n-1);
}

int main(){
    int a = 1,b = 2;
    cin >> a >> b;
    int n ;
    cin >> n;
    foo(a,b,6-a-b,n);
    return 0;
}
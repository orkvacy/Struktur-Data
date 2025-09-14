#include <iostream>
using namespace std;

int tukarData(int& a, int& b) {
    int var = a;
    a = b;
    b = var;
    return 0; 
}

int main() {
    int a, b;
    cout << "Masukkan angka pertama\t: ";
    cin >> a;
    cout << "Masukkan angka kedua\t: ";
    cin >> b;

    cout << "Sebelum: a = " << a << " b = " << b << endl;
    int swap = tukarData(a, b);
    cout << "Sesudah: a = " << a << " b = " << b;
}

#include <iostream>
using namespace std;

void tukarData(int& a, int& b) {
    int var = a;
    a = b;
    b = var;
}

int main() {
    int a, b;
    cout << "Masukkan angka pertama\t: ";
    cin >> a;
    cout << "Masukkan angka kedua\t: ";
    cin >> b;

    cout << "Sebelum: a = " << a << " b = " << b << endl;
    tukarData(a, b);
    cout << "Sesudah: a = " << a << " b = " << b;
}

#include <iostream>
using namespace std;

bool valPrima(int x) {
    if (x < 2) return false;
    if (x == 2) return true;        // Langsung return true untuk 2
    if (x % 2 == 0) return false;   // Eliminasi bilangan genap > 2
    for (int i = 3; i * i <= x; i += 2) {  // Hanya cek bilangan ganjil
        if (x % i == 0) return false;
    }
    return true;
}
//balik arr
void swapArr(int *arr, int x) {
    int *awal = arr;
    int *akhir = arr + x - 1;

    while (awal < akhir) {
        int swap = *awal;
        *awal = *akhir;
        *akhir = swap;
        awal++;
        akhir--;
    }
}

int main() {
    int arr[7];
    int valid = 0, angka = 2; 

    while (valid < 7) {
        if (valPrima(angka)) {
            arr[valid] = angka; //isi kalau prima doang
            valid++;
        }
        angka++;
    }

    //sebelum
    cout << "Array awal\t: " << endl;
    for (int i = 0; i < 7; i++) {
        cout << arr[i] << " ";
    }

    
    //habis di swap
    swapArr(arr, 7);
    cout << "\nBalik array\t: " << endl;
    for (int i = 0; i < 7; i++) {
        cout << arr[i] << " ";
    }

    return 0;
}

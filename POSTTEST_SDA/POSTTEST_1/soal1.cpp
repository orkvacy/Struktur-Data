#include <iostream>
#include <tabulate/table.hpp>
using namespace std;
using namespace tabulate;

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

int main() 
{
    int arr[7];
    int arrAwal[7];
    int valid = 0, angka = 2; 

    while (valid < 7) {
        if (valPrima(angka)) {
            arr[valid] = angka; //isi kalau prima doang
            arrAwal[valid] = angka; 
            valid++;
        }
        angka++;
    }
    swapArr(arr, 7);
    Table t;
    string rowAwal[8];
    rowAwal[0] = "Array awal";
    for (int i = 0; i < 7; i++)
        rowAwal[i + 1] = to_string(arrAwal[i]);
    t.add_row({rowAwal, rowAwal + 8});

    string rowBalik[8];
    rowBalik[0] = "Balik array";
    for (int i = 0; i < 7; i++)
        rowBalik[i + 1] = to_string(arr[i]);
    t.add_row({rowBalik, rowBalik + 8});
    t[0][0].format().font_color(Color::red);
    t[1][0].format().font_color(Color::red);
    cout << t << endl;
    return 0;
}




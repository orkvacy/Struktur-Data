#include <iostream>
#include <tabulate/table.hpp>
using namespace tabulate;
using namespace std;

int main() {
    int matriks[3][3];
    cout << "Input elemen matrix (3x3)" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << "Elemen [" << i+1 << "][" << j+1 << "]: ";
            cin >> matriks[i][j];
        }
    }
    cout << "================================" << endl;
    Table t;
    cout << "Matrix 3x3" << endl;
    for (int i = 0; i<3; i++){
        t.add_row
        ({
            to_string(matriks[i][0]),
            to_string(matriks[i][1]),
            to_string(matriks[i][2])
        });
    }
    cout << t << endl;
    

    int hasil = 0;
    for (int j=0; j<3; j++) {
        hasil += matriks[1][j];  
    }

    cout << "\nJumlah elemen di baris genap\t: " << hasil << endl;

    return 0;
}

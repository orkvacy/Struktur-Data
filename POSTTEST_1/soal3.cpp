#include <iostream>
#include <limits>
using namespace std;

struct mahasiswa {
    string nama;
    char nim[14];
    double ipk;
};

void bubbleSort(mahasiswa mhs[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (n - i - 1); j++) {
            if (mhs[j].ipk > mhs[j + 1].ipk) {
                mahasiswa temp = mhs[j];
                mhs[j] = mhs[j + 1];
                mhs[j + 1] = temp;
            }
        }
    }
}


int main() {
    int len = 4; 
    mahasiswa mhs[len];

    cout << "Input Data mahasiswa" << endl;
    for (int i = 0; i < len; i++) {
        cout << "mahasiswa ke-" << i+1 << endl;
        cout << "Nama : ";
        getline(cin, mhs[i].nama);
        cout << "NIM  : ";
        cin.getline(mhs[i].nim, 14);
        cout << "IPK  : ";
        cin >> mhs[i].ipk;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl;
    }

    bubbleSort(mhs, len);

    cout << "Data Mahasiswa berdasarkan IPK (asc)" << endl;
    for (int i = 0; i < len; i++) {
        cout << "mahasiswa " << i+1 << endl;
        cout << "Nama\t: " << mhs[i].nama << endl;
        cout << "NIM\t: " << mhs[i].nim << endl;
        cout << "IPK\t: " << mhs[i].ipk << endl;
        cout << endl;
    }

    return 0;
}

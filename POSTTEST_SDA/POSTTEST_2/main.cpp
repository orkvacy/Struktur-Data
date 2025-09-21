#include <iostream>
#include <tabulate/table.hpp>
#include <limits>

using namespace std;
using namespace tabulate;

struct jadwalPenerbangan {
    string kodePenerbangan;
    string tujuan;
    string status;
    jadwalPenerbangan *next;
};

jadwalPenerbangan *head = nullptr;
int pkCode = 0;

string buatKodePenerbangan() {
    if (pkCode == 0) {
        pkCode++;
        return "JT-046";
    }
    string kode = "JT-046-" + to_string(pkCode);
    pkCode++;
    return kode;
}

void delayInput() {
    cout << "Tekan Enter untuk kembali ke menu :D" << endl;
    cin.ignore(numeric_limits<streamsize>::max());
}

void showJadwal(){
    system("cls");
    cout << "\tJadwal Penerbangan\n";

    if (head == nullptr) {
        cout << "Belum ada jadwal penerbangan yang ditambahkan." << endl;
        return;
    }
    Table jadwalTable;
    jadwalTable.add_row({"No.", "Kode Penerbangan", "Tujuan", "Status"});

    jadwalPenerbangan *temp = head;
    int no = 1;
    while (temp != nullptr) {
        jadwalTable.add_row({to_string(no++), temp->kodePenerbangan, temp->tujuan, temp->status});
        temp = temp->next;
    }

    cout << jadwalTable << endl;

}

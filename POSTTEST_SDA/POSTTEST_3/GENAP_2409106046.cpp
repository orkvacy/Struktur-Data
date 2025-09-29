#include <iostream>
#include <limits>
#include <string>
#include <tabulate/table.hpp>

using namespace std;
using namespace tabulate;


struct jadwalPenerbangan {
    string kodePenerbangan;
    string tujuan;
    string status;
    jadwalPenerbangan *next;
    jadwalPenerbangan *prev; 
};

jadwalPenerbangan *head = nullptr;
jadwalPenerbangan *tail = nullptr; 

string buatKodePenerbangan() {
    int i = 0;
    while (true) {
        string kodeTemp;
        if (i == 0) {
            kodeTemp = "JT-046";
        } else {
            kodeTemp = "JT-046-" + to_string(i);
        }

        bool ditemukan = false;
        jadwalPenerbangan *temp = head;
        while (temp != nullptr) {
            if (temp->kodePenerbangan == kodeTemp) {
                ditemukan = true;
                break;
            }
            temp = temp->next;
        }

        if (!ditemukan) {
            return kodeTemp;
        }
        i++;
    }
}

void delayOutput() {
    cout << "Tekan Enter untuk kembali...";
    cin.get();
}

string pilihStatus() {
    int pilihan;
    Table menuStatus;
    menuStatus.add_row({"Pilih Status Penerbangan"});
    menuStatus.add_row({"1. Tepat Waktu"});
    menuStatus.add_row({"2. Delay"});
    menuStatus.add_row({"3. Dibatalkan"}); 
    cout << menuStatus << endl;
    cout << "Pilih Opsi: ";

    while (!(cin >> pilihan) || pilihan < 1 || pilihan > 3) {
        cout << "Pilihan tidak valid, mohon masukkan antara 1-3: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (pilihan) {
        case 1: return "Tepat Waktu";
        case 2: return "Delay";
        case 3: return "Dibatalkan";
        default: return "";
    }
}


void showJadwal() {
    system("cls");
    cout << "+---------------------------------------+" << endl;
    cout << "|     Semua Jadwal (Dari Depan)         |" << endl;
    cout << "+---------------------------------------+" << endl;

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

    jadwalTable.column(0).format().width(5).font_align(FontAlign::center);
    jadwalTable.column(1).format().width(20).font_align(FontAlign::center);
    jadwalTable.column(2).format().width(25);
    jadwalTable.column(3).format().width(20);
    for (size_t i = 0; i < 4; ++i) {
        jadwalTable[0][i].format().font_color(Color::yellow).font_style({FontStyle::bold});
    }
    cout << jadwalTable << endl;
}

//point 3. reverse list
void showJadwalDariBelakang() {
    system("cls");
    cout << "+---------------------------------------+" << endl;
    cout << "|     Semua Jadwal (Dari Belakang)      |" << endl;
    cout << "+---------------------------------------+" << endl;

    if (tail == nullptr) {
        cout << "Belum ada jadwal penerbangan yang ditambahkan." << endl;
        return;
    }
    Table jadwalTable;
    jadwalTable.add_row({"No.", "Kode Penerbangan", "Tujuan", "Status"});

    jadwalPenerbangan *temp = tail; 
    int no = 1;
    while (temp != nullptr) {
        jadwalTable.add_row({to_string(no++), temp->kodePenerbangan, temp->tujuan, temp->status});
        temp = temp->prev; 
    }

    jadwalTable.column(0).format().width(5).font_align(FontAlign::center);
    jadwalTable.column(1).format().width(20).font_align(FontAlign::center);
    jadwalTable.column(2).format().width(25);
    jadwalTable.column(3).format().width(20);
    for (size_t i = 0; i < 4; ++i) {
        jadwalTable[0][i].format().font_color(Color::yellow).font_style({FontStyle::bold});
    }
    cout << jadwalTable << endl;
}

//point 4. search berdasarkan id
void showDetailJadwal() {
    system("cls");
    if (head == nullptr) {
        cout << "Jadwal kosong, tidak ada data untuk ditampilkan." << endl;
        return;
    }

    cout << "Masukkan Kode Penerbangan yang ingin dilihat detailnya: ";
    string kodeCari;
    getline(cin, kodeCari);

    jadwalPenerbangan *temp = head;
    bool ditemukan = false;
    while (temp != nullptr) {
        if (temp->kodePenerbangan == kodeCari) {
            ditemukan = true;
            break;
        }
        temp = temp->next;
    }

    if (ditemukan) {
        cout << "\n>> Detail Jadwal Ditemukan <<\n";
        Table detailTable;
        detailTable.add_row({"Atribut", "Nilai"});
        detailTable.add_row({"Kode Penerbangan", temp->kodePenerbangan});
        detailTable.add_row({"Tujuan", temp->tujuan});
        detailTable.add_row({"Status", temp->status});
        
        detailTable.column(0).format().font_style({FontStyle::bold});
        cout << detailTable << endl;
    } else {
        cout << "\nJadwal dengan kode '" << kodeCari << "' tidak ditemukan." << endl;
    }
}


jadwalPenerbangan* buatNodeBaru() {
    jadwalPenerbangan *nodeBaru = new jadwalPenerbangan;
    nodeBaru->kodePenerbangan = buatKodePenerbangan();
    cout << "Masukkan Tujuan Penerbangan\t: ";
    getline(cin, nodeBaru->tujuan);
    nodeBaru->status = pilihStatus();
    nodeBaru->next = nullptr;
    nodeBaru->prev = nullptr; //point 2. ubah ke double linked list
    return nodeBaru;
}

void tambahJadwalAwal() {
    jadwalPenerbangan* nodeBaru = buatNodeBaru();
    if (head == nullptr) {
        head = tail = nodeBaru;
    } else {
        nodeBaru->next = head;
        head->prev = nodeBaru;
        head = nodeBaru;
    }
    cout << "Jadwal dengan kode " << nodeBaru->kodePenerbangan << " berhasil ditambahkan di awal" << endl;
}

void tambahJadwalAkhir() {
    jadwalPenerbangan *nodeBaru = buatNodeBaru();
    if (head == nullptr) {
        head = tail = nodeBaru;
    } else {
        tail->next = nodeBaru;
        nodeBaru->prev = tail;
        tail = nodeBaru;
    }
    cout << "Jadwal dengan kode " << nodeBaru->kodePenerbangan << " berhasil ditambahkan di akhir" << endl;
}

void sisipkanJadwal() {
    if (head == nullptr) {
        cout << "Daftar masih kosong. Data akan ditambahkan di awal." << endl;
        tambahJadwalAwal();
        return;
    }

    showJadwal();
    cout << "Masukkan posisi untuk menyisipkan jadwal: ";
    int posisi;
    cin >> posisi;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (cin.fail() || posisi < 1) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << ">> Posisi tidak valid." << endl;
        return;
    }

    if (posisi == 1) {
        tambahJadwalAwal();
        return;
    }

    jadwalPenerbangan *temp = head;
    int hitung = 1;
    while (temp != nullptr && hitung < posisi - 1) {
        temp = temp->next;
        hitung++;
    }

    if (temp == nullptr || temp == tail) {
        cout << "Posisi sisip melebihi jumlah jadwal. Data akan ditambahkan di akhir." << endl;
        tambahJadwalAkhir();
    } else {
        jadwalPenerbangan *nodeBaru = buatNodeBaru();
        nodeBaru->next = temp->next;
        nodeBaru->prev = temp;
        if (temp->next != nullptr) {
            temp->next->prev = nodeBaru;
        }
        temp->next = nodeBaru;
        cout << "Jadwal berhasil disisipkan pada posisi ke-" << posisi << endl;
    }
}

void hapusJadwalAwal() {
    if (head == nullptr) {
        cout << "LinkedList masih kosong" << endl;
        return;
    }
    jadwalPenerbangan *temp = head;
    string kodeHapus = temp->kodePenerbangan;
    if (head == tail) {
        head = tail = nullptr;
    } else {
        head = head->next;
        head->prev = nullptr;
    }
    delete temp;
    cout << "Jadwal paling awal (" << kodeHapus << ") berhasil dihapus" << endl;
}

void hapusJadwalAkhir() {
    if (head == nullptr) {
        cout << "LinkedList masih kosong." << endl;
        return;
    }
    string kodeHapus = tail->kodePenerbangan;
    jadwalPenerbangan *temp = tail;
    if (head == tail) {
        head = tail = nullptr;
    } else {
        tail = tail->prev;
        tail->next = nullptr;
    }
    delete temp;
    cout << "Jadwal terakhir (" << kodeHapus << ") berhasil dihapus" << endl;
}

void updateStatus() {
    showJadwal();
    if (head == nullptr) {
        cout << "Belum ada jadwal untuk diupdate." << endl;
        return;
    }
    string kodeCari;
    cout << "Masukkan Kode Penerbangan yang akan diupdate: ";
    getline(cin, kodeCari);
    jadwalPenerbangan *temp = head;
    bool ditemukan = false;
    while (temp != nullptr) {
        if (temp->kodePenerbangan == kodeCari) {
            ditemukan = true;
            cout << "Jadwal ditemukan! Status saat ini: " << temp->status << endl;
            temp->status = pilihStatus();
            cout << "Status berhasil diupdate" << endl;
            break;
        }
        temp = temp->next;
    }
    if (!ditemukan) {
        cout << "Jadwal dengan kode " << kodeCari << " tidak ditemukan" << endl;
    }
}

void clearAll() {
    jadwalPenerbangan *current = head;
    jadwalPenerbangan *nextNode;
    while (current != nullptr) {
        nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = tail = nullptr;
}

void menuTambah() {
    int pilihan;
    while (true) {
        system("cls");
        Table subAdd;
        subAdd.add_row({"MENU TAMBAH JADWAL"});
        subAdd.add_row({"1. Tambah di Awal"});
        subAdd.add_row({"2. Tambah di Akhir"});
        subAdd.add_row({"3. Sisipkan di Posisi Tertentu"});
        subAdd.add_row({"0. Kembali ke Menu Utama"});
        
        subAdd[0].format().font_color(Color::cyan);
        cout << subAdd << endl;
        cout << "Pilih Opsi: ";
        cin >> pilihan;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pilihan = -1;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        switch (pilihan) {
            case 1: tambahJadwalAwal(); delayOutput(); break;
            case 2: tambahJadwalAkhir(); delayOutput(); break;
            case 3: sisipkanJadwal(); delayOutput(); break;
            case 0: return;
            default: cout << "\nPilihan tidak valid." << endl; delayOutput(); break;
        }
    }
}

int main() {
    int pilihan;
    while (true) {
        system("cls");
        Table mainMenu;
        mainMenu.add_row({"DOUBLE LINKED LIST - FLIGHT SCHEDULE"});
        mainMenu.add_row({"Nabil - 2409106046"});
        mainMenu.add_row({"1. Tambah Jadwal"});
        mainMenu.add_row({"2. Tampilkan Jadwal (Depan -> Belakang)"});
        mainMenu.add_row({"3. Tampilkan Jadwal (Belakang -> Depan)"}); 
        mainMenu.add_row({"4. Tampilkan Detail Jadwal by Kode"}); 
        mainMenu.add_row({"5. Update Status Penerbangan"});
        mainMenu.add_row({"6. Hapus Jadwal Paling Awal"});
        mainMenu.add_row({"7. Hapus Jadwal Paling Akhir"});
        mainMenu.add_row({"0. Keluar"});

        mainMenu[0].format().font_color(Color::red);
        cout << mainMenu << endl;
        cout << "Pilih Opsi: ";
        cin >> pilihan;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pilihan = -1;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (pilihan)
        {
            case 1:
                menuTambah();
                break;
            case 2:
                showJadwal();
                delayOutput();
                break;
            case 3: 
                showJadwalDariBelakang();
                delayOutput();
                break; 
            case 4:
                showDetailJadwal();
                delayOutput(); 
                break; 
            case 5: 
                updateStatus(); 
                delayOutput(); 
                break;
            case 6: 
                hapusJadwalAwal(); 
                delayOutput(); 
                break;
            case 7: 
                hapusJadwalAkhir(); 
                delayOutput(); 
                break;
            case 0: 
                clearAll(); 
                cout << "Selesaiiiiiiiiiiiii" << endl; 
                return 0;
            default: 
                cout << "pilihan ga valid bang" << endl; 
                delayOutput(); 
                break;
        }
    }
    return 0;
}
#include <iostream>
#include <limits>
#include <tabulate/table.hpp>

using namespace std;
using namespace tabulate;

struct jadwalPenerbangan 
{
    string kodePenerbangan;
    string tujuan;
    string status;
    jadwalPenerbangan *next;
};

jadwalPenerbangan *head = nullptr;
int pkCode = 0;

string buatKodePenerbangan() //ga increment doang, bisa isi yg kosong
{
    int i = 0;
    while (true) {
        string kodeTemp;
        if (i == 0) 
        {
            kodeTemp = "JT-046";
        } else 
        {
            kodeTemp = "JT-046-" + to_string(i);
        }

        bool ditemukan = false;
        jadwalPenerbangan *temp = head;
        while (temp != nullptr) 
        {
            if (temp->kodePenerbangan == kodeTemp) 
            {
                ditemukan = true; 
                break; 
            }
            temp = temp->next;
        }

        if (!ditemukan) 
        {
            return kodeTemp; 
        }
        i++;
    }
}

void delayOutput() 
{
    cout << "Tekan Enter untuk kembali...";
    cin.get();
}

string pilihStatus() {
    int pilihan;
    Table menuStatus;
    menuStatus.add_row({"Pilih Status Penerbangan"});
    menuStatus.add_row({"1. Tepat Waktu"});
    menuStatus.add_row({"2. Delay"});
    menuStatus.add_row({"3. Terlambat"});
    cout << menuStatus << endl;
    cout << "Pilih Opsi: ";

    while (!(cin >> pilihan) || pilihan < 1 || pilihan > 3) {
        cout << "pilihan (1-3) aja bang";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (pilihan) {
        case 1:
            return "Tepat waktu";
        case 2:
            return "Delay";
        case 3:
            return "Terlambat";
        default:
            return "pilih (1-3) aja ya bang";
    }
}

void showJadwal() 
{
    system("cls");
    cout << "+---------------------------------------+" << endl;
    cout << "|           Semua Jadwal                |" << endl;
    cout << "+---------------------------------------+" << endl;

    if (head == nullptr) {
        cout << " Belum ada jadwal penerbangan yang ditambahkan. " << endl;
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
        jadwalTable[0][i].format()
            .font_color(Color::yellow)
            .font_style({FontStyle::bold});
    }
    cout << jadwalTable << endl;
}

jadwalPenerbangan* buatNodeBaru() 
{
    jadwalPenerbangan *nodeBaru = new jadwalPenerbangan;
    nodeBaru->kodePenerbangan = buatKodePenerbangan();
    cout << "Masukkan Tujuan Penerbangan\t: ";
    getline(cin, nodeBaru->tujuan);
    nodeBaru->status = pilihStatus();
    nodeBaru->next = nullptr;
    return nodeBaru;
}

void tambahJadwalAwal() {
    jadwalPenerbangan* nodeBaru = buatNodeBaru();
    nodeBaru->next = head;
    head = nodeBaru;
    cout << "Jadwal dengan kode " << nodeBaru->kodePenerbangan << " berhasil ditambahkan di awal" << endl;
}

void tambahJadwalAkhir() {
    jadwalPenerbangan *nodeBaru = buatNodeBaru();
    if (head == nullptr) 
    {
        head = nodeBaru;
    } else 
    {
        jadwalPenerbangan *temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = nodeBaru;
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

    if (cin.fail() || posisi < 1) 
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << ">> Posisi tidak valid." << endl;
        return;
    }

    if (posisi == 1) 
    {
        tambahJadwalAwal();
        return;
    }

    jadwalPenerbangan *temp = head;
    int hitung = 1;
    while (temp != nullptr && hitung < posisi - 1) 
    {
        temp = temp->next;
        hitung++;
    }

    if (temp == nullptr) 
    {
        cout << "osisi sisip melebihi jumlah jadwal. Data akan ditambahkan di akhir." << endl;
        tambahJadwalAkhir();
    } else 
    {
        jadwalPenerbangan *nodeBaru = buatNodeBaru();
        nodeBaru->next = temp->next;
        temp->next = nodeBaru;
        cout << "Jadwal berhasil disisipkan pada posisi ke-" << posisi << endl;
    }
}

void hapusJadwalAwal() 
{
    if (head == nullptr) 
    {
        cout << "LinkedList masih kosong" << endl;
        return;
    }
    jadwalPenerbangan *temp = head;
    string kodeHapus = temp->kodePenerbangan;
    head = head->next;
    delete temp;
    cout << "Jadwal paling awal (" << kodeHapus << ") berhasil dihapus" << endl;
}

void updateStatus() 
{
    showJadwal();
    if (head == nullptr) 
    {
        cout << "Belum ada jadwal untuk diupdate. " << endl;
        return;
    }
    string kodeCari;
    cout << "Masukkan Kode Penerbangan yang akan diupdate: ";
    getline(cin, kodeCari);
    jadwalPenerbangan *temp = head;
    bool ditemukan = false;
    while (temp != nullptr) 
    {
        if (temp->kodePenerbangan == kodeCari) 
        {
            ditemukan = true;
            cout << "Jadwal ditemukan! Status saat ini: " << temp->status << endl;
            temp->status = pilihStatus();
            cout << "Status berhasil diupdate" << endl;
            break;
        }
        temp = temp->next;
    }
    if (!ditemukan) 
    {
        cout << "Jadwal dengan kode " << kodeCari << " tidak ditemukan" << endl;
    }
}

void hapusJadwalAkhir() 
{
    if (head == nullptr) 
    {
        cout << "LinkedList masih kosong." << endl;
        return;
    }
    if (head->next == nullptr) 
    {
        delete head;
        head = nullptr;
        cout << "Jadwal berhasil dihapus" << endl;
        return;
    }
    jadwalPenerbangan *temp = head;
    while (temp->next->next != nullptr) 
    {
        temp = temp->next;
    }
    string kodeHapus = temp->next->kodePenerbangan;
    delete temp->next;
    temp->next = nullptr;
    cout << "Jadwal terakhir (" << kodeHapus << ") berhasil dihapus" << endl;
}

void sisipkanJadwalByNIM() {
    int posisi = 7; 
    cout << "Menyisipkan jadwal pada posisi " << posisi << " (sesuai aturan NIM)..." << endl;

    if (posisi <= 1 || head == nullptr) {
        cout << "Daftar masih kosong atau posisi di awal. Data akan ditambahkan di awal." << endl;
        tambahJadwalAwal();
        return;
    }

    jadwalPenerbangan *temp = head;
    int hitung = 1;
    while (temp != nullptr && hitung < posisi - 1) {
        temp = temp->next;
        hitung++;
    }

    if (temp == nullptr) {
        cout << ">> Posisi sisip melebihi jumlah jadwal. Data akan ditambahkan di akhir." << endl;
        tambahJadwalAkhir();
    } else {
        jadwalPenerbangan *nodeBaru = buatNodeBaru();
        nodeBaru->next = temp->next;
        temp->next = nodeBaru;
        cout << "\n>> Jadwal berhasil disisipkan pada posisi ke-" << posisi << endl;
    }
}



void clearAll() 
{
    jadwalPenerbangan *current = head;
    jadwalPenerbangan *nextNode;
    while (current != nullptr) 
    {
        nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
}



void menuTambah() 
{
    int pilihan;
    while (true) 
    {
        system("cls");
        Table subAdd;
        subAdd.add_row({"MENU TAMBAH JADWAL"});
        subAdd.add_row({"1. Tambah di Awal"});
        subAdd.add_row({"2. Tambah di Akhir"});
        subAdd.add_row({"3. Sisipkan di Posisi Tertentu"});
        subAdd.add_row({"4. Sisipkan di Posisi 7 (point plus)"});
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
        
        switch (pilihan) 
        {
            case 1:
                tambahJadwalAwal();
                delayOutput();
                break;
            case 2:
                tambahJadwalAkhir();
                delayOutput();
                break;
            case 3:
                sisipkanJadwal();
                delayOutput();
                break;
            case 4:
                sisipkanJadwalByNIM();
                delayOutput();
                break;
            case 0:
                return; 
            default:
                cout << "\nPilihan ga valid bang" << endl;
                delayOutput();
                break;
        }
    }
}



int main() 
{
    int pilihan;
    while (true) 
    {
        system("cls");
        Table mainMenu;
        mainMenu.add_row({"FLIGHT SCHEDULE SYSTEM"});
        mainMenu.add_row({"Nabil - 046"});
        mainMenu.add_row({"1. Menu Tambah Jadwal"}); 
        mainMenu.add_row({"2. Hapus Jadwal Paling Awal"});
        mainMenu.add_row({"3. Update Status Penerbangan"});
        mainMenu.add_row({"4. Tampilkan Semua Jadwal"});
        mainMenu.add_row({"5. Hapus Jadwal Terakhir"});
        mainMenu.add_row({"0. Keluar"});

        mainMenu[0].format().font_color(Color::red);
        cout << mainMenu << endl;
        cout << "Pilih Opsi: ";
        cin >> pilihan;

        if (cin.fail()) 
        {
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
                hapusJadwalAwal();
                delayOutput();
                break;
            case 3:
                updateStatus();
                delayOutput();
                break;
            case 4:
                showJadwal();
                delayOutput();
                break;
            case 5:
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
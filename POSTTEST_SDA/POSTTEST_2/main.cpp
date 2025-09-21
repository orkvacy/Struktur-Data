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

string buatKodePenerbangan() {
    if (pkCode == 0) {
        pkCode++;
        return "JT-046";
    }
    string kode = "JT-046-" + to_string(pkCode);
    pkCode++;
    return kode;
}

jadwalPenerbangan *head = nullptr;
int pkCode = 0;
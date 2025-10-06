#include <iostream>
#include <string>
using namespace std;

struct Node {
    string document;
    Node* next;
};

void enqueue(Node*& front, Node*& rear, string document) {
    Node* newNode = new Node{document, nullptr};

    // --- LENGKAPI DI SINI ---
    // 1. Jika queue kosong, set front dan rear ke newNode
    if (front == nullptr) {
        front = newNode;
        rear = newNode;
    } 
    // 2. Jika tidak kosong, sambungkan rear->next ke newNode, lalu update rear
    else {
        rear->next = newNode;
        rear = newNode;
    }
    // --- LENGKAPI DI SINI ---
}

string dequeue(Node*& front, Node*& rear) {
    if (front == nullptr) return "Antrian kosong"; // Queue kosong

    // --- LENGKAPI DI SINI ---
    // 1. Simpan node depan dan datanya
    Node* temp = front;
    string docData = temp->document;

    // 2. Geser front ke front->next
    front = front->next;

    // 3. Jika front menjadi nullptr setelah digeser, set rear juga ke nullptr
    if (front == nullptr) {
        rear = nullptr;
    }

    // 4. Delete node lama dan return data
    delete temp;
    return docData;
    // --- LENGKAPI DI SINI ---
}

void processAllDocuments(Node*& front, Node*& rear) {
    // --- LENGKAPI DI SINI ---
    // Loop hingga queue kosong, dequeue dan print setiap dokumen
    while (front != nullptr) {
        string doc = dequeue(front, rear);
        cout << "Memproses: " << doc << endl;
    }
    // --- LENGKAPI DI SINI ---
}

int main() {
    Node* front = nullptr;
    Node* rear = nullptr;

    enqueue(front, rear, "Document1.pdf");
    enqueue(front, rear, "Report.docx");
    enqueue(front, rear, "Presentation.pptx");

    cout << "Memulai pemprosesan antrian printer:" << endl;
    processAllDocuments(front, rear);

    return 0;
}
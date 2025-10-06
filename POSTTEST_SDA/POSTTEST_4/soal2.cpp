#include <iostream>
#include <string>
using namespace std;

struct Node {
    char data;
    Node* next;
};

// Anda bisa menggunakan fungsi push dan pop dari soal sebelumnya.
void push(Node*& top, char data) {
    Node* newNode = new Node{data, top};
    top = newNode;
}

char pop(Node*& top) {
    if (top == nullptr) return '\0';
    Node* temp = top;
    char poppedValue = temp->data;
    top = top->next;
    delete temp;
    return poppedValue;
}



bool areBracketsBalanced(string expr) {
    Node* stackTop = nullptr;

    // --- LENGKAPI DI SINI ---
    // 1. Loop setiap karakter dalam `expr`.
    for (char c : expr) {
        // 2. Jika karakter adalah kurung buka '(', '{', '[', push ke stack.
        if (c == '(' || c == '{' || c == '[') {
            push(stackTop, c);
        }
        // 3. Jika karakter adalah kurung tutup ')', '}', ']'.
        else if (c == ')' || c == '}' || c == ']') {
            // a. Cek apakah stack kosong.
            if (stackTop == nullptr) {
                return false; // Ada kurung tutup tanpa kurung buka
            }

            // b. Pop stack dan cek kecocokan.
            char openBracket = pop(stackTop);
            if ((c == ')' && openBracket != '(') ||
                (c == '}' && openBracket != '{') ||
                (c == ']' && openBracket != '[')) {
                return false; // Pasangan kurung tidak cocok
            }
        }
    }

    // 4. Setelah loop, jika stack kosong, berarti seimbang.
    return stackTop == nullptr;
    // --- LENGKAPI DI SINI ---
}

int main() {
    string expr1 = "{[()]}";
    cout << expr1 << " -> " << (areBracketsBalanced(expr1) ? "Seimbang" : "Tidak Seimbang") << endl;
    string expr2 = "{[(])}";
    cout << expr2 << " -> " << (areBracketsBalanced(expr2) ? "Tidak Seimbang" : "Seimbang") << endl;
    //uji coba tambahan
    string expr3 = "{{{";
    cout << expr3 << " -> " << (areBracketsBalanced(expr3) ? "Seimbang" : "Tidak Seimbang") << endl;

    return 0;
}
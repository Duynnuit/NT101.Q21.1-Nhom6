#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Hàm chuẩn hóa dữ liệu: Chuyển về chữ in hoa và loại bỏ các ký tự không phải alphabet
string normalize_text(const string& text) {
    string normalized = "";
    for (char c : text) {
        if (isalpha(c)) {
            normalized += toupper(c);
        }
    }
    return normalized;
}

// Hàm mã hóa Vigenère
string vigenere_encrypt(const string& plaintext, const string& key) {
    string pt = normalize_text(plaintext);
    string k = normalize_text(key);

    if (k.empty()) return "";

    string ciphertext = "";
    int m = k.length();

    for (int i = 0; i < pt.length(); i++) {
        int p_i = pt[i] - 'A';
        int k_i = k[i % m] - 'A';

        // C_i = (p_i + k_i) mod 26
        int c_i = (p_i + k_i) % 26;
        ciphertext += (char)(c_i + 'A');
    }
    return ciphertext;
}

// Hàm giải mã Vigenère
string vigenere_decrypt(const string& ciphertext, const string& key) {
    string ct = normalize_text(ciphertext);
    string k = normalize_text(key);

    if (k.empty()) return "";

    string plaintext = "";
    int m = k.length();

    for (int i = 0; i < ct.length(); i++) {
        int c_i = ct[i] - 'A';
        int k_i = k[i % m] - 'A';

        // p_i = (C_i - k_i + 26) mod 26
        int p_i = (c_i - k_i + 26) % 26;
        plaintext += (char)(p_i + 'A');
    }
    return plaintext;
}

int main() {
    int choice;
    string key, text, result;

    cout << "--- CHUONG TRINH MA HOA/GIAI MA VIGENERE ---\n";
    cout << "1. Ma hoa (Encrypt)\n";
    cout << "2. Giai ma (Decrypt)\n";
    cout << "Chon chuc nang (1 hoac 2): ";
    cin >> choice;

    // Xóa bộ nhớ đệm sau khi nhập số
    cin.ignore();

    cout << "Nhap khoa (Key): ";
    getline(cin, key);

    if (choice == 1) {
        cout << "Nhap ban ro (Plaintext): ";
        getline(cin, text);

        result = vigenere_encrypt(text, key);
        cout << "\n=> Ban ma (Ciphertext): " << result << "\n";

    }
    else if (choice == 2) {
        cout << "Nhap ban ma (Ciphertext): ";
        getline(cin, text);

        result = vigenere_decrypt(text, key);
        cout << "\n=> Ban ro (Plaintext):  " << result << "\n";

    }
    else {
        cout << "Lua chon khong hop le!\n";
    }

    return 0;
}
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string encrypt(const string& text, int key) {
    string r = text;
    for (char& c : r) {
        if (isupper(c)) c = 'A' + (c - 'A' + key) % 26;
        else if (islower(c)) c = 'a' + (c - 'a' + key) % 26;
    }
    return r;
}

string decrypt(const string& text, int key) {
    string r = text;
    for (char& c : r) {
        if (isupper(c)) c = 'A' + (c - 'A' - key + 26) % 26;
        else if (islower(c)) c = 'a' + (c - 'a' - key + 26) % 26;
    }
    return r;
}

double scoreText(const string& text) {
    double freq[26] = { 0.08167,0.01492,0.02782,0.04253,0.12702,
                        0.02228,0.02015,0.06094,0.06966,0.00153,
                        0.00772,0.04025,0.02406,0.06749,0.07507,
                        0.01929,0.00095,0.05987,0.06327,0.09056,
                        0.02758,0.00978,0.02360,0.00150,0.01974,0.00074 };
    int count[26] = { 0 };
    for (char c : text)
        if (isalpha(c)) count[toupper(c) - 'A']++;
    double s = 0;
    for (int i = 0; i < 26; i++) s += freq[i] * count[i];
    return s;
}

void bruteForce(const string& cipher) {
    cout << "\n[Brute Force - 26 ket qua:]\n";
    for (int k = 1; k <= 26; k++)
        cout << "Key " << k << ": " << decrypt(cipher, k) << "\n\n";
}

string autoSolve(const string& cipher) {
    double best = -1;
    string bestText;
    for (int k = 0; k < 26; k++) {
        string t = decrypt(cipher, k);
        double sc = scoreText(t);
        if (sc > best) { best = sc; bestText = t; }
    }
    return bestText;
}

string normalize(const string& text) {
    string r;
    for (char c : text) {
        if (isalpha((unsigned char)c)) r += toupper(c);
        else if (c == ' ') r += ' ';
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "1. Encrypt\n2. Decrypt (biet key)\n3. Brute Force\n4. Auto Decode\n";
    cout << "Chon chuc nang (1-4): ";
    int choice; cin >> choice; cin.ignore();

    if (choice == 1) {
        cout << "Nhap plaintext: "; string text; getline(cin, text);
        cout << "Nhap key (1-26): "; int key; cin >> key;
        cout << "\nCiphertext: " << encrypt(text, key) << "\n";
    }
    else if (choice == 2) {
        cout << "Nhap ciphertext: "; string text; getline(cin, text);
        cout << "Nhap key (1-26): "; int key; cin >> key;
        cout << "\nPlaintext: " << decrypt(text, key) << "\n";
    }
    else if (choice == 3) {
        cout << "Nhap ciphertext: "; string text; getline(cin, text);
        bruteForce(normalize(text));
    }
    else {
        string input, line;
        cout << "Nhap ciphertext:\n";
        getline(cin, input);
        cout << "\nPLAINTEXT:\n" << autoSolve(normalize(input));
    }
    return 0;
}
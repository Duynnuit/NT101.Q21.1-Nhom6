#include <iostream>
#include <string>
#include <cctype>
#include <map>
using namespace std;

string encrypt(const string& text, int key) {
    string result = "";
    key = ((key % 26) + 26) % 26;
    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            result += (char)((c - base + key) % 26 + base);
        }
        else {
            result += c;
        }
    }
    return result;
}

string decrypt(const string& text, int key) {
    return encrypt(text, 26 - key);
}

double scoreText(const string& text) {
    double freq[] = {
        0.08167, 0.01492, 0.02782, 0.04253, 0.12702,
        0.02228, 0.02015, 0.06094, 0.06966, 0.00153,
        0.00772, 0.04025, 0.02406, 0.06749, 0.07507,
        0.01929, 0.00095, 0.05987, 0.06327, 0.09056,
        0.02758, 0.00978, 0.02360, 0.00150, 0.01974, 0.00074
    };

    int count[26] = { 0 };
    int total = 0;
    for (char c : text) {
        if (isalpha(c)) {
            count[tolower(c) - 'a']++;
            total++;
        }
    }

    if (total == 0) return 0;

    double score = 0;
    for (int i = 0; i < 26; i++) {
        score += freq[i] * count[i];
    }
    return score;
}

void bruteForce(const string& ciphertext) {
    cout << string(60, '-') << endl;

    double bestScore = -1;
    int bestKey = 0;
    string bestText = "";

    for (int key = 0; key < 26; key++) {
        string decrypted = decrypt(ciphertext, key);
        double score = scoreText(decrypted);
        cout << "Key " << key << ": " << decrypted.substr(0, 40) << "..." << endl;
        if (score > bestScore) {
            bestScore = score;
            bestKey = key;
            bestText = decrypted;
        }
    }

    cout << string(60, '-') << endl;
    cout << "\n>>> KET QUA GIAI MA DUY NHAT:" << endl;
    cout << "Khoa tot nhat: " << bestKey << endl;
    cout << "Van ban ro:\n" << bestText << endl;
}

int main() {
    int choice;
    cout << "CAESAR CIPHER" << endl;
    cout << "1. Ma hoa" << endl;
    cout << "2. Giai ma (nhap khoa)" << endl;
    cout << "3. Brute-force" << endl;
    cout << "Chon chuc nang (1/2/3): ";
    cin >> choice;
    cin.ignore();

    string text;
    cout << "Nhap chuoi van ban: ";
    getline(cin, text);

    if (choice == 1) {
        int key;
        cout << "Nhap khoa (0-25): ";
        cin >> key;
        string encrypted = encrypt(text, key);
        cout << "\nVan ban ma hoa: " << encrypted << endl;

    }
    else if (choice == 2) {
        int key;
        cout << "Nhap khoa (0-25): ";
        cin >> key;
        string decrypted = decrypt(text, key);
        cout << "\nVan ban giai ma: " << decrypted << endl;

    }
    else if (choice == 3) {
        bruteForce(text);

    }
    else {
        cout << "Lua chon khong hop le!" << endl;
    }

    return 0;
}
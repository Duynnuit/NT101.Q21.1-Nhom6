#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
#include <iomanip>

using namespace std;

bool cmp(const pair<int, char>& a, const pair<int, char>& b) {
    if (a.first != b.first) return a.first > b.first;
    return a.second < b.second;
}

int main() {
    string ciphertext = "", line;

    cout << "Nhap van ban da ma hoa(Sau khi nhap xong nhap 'END' de ket thuc): \n";
    while (getline(cin, line) && line != "END") {
        ciphertext += line + "\n";
    }

    if (ciphertext.empty()) return 0;

    map<char, int> counts;
    int total_letters = 0;
    for (char c = 'A'; c <= 'Z'; ++c) counts[c] = 0;

    for (char c : ciphertext) {
        if (isalpha((unsigned char)c)) {
            counts[toupper((unsigned char)c)]++;
            total_letters++;
        }
    }

    vector<pair<int, char>> sorted_chars;
    for (auto const& p : counts) {
        sorted_chars.push_back({ p.second, p.first });
    }
    sort(sorted_chars.begin(), sorted_chars.end(), cmp);

    cout << "\n--- THONG KE TAN SUAT ---\n";
    cout << "Ky tu\tSo lan\tTi le (%)\n";
    for (const auto& p : sorted_chars) {
        if (p.first > 0) {
            cout << "  " << p.second << "\t  " << p.first << "\t  "
                << fixed << setprecision(2) << (p.first * 100.0) / total_letters << "%\n";
        }
    }

    string eng_freq = "ETAOINSHRDLCUMWFGYPBVKJXQZ";
    map<char, char> key, rev_key;

    for (size_t i = 0; i < sorted_chars.size(); ++i) {
        char c = sorted_chars[i].second;
        char p = eng_freq[i];
        key[c] = p;
        rev_key[p] = c;
    }

    char c1, c2;
    while (true) {
        string plaintext = "";
        for (char c : ciphertext) {
            unsigned char uc = static_cast<unsigned char>(c);
            if (isalpha(uc)) {
                char p = key[toupper(uc)];
                plaintext += isupper(uc) ? p : tolower(p);
            }
            else {
                plaintext += c;
            }
        }
        cout << "\n--- BAN RO HIEN TAI ---\n" << plaintext;
        cout << "\nNhap 2 chu cai can hoan doi (VD: A E). Nhap '0 0' de thoat: ";
        cin >> c1 >> c2;

        if (c1 == '0' || c2 == '0') break;

        c1 = toupper(c1);
        c2 = toupper(c2);

        char k1 = rev_key[c1];
        char k2 = rev_key[c2];

        key[k1] = c2;
        key[k2] = c1;

        rev_key[c1] = k2;
        rev_key[c2] = k1;
    }
    return 0;
}
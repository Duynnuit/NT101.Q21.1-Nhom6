#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include <cctype>
using namespace std;

string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// Chuẩn hóa
string normalize(string text) {
    string result = "";
    for (char c : text)
        if (isalpha(c))
            result += toupper(c);
    return result;
}

// Giải mã
string decryptFast(string& cipher, string& key) {
    string result = cipher;
    for (int i = 0; i < cipher.length(); i++)
        result[i] = key[cipher[i] - 'A'];
    return result;
}

// Chấm điểm đơn giản nhưng hiệu quả
double score(string& text) {
    double s = 0;
    for (int i = 0; i < text.length() - 1; i++) {
        if (text[i] == 'T' && text[i + 1] == 'H') s += 3;
        if (text[i] == 'H' && text[i + 1] == 'E') s += 3;
        if (text[i] == 'I' && text[i + 1] == 'N') s += 2;
        if (text[i] == 'E') s += 0.5;
    }
    return s;
}

// Tạo key ngẫu nhiên
string randomKey() {
    string key = alphabet;
    random_shuffle(key.begin(), key.end());
    return key;
}

int main() {
    srand(time(0));

    string input, line;
    cout << "Nhap ciphertext (ket thuc bang dong trong):\n";

    while (true) {
        getline(cin, line);
        if (line.empty()) break;
        input += line;
    }

    string cipher = normalize(input);

    string bestKey;
    string bestText;
    double bestScore = -1;

    // Chỉ 10 restart để chạy nhanh
    for (int restart = 0; restart < 10; restart++) {

        string key = randomKey();
        string plain = decryptFast(cipher, key);
        double localBest = score(plain);

        // 2000 vòng là đủ
        for (int i = 0; i < 2000; i++) {

            string newKey = key;
            int a = rand() % 26;
            int b = rand() % 26;
            swap(newKey[a], newKey[b]);

            string newPlain = decryptFast(cipher, newKey);
            double newScore = score(newPlain);

            if (newScore > localBest) {
                key = newKey;
                localBest = newScore;
            }
        }

        if (localBest > bestScore) {
            bestScore = localBest;
            bestKey = key;
            bestText = decryptFast(cipher, key);
        }
    }

    cout << "\n========== KET QUA ==========\n";
    cout << "Key: " << bestKey << endl;
    cout << "\nPlaintext:\n" << bestText << endl;

    return 0;
}
#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;

string normalize(string s)
{
    string r = "";
    for (char c : s)
        if (isalpha(c))
            r += tolower(c);
    return r;
}

double IC(string s)
{
    int f[26] = { 0 };

    for (char c : s)
        f[c - 'a']++;

    int n = s.length();
    if (n < 2) return 0;

    double sum = 0;

    for (int i = 0;i < 26;i++)
        sum += f[i] * (f[i] - 1);

    return sum / (n * (n - 1.0));
}

string getGroup(string s, int start, int k)
{
    string g = "";

    for (int i = start;i < s.length();i += k)
        g += s[i];

    return g;
}

char findShift(string g)
{
    double freqEng[26] = {
        8.2,1.5,2.8,4.3,12.7,2.2,2.0,6.1,7.0,0.15,
        0.77,4.0,2.4,6.7,7.5,1.9,0.095,6.0,6.3,9.1,
        2.8,1.0,2.4,0.15,2.0,0.074
    };

    int n = g.length();
    int freq[26];

    double bestScore = 1e18;
    int bestShift = 0;

    for (int shift = 0; shift < 26; shift++)
    {
        for (int i = 0;i < 26;i++)
            freq[i] = 0;

        for (char c : g)
        {
            int p = (c - 'a' - shift + 26) % 26;
            freq[p]++;
        }

        double score = 0;

        for (int i = 0;i < 26;i++)
        {
            double expected = freqEng[i] * n / 100;
            score += (freq[i] - expected) * (freq[i] - expected) / expected;
        }

        if (score < bestScore)
        {
            bestScore = score;
            bestShift = shift;
        }
    }

    return char(bestShift + 'a');
}

string findKey(string text, int k)
{
    string key = "";

    for (int i = 0;i < k;i++)
    {
        string g = getGroup(text, i, k);
        key += findShift(g);
    }

    return key;
}

string decrypt(string cipher, string key)
{
    string plain = "";
    int k = key.length();
    int j = 0;

    for (char c : cipher)
    {
        if (isalpha(c))
        {
            int ci = tolower(c) - 'a';
            int ki = key[j % k] - 'a';

            char p = (ci - ki + 26) % 26 + 'a';

            plain += p;
            j++;
        }
        else
            plain += c;
    }

    return plain;
}

int guessKeyLength(string text)
{
    double targetIC = 0.067;
    double bestDiff = 1;

    int bestLen = 1;
    int maxKey = sqrt(text.length());

    for (int k = 1;k <= maxKey;k++)
    {
        double avgIC = 0;

        for (int i = 0;i < k;i++)
        {
            string g = getGroup(text, i, k);
            avgIC += IC(g);
        }

        avgIC /= k;

        double diff = fabs(avgIC - targetIC);

        if (diff < bestDiff)
        {
            bestDiff = diff;
            bestLen = k;
        }
    }

    return bestLen;
}

int main()
{
    string cipher;

    cout << "Nhap ciphertext:\n";
    getline(cin, cipher);

    string norm = normalize(cipher);

    int keyLen = guessKeyLength(norm);

    cout << "\nDo dai key du doan: " << keyLen << endl;

    string key = findKey(norm, keyLen);

    cout << "Key tim duoc: " << key << endl;

    string plain = decrypt(cipher, key);

    cout << "\nPlaintext:\n" << plain << endl;

    return 0;
}
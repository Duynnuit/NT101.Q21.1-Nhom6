#include <iostream>
#include <string>
#include <cctype>

using namespace std;

char matrix_pf[5][5];

void createMatrix(string key)
{
    bool used[26] = { false };
    int k = 0;

    for (int i = 0; i < key.length(); i++)
    {
        char c = toupper(key[i]);

        if (c == 'J')
            c = 'I';

        if (c < 'A' || c > 'Z')
            continue;

        if (!used[c - 'A'])
        {
            matrix_pf[k / 5][k % 5] = c;
            used[c - 'A'] = true;
            k++;
        }
    }

    for (char c = 'A'; c <= 'Z'; c++)
    {
        if (c == 'J')
            continue;

        if (!used[c - 'A'])
        {
            matrix_pf[k / 5][k % 5] = c;
            used[c - 'A'] = true;
            k++;
        }
    }
}

void printMatrix()
{
    cout << "Playfair Matrix:\n";

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
            cout << matrix_pf[i][j] << " ";

        cout << endl;
    }
}

void findPosition(char c, int& row, int& col)
{
    if (c == 'J')
        c = 'I';

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (matrix_pf[i][j] == c)
            {
                row = i;
                col = j;
            }
}

string normalizeText(string s)
{
    string result = "";

    for (int i = 0; i < s.length(); i++)
    {
        if (isalpha(s[i]))
        {
            char c = toupper(s[i]);

            if (c == 'J')
                c = 'I';

            result += c;
        }
    }

    return result;
}

string prepareText(string s)
{
    string result = "";

    for (int i = 0; i < s.length(); i++)
    {
        result += s[i];

        if (i + 1 < s.length() && s[i] == s[i + 1])
            result += 'X';
    }

    if (result.length() % 2 != 0)
        result += 'X';

    return result;
}

string encryptText(string s)
{
    string result = "";

    for (int i = 0; i < s.length(); i += 2)
    {
        char a = s[i];
        char b = s[i + 1];

        int r1, c1, r2, c2;

        findPosition(a, r1, c1);
        findPosition(b, r2, c2);

        if (r1 == r2)
        {
            result += matrix_pf[r1][(c1 + 1) % 5];
            result += matrix_pf[r2][(c2 + 1) % 5];
        }
        else if (c1 == c2)
        {
            result += matrix_pf[(r1 + 1) % 5][c1];
            result += matrix_pf[(r2 + 1) % 5][c2];
        }
        else
        {
            result += matrix_pf[r1][c2];
            result += matrix_pf[r2][c1];
        }
    }

    return result;
}

string decryptText(string s)
{
    string result = "";

    for (int i = 0; i < s.length(); i += 2)
    {
        char a = s[i];
        char b = s[i + 1];

        int r1, c1, r2, c2;

        findPosition(a, r1, c1);
        findPosition(b, r2, c2);

        if (r1 == r2)
        {
            result += matrix_pf[r1][(c1 + 4) % 5];
            result += matrix_pf[r2][(c2 + 4) % 5];
        }
        else if (c1 == c2)
        {
            result += matrix_pf[(r1 + 4) % 5][c1];
            result += matrix_pf[(r2 + 4) % 5][c2];
        }
        else
        {
            result += matrix_pf[r1][c2];
            result += matrix_pf[r2][c1];
        }
    }

    return result;
}

int main()
{
    string key;
    string text;
    int choice;

    cout << "Enter key: ";
    getline(cin, key);

    createMatrix(key);

    printMatrix();

    cout << "\n1. Encrypt\n2. Decrypt\nChoose: ";
    cin >> choice;
    cin.ignore();

    cout << "Enter text: ";
    getline(cin, text);

    text = normalizeText(text);

    if (choice == 1)
    {
        text = prepareText(text);
        cout << "Ciphertext: " << encryptText(text);
    }
    else
    {
        cout << "Plaintext: " << decryptText(text);
    }

    return 0;
}
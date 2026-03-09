#include <iostream>
#include <vector>
#include <string>
using namespace std;

string encryptRailFence(string text, int key)
{
    vector<vector<char>> rail(key, vector<char>(text.length(), '\n'));

    bool dir_down = false;
    int row = 0, col = 0;

    for (int i = 0; i < text.length(); i++)
    {
        if (row == 0 || row == key - 1)
            dir_down = !dir_down;

        rail[row][col++] = text[i];

        if (dir_down)
            row++;
        else
            row--;
    }

    string result;

    for (int i = 0; i < key; i++)
        for (int j = 0; j < text.length(); j++)
            if (rail[i][j] != '\n')
                result += rail[i][j];

    return result;
}

string decryptRailFence(string cipher, int key)
{
    vector<vector<char>> rail(key, vector<char>(cipher.length(), '\n'));

    bool dir_down;
    int row = 0, col = 0;

    for (int i = 0; i < cipher.length(); i++)
    {
        if (row == 0)
            dir_down = true;
        if (row == key - 1)
            dir_down = false;

        rail[row][col++] = '*';

        if (dir_down)
            row++;
        else
            row--;
    }

    int index = 0;

    for (int i = 0; i < key; i++)
        for (int j = 0; j < cipher.length(); j++)
            if (rail[i][j] == '*' && index < cipher.length())
                rail[i][j] = cipher[index++];

    string result;
    row = 0;
    col = 0;

    for (int i = 0; i < cipher.length(); i++)
    {
        if (row == 0)
            dir_down = true;
        if (row == key - 1)
            dir_down = false;

        if (rail[row][col] != '\n')
            result += rail[row][col++];

        if (dir_down)
            row++;
        else
            row--;
    }

    return result;
}

int main()
{
    int choice;
    string text;
    int key;

    cout << "1. Encrypt\n";
    cout << "2. Decrypt\n";
    cout << "Choose: ";
    cin >> choice;
    cin.ignore();

    cout << "Enter text: ";
    getline(cin, text);

    cout << "Enter key: ";
    cin >> key;

    if (choice == 1)
    {
        string cipher = encryptRailFence(text, key);
        cout << "Ciphertext: " << cipher;
    }
    else if (choice == 2)
    {
        string plain = decryptRailFence(text, key);
        cout << "Plaintext: " << plain;
    }
    else
    {
        cout << "Invalid choice";
    }

    return 0;
}
#include <bits/stdc++.h>

using namespace std;

vector<vector<char>> createMatrix(string key) {
    unordered_set<char> s;
    queue<char> q;
    for (char c : key) {
        if (s.find(c) == s.end()) {
            s.insert(c);
            q.push(c);
        }
    }
    for (char c = 'A'; c <= 'Z'; c++) {
        if (c != 'Q') {
            if (s.find(c) == s.end()) {
                s.insert(c);
                q.push(c);
            }
        }
    }
    vector<vector<char>> ans(5, vector<char>(5));
    int i = 0;
    while (!q.empty()) {
        ans[i / 5][i % 5] = q.front();
        q.pop();
        i++;
    }
    return ans;
}
string encryptString(string text, string key) {
    vector<vector<char>> mat = createMatrix(key);
    unordered_map<char, pair<int, int>> m;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            m[mat[i][j]] = {i, j};
        }
    }
    int n = text.length();
    string ans;
    for (int i = 0; i < n - 1; i += 2) {
        pair<int, int> pos1 = m[text[i]];
        pair<int, int> pos2 = m[text[i + 1]];
        if (pos1.first == pos2.first) {
            ans += mat[pos1.first][(pos1.second + 1) % 5];
            ans += mat[pos2.first][(pos2.second + 1) % 5];
        } else if (pos1.second == pos2.second) {
            ans += mat[(pos1.first + 1) % 5][pos1.second];
            ans += mat[(pos2.first + 1) % 5][pos2.second];
        } else {
            ans += mat[pos1.first][pos2.second];
            ans += mat[pos2.first][pos1.second];
        }
    }
    return ans;
}
string decryptString(string text, string key) {
    vector<vector<char>> mat = createMatrix(key);
    unordered_map<char, pair<int, int>> m;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            m[mat[i][j]] = {i, j};
        }
    }
    int n = text.length();
    string ans;
    for (int i = 0; i < n - 1; i += 2) {
        pair<int, int> pos1 = m[text[i]];
        pair<int, int> pos2 = m[text[i + 1]];
        if (pos1.first == pos2.first) {
            ans += mat[pos1.first][(pos1.second - 1) % 5];
            ans += mat[pos2.first][(pos2.second - 1) % 5];
        } else if (pos1.second == pos2.second) {
            ans += mat[(pos1.first - 1) % 5][pos1.second];
            ans += mat[(pos2.first - 1) % 5][pos2.second];
        } else {
            ans += mat[pos1.first][pos2.second];
            ans += mat[pos2.first][pos1.second];
        }
    }
    return ans;
}
pair<int, int> findPos(vector<vector<char>> mat, char c) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (mat[i][j] == c) {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}
vector<vector<char>> break_cipher(string plainText, string cipherText) {
    vector<vector<char>> mat = createMatrix("ABCDEFGHIJKLMNOPRSTUVWXYZ");
    for (int i = 0; i < plainText.length(); i += 2) {
        char a = plainText[i];
        char b = plainText[i + 1];

        pair<int, int> pos1 = findPos(mat, a);
        pair<int, int> pos2 = findPos(mat, b);
        pair<int, int> posCipher1 = findPos(mat, cipherText[i]);
        pair<int, int> posCipher2 = findPos(mat, cipherText[i + 1]);
         if (pos1.first == pos2.first) {
            swap(mat[pos1.first][(pos1.second + 1) % 5], mat[posCipher1.first][posCipher2.second]);
            swap(mat[pos2.first][(pos2.second + 1) % 5], mat[posCipher2.first][posCipher1.second]);
        } else if (pos1.second == pos2.second) {
            swap(mat[(pos1.first + 1) % 5][pos1.second], mat[posCipher2.first][posCipher1.second]);
            swap(mat[(pos2.first + 1) % 5][pos2.second], mat[posCipher1.first][posCipher2.second]);
        } else {
            swap(mat[pos1.first][pos2.second], mat[posCipher1.first][posCipher1.second]);
            swap(mat[pos2.first][pos1.second], mat[posCipher2.first][posCipher2.second]);
        }
    }
    return mat;
}
int main() {
    string key = "MONARCHY";
    string plainText = "GETTHEGOLD";
    string cipherText = encryptString(plainText, key);
    cout << "Cipher Text: " << cipherText << endl;
    string partialPlaintext = "GETH";
    vector<vector<char>> mat = break_cipher(partialPlaintext, cipherText);
    string key1 = "";
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            key1 += mat[i][j];
        }
    }
    cout << "Plain Text: " << plainText << endl;
    cout << "Original Key: " << key << endl;
    cout << "Predicted Key: " << key1 << endl;
    cout << "Cipher text using key predcited: " << encryptString(plainText, key1) << endl;
    cout << "Decrypted text using key predcited: " << decryptString(cipherText, key1) << endl;
    return 0;
}

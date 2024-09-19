#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <bits/stdc++.h>
using namespace std;
const std::string ALPHABET = "ABCDEFGHIKLMNOPQRSTUVWXYZ"; // Note: J is omitted

// Function to create the 5x5 key matrix
vector<vector<char>> createKeyMatrix(string key) {
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

// Function to find the position of a character in the key matrix
std::pair<int, int> findPosition(const std::vector<std::vector<char>>& matrix, char c) {
    if (c == 'J') c = 'I';
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == c) {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

// Function to decrypt a message using the Playfair cipher
std::string encrypt(const std::string& plainText, const std::string& key) {
    auto matrix = createKeyMatrix(key);
    std::string cipherText = "";
    for (size_t i = 0; i < plainText.length(); i += 2) {
        char a = plainText[i];
        char b = plainText[i + 1];

        auto [row1, col1] = findPosition(matrix, a);
        auto [row2, col2] = findPosition(matrix, b);

        if (row1 == row2) {
            cipherText += matrix[row1][(col1 + 1 + 5) % 5];
            cipherText += matrix[row2][(col2 + 1 + 5) % 5];
        } else if (col1 == col2) {
            cipherText += matrix[(row1 + 1 + 5) % 5][col1];
            cipherText += matrix[(row2 + 1 + 5) % 5][col2];
        } else {
            cipherText += matrix[row1][col2];
            cipherText += matrix[row2][col1];
        }
    }

    return cipherText;
}
std::string decrypt(const std::string& ciphertext, const std::string& key) {
    auto matrix = createKeyMatrix(key);
    std::string plaintext = "";

    for (size_t i = 0; i < ciphertext.length(); i += 2) {
        char a = ciphertext[i];
        char b = ciphertext[i + 1];

        auto [row1, col1] = findPosition(matrix, a);
        auto [row2, col2] = findPosition(matrix, b);

        if (row1 == row2) {
            plaintext += matrix[row1][(col1 - 1 + 5) % 5];
            plaintext += matrix[row2][(col2 - 1 + 5) % 5];
        } else if (col1 == col2) {
            plaintext += matrix[(row1 - 1 + 5) % 5][col1];
            plaintext += matrix[(row2 - 1 + 5) % 5][col2];
        } else {
            plaintext += matrix[row1][col2];
            plaintext += matrix[row2][col1];
        }
    }

    return plaintext;
}

// Function to evaluate the quality of a key
int evaluateKey(const std::string& key, const std::string& knownPlaintext, const std::string& knownCiphertext) {
    std::string decrypted = decrypt(knownCiphertext, key);
    int score = 0;
    for (size_t i = 0; i < knownPlaintext.length(); ++i) {
        if (i < decrypted.length() && knownPlaintext[i] == decrypted[i]) {
            score++;
        }
    }
    return score;
}

// Function to generate a random key
std::string generateRandomKey() {
    std::string key = ALPHABET;
    for (int i = 24; i > 0; --i) {
        std::swap(key[i], key[std::rand() % (i + 1)]);
    }
    return key;
}

// Function to mutate a key
std::string mutateKey(const std::string& key) {
    std::string newKey = key;
    int pos1 = std::rand() % 25;
    int pos2 = std::rand() % 25;
    std::swap(newKey[pos1], newKey[pos2]);
    return newKey;
}

// Main function to break the Playfair cipher
std::string break_playfair(const std::string& partialPlaintext, const std::string& ciphertext, int iterations = 1000) {
    std::srand(std::time(nullptr)); // Seed the random number generator
    
    std::string bestKey = generateRandomKey();
    int bestScore = evaluateKey(bestKey, partialPlaintext, ciphertext);

    for (int i = 0; i < iterations; ++i) {
        std::string newKey = mutateKey(bestKey);
        int newScore = evaluateKey(newKey, partialPlaintext, ciphertext);

        if (newScore > bestScore) {
            bestKey = newKey;
            bestScore = newScore;
        }
    }

    return bestKey;
}

int main() {
    string plainText = "GETTHEGOLD";
    string key = "MONARCHY";
    string ciphertext = encrypt(plainText, key);
    cout << ciphertext << endl;
    // std::string partialPlaintext = "GETTH";
    // std::string ciphertext = "KCZPZR";

    // std::string foundKey = break_playfair(partialPlaintext, ciphertext);

    // std::cout << "Found key: " << foundKey << std::endl;
    // std::cout << "Decrypted: " << decrypt(ciphertext, foundKey) << std::endl;

    return 0;
}
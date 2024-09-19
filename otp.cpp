#include <iostream>
#include <vector>
#include <random>
#include <bitset>
#include <iomanip>

using namespace std;

const int KEY_SIZE = 32;

vector<unsigned char> generateKey() {
    random_device rd;
    uniform_int_distribution<int> dist(0, 255);

    vector<unsigned char> key(KEY_SIZE);
    for (int i = 0; i < KEY_SIZE; ++i) {
        key[i] = static_cast<unsigned char>(dist(rd));
    }
    return key;
}

vector<unsigned char> otpEncryptDecrypt(const vector<unsigned char>& text, const vector<unsigned char>& key) {
    vector<unsigned char> result(text.size());
    for (size_t i = 0; i < text.size(); ++i) {
        result[i] = text[i] ^ key[i % key.size()];
    }
    return result;
}

void printHex(const vector<unsigned char>& data) {
    for (size_t i = 0; i < data.size(); ++i) {
        cout << hex << setw(2) << setfill('0') << static_cast<int>(data[i]) << " ";
    }
    cout << dec << endl;
}

int main() {
    vector<unsigned char> plaintext = {
        'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 'a', ' ', 't', 'e', 's', 't', ' ', 'm', 'e', 's', 's', 'a', 'g', 'e', ' ', '!', '!', '!', '!', '!', '!', '!', '!' };

    vector<unsigned char> key = generateKey();

    cout << "Plaintext: ";
    printHex(plaintext);

    cout << "Key:       ";
    printHex(key);

    vector<unsigned char> ciphertext = otpEncryptDecrypt(plaintext, key);
    cout << "Ciphertext:";
    printHex(ciphertext);

    vector<unsigned char> decryptedtext = otpEncryptDecrypt(ciphertext, key);
    cout << "Decrypted: ";
    printHex(decryptedtext);

    return 0;
}
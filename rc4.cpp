#include <iostream>
#include <vector>
#include <string>

using namespace std;

class RC4 {
private:
    vector<int> S;
    int key_length;

public:
    RC4(const vector<unsigned char>& key) {
        key_length = key.size();
        S.resize(256);
        KSA(key);
    }

    void KSA(const vector<unsigned char>& key) {
        for (int i = 0; i < 256; ++i) {
            S[i] = i;
        }
        int j = 0;
        for (int i = 0; i < 256; ++i) {
            j = (j + S[i] + key[i % key_length]) % 256;
            swap(S[i], S[j]);
        }
    }

    vector<unsigned char> encrypt(const vector<unsigned char>& data) {
        vector<unsigned char> result(data.size());
        int i = 0, j = 0;
        for (size_t n = 0; n < data.size(); ++n) {
            i = (i + 1) % 256;
            j = (j + S[i]) % 256;
            swap(S[i], S[j]);
            int K = S[(S[i] + S[j]) % 256];
            result[n] = data[n] ^ K;
        }
        return result;
    }
};

int main() {
    string key_str = "SecretKey";
    vector<unsigned char> key(key_str.begin(), key_str.end());

    string plaintext = "Hello, RC4!";
    vector<unsigned char> data(plaintext.begin(), plaintext.end());

    RC4 rc4(key);
    vector<unsigned char> ciphertext = rc4.encrypt(data);

    cout << "Ciphertext: ";
    for (unsigned char c : ciphertext) {
        printf("%02X ", c);
    }
    cout << endl;

    RC4 rc4_decrypt(key);
    vector<unsigned char> decrypted = rc4_decrypt.encrypt(ciphertext);

    string decrypted_text(decrypted.begin(), decrypted.end());
    cout << "Decrypted text: " << decrypted_text << endl;

    return 0;
}

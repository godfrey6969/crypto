#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

const int Nb = 4;
const int Nk = 4;
const int Nr = 10;

typedef vector<vector<uint8_t>> state_t;

uint8_t sbox[256] = {
    // S-box table
    // ...
};

void KeyExpansion(const vector<uint8_t>& key, vector<uint8_t>& expandedKey) {
    expandedKey = key;
}

void AddRoundKey(state_t& state, const vector<uint8_t>& roundKey) {
    for (int i = 0; i < Nb; ++i) {
        for (int j = 0; j < 4; ++j) {
            state[j][i] ^= roundKey[i * 4 + j];
        }
    }
}

void SubBytes(state_t& state) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < Nb; ++j) {
            state[i][j] = sbox[state[i][j]];
        }
    }
}

void ShiftRows(state_t& state) {
    uint8_t temp;

    temp = state[1][0];
    state[1][0] = state[1][1];
    state[1][1] = state[1][2];
    state[1][2] = state[1][3];
    state[1][3] = temp;

    temp = state[2][0];
    state[2][0] = state[2][2];
    state[2][2] = temp;
    temp = state[2][1];
    state[2][1] = state[2][3];
    state[2][3] = temp;

    temp = state[3][0];
    state[3][0] = state[3][3];
    state[3][3] = state[3][2];
    state[3][2] = state[3][1];
    state[3][1] = temp;
}

uint8_t xtime(uint8_t x) {
    return ((x << 1) ^ (((x >> 7) & 1) * 0x1b));
}

void MixColumns(state_t& state) {
    uint8_t Tmp, Tm, t;
    for (int i = 0; i < 4; ++i) {
        t = state[0][i];
        Tmp = state[0][i] ^ state[1][i] ^ state[2][i] ^ state[3][i];
        Tm = state[0][i] ^ state[1][i];
        Tm = xtime(Tm);
        state[0][i] ^= Tm ^ Tmp;
        Tm = state[1][i] ^ state[2][i];
        Tm = xtime(Tm);
        state[1][i] ^= Tm ^ Tmp;
        Tm = state[2][i] ^ state[3][i];
        Tm = xtime(Tm);
        state[2][i] ^= Tm ^ Tmp;
        Tm = state[3][i] ^ t;
        Tm = xtime(Tm);
        state[3][i] ^= Tm ^ Tmp;
    }
}

void AES_Encrypt(const vector<uint8_t>& input, const vector<uint8_t>& key, vector<uint8_t>& output) {
    state_t state(4, vector<uint8_t>(Nb));
    vector<uint8_t> expandedKey;

    for (int i = 0; i < 16; ++i) {
        state[i % 4][i / 4] = input[i];
    }

    KeyExpansion(key, expandedKey);

    AddRoundKey(state, expandedKey);

    for (int round = 1; round < Nr; ++round) {
        SubBytes(state);
        ShiftRows(state);
        MixColumns(state);
        AddRoundKey(state, expandedKey);
    }

    SubBytes(state);
    ShiftRows(state);
    AddRoundKey(state, expandedKey);

    output.resize(16);
    for (int i = 0; i < 16; ++i) {
        output[i] = state[i % 4][i / 4];
    }
}

int main() {
    vector<uint8_t> plaintext = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};
    vector<uint8_t> key = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x4d, 0x4a, 0x90, 0x8d, 0x3b, 0x4e};
    vector<uint8_t> ciphertext;

    AES_Encrypt(plaintext, key, ciphertext);

    cout << "Cipher text: ";
    for (uint8_t byte : ciphertext) {
        cout << hex << setw(2) << setfill('0') << (int)byte << " ";
    }
    cout << endl;

    return 0;
}

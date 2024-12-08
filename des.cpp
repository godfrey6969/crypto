#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

int IP[] = { 58, 50, 42, 34, 26, 18, 10, 2,
             60, 52, 44, 36, 28, 20, 12, 4,
             62, 54, 46, 38, 30, 22, 14, 6,
             64, 56, 48, 40, 32, 24, 16, 8,
             57, 49, 41, 33, 25, 17, 9, 1,
             59, 51, 43, 35, 27, 19, 11, 3,
             61, 53, 45, 37, 29, 21, 13, 5,
             63, 55, 47, 39, 31, 23, 15, 7 };

int FP[] = { 40, 8, 48, 16, 56, 24, 64, 32,
             39, 7, 47, 15, 55, 23, 63, 31,
             38, 6, 46, 14, 54, 22, 62, 30,
             37, 5, 45, 13, 53, 21, 61, 29,
             36, 4, 44, 12, 52, 20, 60, 28,
             35, 3, 43, 11, 51, 19, 59, 27,
             34, 2, 42, 10, 50, 18, 58, 26,
             33, 1, 41, 9, 49, 17, 57, 25 };

int E[] = { 32, 1, 2, 3, 4, 5, 4, 5,
            6, 7, 8, 9, 8, 9, 10, 11,
            12, 13, 12, 13, 14, 15, 16, 17,
            16, 17, 18, 19, 20, 21, 20, 21,
            22, 23, 24, 25, 24, 25, 26, 27,
            28, 29, 28, 29, 30, 31, 32, 1 };

int S[8][4][16] = {
    {{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
     {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
     {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
     {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}},
    {{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
     {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
     {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
     {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}},
    {{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
     {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
     {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
     {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}},
    {{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
     {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
     {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
     {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}},
    {{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
     {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
     {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
     {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}},
    {{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
     {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
     {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
     {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}},
    {{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
     {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
     {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
     {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}},
    {{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
     {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
     {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
     {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}}
};

int P[] = { 16, 7, 20, 21,
            29, 12, 28, 17,
            1, 15, 23, 26,
            5, 18, 31, 10,
            2, 8, 24, 14,
            32, 27, 3, 9,
            19, 13, 30, 6,
            22, 11, 4, 25 };

int PC1[] = { 57, 49, 41, 33, 25, 17, 9,
              1, 58, 50, 42, 34, 26, 18,
              10, 2, 59, 51, 43, 35, 27,
              19, 11, 3, 60, 52, 44, 36,
              63, 55, 47, 39, 31, 23, 15,
              7, 62, 54, 46, 38, 30, 22,
              14, 6, 61, 53, 45, 37, 29,
              21, 13, 5, 28, 20, 12, 4 };

int PC2[] = { 14, 17, 11, 24, 1, 5,
              3, 28, 15, 6, 21, 10,
              23, 19, 12, 4, 26, 8,
              16, 7, 27, 20, 13, 2,
              41, 52, 31, 37, 47, 55,
              30, 40, 51, 45, 33, 48,
              44, 49, 39, 56, 34, 53,
              46, 42, 50, 36, 29, 32 };

int shifts[] = { 1, 1, 2, 2, 2, 2, 2, 2,
                 1, 2, 2, 2, 2, 2, 2, 1 };

bitset<64> initialPermutation(bitset<64> plainText) {
    bitset<64> permutedText;
    for (int i = 0; i < 64; i++) {
        permutedText[63 - i] = plainText[64 - IP[i]];
    }
    return permutedText;
}

bitset<64> finalPermutation(bitset<64> text) {
    bitset<64> permutedText;
    for (int i = 0; i < 64; i++) {
        permutedText[63 - i] = text[64 - FP[i]];
    }
    return permutedText;
}

bitset<48> expansionPermutation(bitset<32> halfBlock) {
    bitset<48> expandedBlock;
    for (int i = 0; i < 48; i++) {
        expandedBlock[47 - i] = halfBlock[32 - E[i]];
    }
    return expandedBlock;
}

bitset<32> sBoxSubstitution(bitset<48> expandedBlock) {
    bitset<32> substitutedBlock;
    int index = 0;
    for (int i = 0; i < 48; i += 6) {
        int row = expandedBlock[47 - i] * 2 + expandedBlock[47 - i - 5];
        int col = expandedBlock[47 - i - 1] * 8 + expandedBlock[47 - i - 2] * 4 + expandedBlock[47 - i - 3] * 2 + expandedBlock[47 - i - 4];
        int sBoxValue = S[i / 6][row][col];
        bitset<4> sBoxBits(sBoxValue);
        for (int j = 0; j < 4; j++) {
            substitutedBlock[31 - index - j] = sBoxBits[3 - j];
        }
        index += 4;
    }
    return substitutedBlock;
}

bitset<32> permutation(bitset<32> block) {
    bitset<32> permutedBlock;
    for (int i = 0; i < 32; i++) {
        permutedBlock[31 - i] = block[32 - P[i]];
    }
    return permutedBlock;
}

vector<bitset<48>> generateSubkeys(bitset<64> key) {
    vector<bitset<48>> subkeys;
    bitset<56> permutedKey;
    for (int i = 0; i < 56; i++) {
        permutedKey[55 - i] = key[64 - PC1[i]];
    }
    bitset<28> leftHalf;
    bitset<28> rightHalf;
    for (int i = 0; i < 28; i++) {
        leftHalf[27 - i] = permutedKey[55 - i];
        rightHalf[27 - i] = permutedKey[27 - i];
    }
    for (int round = 0; round < 16; round++) {
        leftHalf = (leftHalf << shifts[round]) | (leftHalf >> (28 - shifts[round]));
        rightHalf = (rightHalf << shifts[round]) | (rightHalf >> (28 - shifts[round]));
        bitset<56> combinedKey;
        for (int i = 0; i < 28; i++) {
            combinedKey[55 - i] = leftHalf[27 - i];
            combinedKey[27 - i] = rightHalf[27 - i];
        }
        bitset<48> subkey;
        for (int i = 0; i < 48; i++) {
            subkey[47 - i] = combinedKey[56 - PC2[i]];
        }
        subkeys.push_back(subkey);
    }
    return subkeys;
}

bitset<64> desEncrypt(bitset<64> plainText, bitset<64> key) {
    bitset<64> permutedText = initialPermutation(plainText);
    bitset<32> leftHalf;
    bitset<32> rightHalf;
    for (int i = 0; i < 32; i++) {
        leftHalf[31 - i] = permutedText[63 - i];
        rightHalf[31 - i] = permutedText[31 - i];
    }
    vector<bitset<48>> subkeys = generateSubkeys(key);
    for (int round = 0; round < 16; round++) {
        bitset<32> newRightHalf = leftHalf;
        bitset<48> expandedRightHalf = expansionPermutation(rightHalf);
        expandedRightHalf ^= subkeys[round];
        bitset<32> substitutedBlock = sBoxSubstitution(expandedRightHalf);
        bitset<32> permutedBlock = permutation(substitutedBlock);
        leftHalf = rightHalf;
        rightHalf = newRightHalf ^ permutedBlock;
    }
    bitset<64> combinedText;
    for (int i = 0; i < 32; i++) {
        combinedText[63 - i] = rightHalf[31 - i];
        combinedText[31 - i] = leftHalf[31 - i];
    }
    bitset<64> cipherText = finalPermutation(combinedText);
    return cipherText;
}

int main() {
    bitset<64> plainText(0x0123456789ABCDEF);
    bitset<64> key(0x133457799BBCDFF1);
    bitset<64> cipherText = desEncrypt(plainText, key);
    cout << "Cipher Text: " << hex << cipherText.to_ullong() << endl;
    return 0;
}

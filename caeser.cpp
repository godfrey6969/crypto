#include <iostream>
#include <string>


using namespace std;


string encrypt(string message, int shift) {
    string encryptedMessage = "";
    for (char c : message) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            encryptedMessage += static_cast<char>((c - base + shift) % 26 + base);
        } else {
            encryptedMessage += c;
        }
    }
    return encryptedMessage;
}


string decrypt(string encryptedMessage, int shift) {
    return encrypt(encryptedMessage, 26 - shift);
}

string decryptCaesarCipher(const string& cipherText, int shift) {
    string decryptedText = "";


    for (char c : cipherText) {
        if (isalpha(c)) {
            char decryptedChar = (c - shift - 'A' + 26) % 26 + 'A';
            decryptedText += decryptedChar;
        } else {
            decryptedText += c;
        }
    }


    return decryptedText;
}


void performLetterFrequencyAnalysis(const string& decryptedText) {
    int frequency[26] = {0};


    for (char c : decryptedText) {
        if (isalpha(c)) {
            frequency[toupper(c) - 'A']++;
        }
    }


    cout << "Letter Frequency Analysis:\n";
    for (int i = 0; i < 26; i++) {
        char letter = 'A' + i;
        cout << letter << ": " << frequency[i] << "\n";
    }
}



int main() {
    string message;
    int shift;


    cout << "Enter a message: ";
    getline(cin, message);


    cout << "Enter the shift value: ";
    cin >> shift;


    string encryptedMessage = encrypt(message, shift);
    cout << "Encrypted message: " << encryptedMessage << endl;


    string decryptedMessage = decrypt(encryptedMessage, shift);
    cout << "Decrypted message: " << decryptedMessage << endl;


    return 0;
}

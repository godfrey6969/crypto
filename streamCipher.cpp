#include <bits/stdc++.h>

using namespace std;

string getBinary(int val) {
	string ans;
	while (val > 0) {
    	if (val & 1) {
        	ans = '1' + ans;
    	} else {
        	ans = '0' + ans;
    	}
    	val = val >> 1;
	}
	return ans;
}
string strToBinary(string str) {

	string bin;
	for (char c : str) {
    	int val = c;
    	bin += getBinary(val);
	}
	return bin;
}
string xorBinaryStrings(const string& a, const string& b) {
    string result;
    for (int i = 0; i < a.size(); ++i) {
        result += (a[i] == b[i]) ? '0' : '1';
    }
    return result;
}

string binaryToString(const string& binary) {
    string text;
    for (int i = 0; i < binary.size(); i += 8) {
        bitset<8> byte(binary.substr(i, 8));
        text += static_cast<char>(byte.to_ulong());
    }
    return text;
}


int main() {
	random_device r1;
	string str = "cryptography";
	string bin = strToBinary(str);
	string ans;
	int s = bin.length();
	string key1, key2;
	for (int i = 0; i < s; i++) {

    	char randomBit1 = r1() % 2 ? '1' : '0';
    	char randomBit2 = r1() % 2 ? '1' : '0';
    	key1 += randomBit1;
    	key2 += randomBit2;
	}
	for (int i = 0; i < s; i++) {
    	if (bin[i] == key1[i]) {
        	ans += '0';
    	} else {
        	ans += '1';
    	}
	}
	string finalAns;
	for (int i = 0; i < s; i++) {
    	if (ans[i] == key2[i]) {
        	finalAns += '0';
    	} else {
        	finalAns += '1';
    	}
	}
	cout << finalAns << endl;
	return 0;
}

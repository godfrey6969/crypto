#include <bits/stdc++.h>
using namespace std;

pair<int, int> rsa (int p, int q) {
    int n = p * q;
    int phi = (p - 1) * (q - 1);
    int e = 2;
    while (__gcd(e, phi) != 1) e++;
    int d = 1;
    while ((d * e) % phi != 1) d++;
    return {e, d};
}
int main() {
    int p = 61, q = 53;
    auto keys = rsa(p, q);
    cout << "Public key: " << keys.first << endl;
    cout << "Private key: " << keys.second << endl;
    return 0;
}
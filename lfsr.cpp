#include <iostream>
#include <vector>

using namespace std;

class LFSR {
private:
    vector<int> taps;
    vector<int> state;
    int size;

public:
    LFSR(const vector<int>& feedback_poly, const vector<int>& initial_seed) {
        taps = feedback_poly;
        state = initial_seed;
        size = initial_seed.size();
    }

    int nextBit() {
        int new_bit = 0;
        for (int tap : taps) {
            new_bit ^= state[(size - 1) - tap];
        }
        int out_bit = state.back();
        state.pop_back();
        state.insert(state.begin(), new_bit);
        return out_bit;
    }

    vector<int> generateSequence(int length) {
        vector<int> sequence;
        for (int i = 0; i < length; ++i) {
            sequence.push_back(nextBit());
        }
        return sequence;
    }
};

int main() {
    vector<int> feedback_poly = {0, 3};
    vector<int> initial_seed = {1, 0, 0, 1};

    LFSR lfsr(feedback_poly, initial_seed);

    int n = initial_seed.size();

    vector<int> sequence = lfsr.generateSequence(2 * n);

    cout << "Generated sequence: ";
    for (int bit : sequence) {
        cout << bit;
    }
    cout << endl;

    vector<vector<int>> matrix(n, vector<int>(n + 1, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = sequence[i + j];
        }
        matrix[i][n] = sequence[i + n];
    }

    for (int i = 0; i < n; ++i) {
        if (matrix[i][i] == 0) {
            for (int k = i + 1; k < n; ++k) {
                if (matrix[k][i] == 1) {
                    swap(matrix[i], matrix[k]);
                    break;
                }
            }
        }
        for (int j = i + 1; j < n; j++) {
            if (matrix[j][i] == 1) {
                for (int k = i; k <= n; k++) {
                    matrix[j][k] ^= matrix[i][k];
                }
            }
        }
    }

    vector<int> recovered_poly(n, 0);
    for (int i = n - 1; i >= 0; --i) {
        int sum = matrix[i][n];
        for (int j = i + 1; j < n; ++j) {
            sum ^= (matrix[i][j] & recovered_poly[j]);
        }
        recovered_poly[i] = sum;
    }

    cout << "Recovered feedback polynomial coefficients: ";
    for (int coef : recovered_poly) {
        cout << coef << " ";
    }
    cout << endl;

    vector<int> recovered_state(sequence.begin(), sequence.begin() + n);

    cout << "Recovered initial state: ";
    for (int bit : recovered_state) {
        cout << bit << " ";
    }
    cout << endl;

    return 0;
}

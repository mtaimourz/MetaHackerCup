#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

vector<int> factorize(int x) {
    vector<int> res;
    for (int d = 2; d * d <= x; ++d) {
        while (x % d == 0) {
            res.push_back(d);
            x /= d;
        }
    }
    if (x > 1) res.push_back(x);
    sort(res.begin(), res.end());
    return res;
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    if (!fin.is_open() || !fout.is_open()) return 1;

    int T; fin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        int N, A, B;
        fin >> N >> A >> B;

        vector<int> ans(2 * N, 1);

        if (B == 1) {
            fout << "Case #" << tc << ":";
            for (int v : ans) fout << " " << v;
            fout << "\n";
            continue;
        }

        vector<int> primes = factorize(B);

        long long P = 1;
        vector<int> chosen_indices;
        vector<int> remaining_indices;
        for (int i = 0; i < (int)primes.size(); ++i) {
            int p = primes[i];
            if (P * p <= A) {
                P *= p;
                chosen_indices.push_back(i);
            } else {
                remaining_indices.push_back(i);
            }
        }

        if (chosen_indices.empty()) {
            for (int i = 0; i < (int)primes.size(); ++i) {
                if (primes[i] <= A) {
                    chosen_indices.push_back(i);
                    remaining_indices.erase(remove(remaining_indices.begin(), remaining_indices.end(), i),
                                            remaining_indices.end());
                    P = primes[i];
                    break;
                }
            }
        }

        int slot = N - 1;
        for (int idx = (int)chosen_indices.size() - 1; idx >= 0; --idx) {
            if (slot < 0) slot = 0;
            ans[slot] *= primes[chosen_indices[idx]];
            --slot;
        }

        int pos = N;
        for (int idx : remaining_indices) {
            if (pos > 2 * N - 1) pos = 2 * N - 1;
            ans[pos] *= primes[idx];
            ++pos;
        }

        long long prefix = 1, total = 1;
        for (int i = 0; i < N; ++i) prefix *= ans[i];
        for (int i = 0; i < 2 * N; ++i) total *= ans[i];

        if (prefix > A || total != B) {
            for (int i = 0; i < 2 * N; ++i) ans[i] = 1;
            ans[2 * N - 1] = B;
        }

        fout << "Case #" << tc << ":";
        for (int v : ans) fout << " " << v;
        fout << "\n";
    }

    fin.close();
    fout.close();
    return 0;
}

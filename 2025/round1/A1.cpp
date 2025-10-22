#include <iostream>
#include <fstream>
#include <vector> 
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int T;
    fin >> T;

    for (int t = 1; t <= T; ++t) {
        int N;
        fin >> N;

        vector<int> A(N);
        for (int i = 0; i < N; ++i) fin >> A[i];

        if (N <= 1) {
            fout << "Case #" << t << ": " << 0 << "\n";
            continue;
        }

        int required_ladder = 0;
        for (int i = 0; i + 1 < N; ++i) {
            int diff = abs(A[i+1] - A[i]);
            required_ladder = max(required_ladder, diff);
        }

        fout << "Case #" << t << ": " << required_ladder << "\n";
    }

    fin.close();
    fout.close();
    return 0;
}

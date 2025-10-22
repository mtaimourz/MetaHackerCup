#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int testCases;
    cin >> testCases;

    for (int caseIndex = 1; caseIndex <= testCases; caseIndex++) {
        int arraySize;
        cin >> arraySize;
        vector<int> numbers(arraySize + 1);
        for (int i = 1; i <= arraySize; i++) {
            cin >> numbers[i];
        }

        vector<int> prefixXor(arraySize + 1, 0);
        for (int i = 1; i <= arraySize; i++) {
            prefixXor[i] = prefixXor[i - 1] ^ numbers[i];
        }

        map<int, int> xorFrequency;
        for (int i = 0; i <= arraySize; i++) {
            xorFrequency[prefixXor[i]]++;
        }

        long long subarrayCountToSubtract = 0;
        for (auto& entry : xorFrequency) {
            long long frequency = entry.second;
            subarrayCountToSubtract += frequency * (frequency * frequency - 1) / 6;
        }

        long long totalSubarrays = (long long)arraySize * (arraySize + 1) * (arraySize + 2) / 6;
        long long answer = totalSubarrays - subarrayCountToSubtract;

        cout << "Case #" << caseIndex << ": " << answer << '\n';
    }

    return 0;
}
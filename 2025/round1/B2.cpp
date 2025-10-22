#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>

using namespace std;

const long long MOD = 1000000007;
const int MAX_FACTORIAL = 150;

vector<long long> factorial;
vector<long long> invFactorial;

long long modPow(long long base, long long exponent, long long mod) {
    long long result = 1;
    base %= mod;
    while (exponent > 0) {
        if (exponent & 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exponent >>= 1;
    }
    return result;
}

long long modInverse(long long number, long long mod) {
    return modPow(number, mod - 2, mod);
}

void precomputeFactorials(int n) {
    factorial.resize(n + 1);
    invFactorial.resize(n + 1);
    factorial[0] = 1;
    for (int i = 1; i <= n; i++) {
        factorial[i] = (factorial[i - 1] * i) % MOD;
    }
    invFactorial[n] = modInverse(factorial[n], MOD);
    for (int i = n - 1; i >= 0; i--) {
        invFactorial[i] = (invFactorial[i + 1] * (i + 1)) % MOD;
    }
}

long long nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return (factorial[n] * invFactorial[r] % MOD) * invFactorial[n - r] % MOD;
}

long long combinationLargeN(long long exponent, long long n) {
    if (exponent == 0) return 1;
    long long result = 1;
    for (int i = 1; i <= exponent; i++) {
        long long term = ((n - 1 + exponent - i + 1) % MOD + MOD) % MOD;
        result = (result * term) % MOD;
        result = (result * modInverse(i, MOD)) % MOD;
    }
    return result;
}

vector<pair<long long, int>> factorizeNumber(long long number) {
    vector<pair<long long, int>> primeFactors;
    if (number % 2 == 0) {
        int count = 0;
        while (number % 2 == 0) {
            number /= 2;
            count++;
        }
        primeFactors.push_back({2, count});
    }
    for (long long i = 3; i * i <= number; i += 2) {
        if (number % i == 0) {
            int count = 0;
            while (number % i == 0) {
                number /= i;
                count++;
            }
            primeFactors.push_back({i, count});
        }
    }
    if (number > 1) {
        primeFactors.push_back({number, 1});
    }
    return primeFactors;
}

vector<long long> getDivisors(const vector<pair<long long, int>>& primeFactors, long long maxLimit) {
    vector<long long> divisors = {1};
    for (auto& [prime, exponent] : primeFactors) {
        int currentSize = divisors.size();
        long long power = 1;
        for (int i = 0; i < exponent; i++) {
            power *= prime;
            for (int j = 0; j < currentSize; j++) {
                long long newDivisor = divisors[j] * power;
                if (newDivisor <= maxLimit) {
                    divisors.push_back(newDivisor);
                }
            }
        }
    }
    return divisors;
}

long long computeSequenceCount(const vector<pair<long long, int>>& primeFactors, long long sequenceLength) {
    long long result = 1;
    for (auto& [prime, exponent] : primeFactors) {
        result = (result * combinationLargeN(exponent, sequenceLength)) % MOD;
    }
    return result;
}

long long computeSequenceCount(long long number, long long sequenceLength, const vector<pair<long long, int>>& baseFactors) {
    vector<pair<long long, int>> primeFactors;
    long long temp = number;
    for (auto& [prime, baseExponent] : baseFactors) {
        int exponent = 0;
        while (temp % prime == 0) {
            temp /= prime;
            exponent++;
        }
        if (exponent > 0) {
            primeFactors.push_back({prime, exponent});
        }
    }
    return computeSequenceCount(primeFactors, sequenceLength);
}


int main() {
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");
    
    precomputeFactorials(MAX_FACTORIAL);
    
    int testCases;
    inputFile >> testCases;
    
    for (int caseIndex = 1; caseIndex <= testCases; caseIndex++) {
        long long sequenceLength, maxA, numberB;
        inputFile >> sequenceLength >> maxA >> numberB;
        
        if (numberB == 1) {
            if (maxA >= 1) {
                outputFile << "Case #" << caseIndex << ": " << 1 << endl;
            } else {
                outputFile << "Case #" << caseIndex << ": " << 0 << endl;
            }
            continue;
        }
        
        vector<pair<long long, int>> baseFactors = factorizeNumber(numberB);
        vector<long long> divisors = getDivisors(baseFactors, maxA);
        
        long long totalCount = 0;
        for (long long divisor : divisors) {
            if (numberB % divisor != 0) continue;
            
            long long complementaryDivisor = numberB / divisor;
            
            long long count1 = computeSequenceCount(divisor, sequenceLength, baseFactors);
            long long count2 = computeSequenceCount(complementaryDivisor, sequenceLength, baseFactors);
            
            totalCount = (totalCount + count1 * count2 % MOD) % MOD;
        }
        
        outputFile << "Case #" << caseIndex << ": " << totalCount << endl;
    }
    
    inputFile.close();
    outputFile.close();
    return 0;
}

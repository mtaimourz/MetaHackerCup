#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int T;
    fin >> T;
    for (int t = 1; t <= T; t++) {
        long long n;
        fin >> n;
        vector<int> temps;
        vector<int> target;

        int k = 2;
        while (k) {
            for (int i = 0; i < n; i++) {
                int temp;
                fin >> temp;
                if (k == 2) temps.push_back(temp);
                else target.push_back(temp);
            }
            k--;
        }

        // check if impossible
        bool impossible = false;
        for (int i = 0; i < target.size(); i++) {
            if (target[i] < temps[i]) {
                impossible = true;
                break;
            }
        }

        if (impossible) {
            fout << "Case #" << t << ": -1" << endl;
        } else {
            // find unique target values
            vector<int> unique_targets = target;
            sort(unique_targets.begin(), unique_targets.end());
            unique_targets.erase(unique(unique_targets.begin(), unique_targets.end()), unique_targets.end());

            vector<pair<int, int>> ops;

            // loop through each unique temperature value
            for (int u = 0; u < unique_targets.size(); u++) {
                int value = unique_targets[u];

                // find source dish which already has this temperature
                int source_index = -1;
                for (int i = 0; i < n; i++) {
                    if (temps[i] == value) {
                        source_index = i;
                        break;
                    }
                }

                // if we need this temp but no source exists, it's impossible
                bool need_value = false;
                for (int i = 0; i < n; i++) {
                    if (target[i] == value && temps[i] < value) {
                        need_value = true;
                        break;
                    }
                }

                if (need_value && source_index == -1) {
                    impossible = true;
                    break;
                }

                // perform operations for dishes needing this temp
                if (source_index != -1) {
                    for (int i = 0; i < n; i++) {
                        if (target[i] == value && temps[i] < value) {
                            ops.push_back({source_index + 1, i + 1});
                            temps[i] = value; // update temps
                        }
                    }
                }
            }

			fout << "Case #" << t << ": " << ops.size() << endl;
			for (int i = 0; i < ops.size(); i++) {
				fout << ops[i].first << " " << ops[i].second << endl;
			}
        }
    }

    fin.close();
    fout.close();
    return 0;
}

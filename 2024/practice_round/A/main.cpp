#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

   int T;
   fin>>T;
   for(int t = 1; t<=T; t++){
	long long n,k;
	fin>>n>>k;
	vector<long long> a(n);
	long long totalTime = 0;
	for(int i = 0 ; i < n; i++) fin>>a[i];
	sort(a.begin(), a.end());
	if(n==1) totalTime=a[0];
	else totalTime = (2LL*n-3LL)*a[0]; // --> 2(n-2)a_0+a_0=2na-4a+a=2na-3a=(2n-3)a
	fout << "Case #"<<t<<": ";
	if(totalTime<=k)
	fout << "YES";
	else fout <<"NO";
        fout <<endl;
   }


    fin.close();
    fout.close();
    return 0;
}

#include <bits/stdc++.h>
using namespace std;



int main()
{
	int t; cin >> t;
	while(t--)
	{
		int n,k; cin >> n >> k;
		int kk = k;
		if(k%n == 0) cout << k/n << endl;
		else{
			while(k <= n) k+=kk;
			if(k%n == 0) cout << k/n << endl;
			else	     cout << k/n + 1 << endl;
		}
	}
}

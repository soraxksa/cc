#include <bits/stdc++.h>
using namespace std;

 
bool isPalin(string &s, int left, int right)
{
	cout << "isPalin: left:" << left << " right" << right << endl;
	if(left >= right)
	    return true;
	if(s[left] == s[right])
	{
	    return isPalin(s, ++left, --right);
	}else
	    return false;
}                                       

string longestPalindrome(string s) {

        int max_str_len = 1;
        int left        = 0;
        int right       = 0;
        for(int i = 0; i < s.size()-1; i++)
        {
            for(int k = s.size()-1; k > i; k--)
            {
		cout << "left:" << i << " right:" << k << endl;
                if(isPalin(s, i, k))
                {
                    if(k-i+1 > max_str_len)
                    {
                        left  = i;
                        right = k;
			
                    }
                    break;
                }
            }
        }
        return s.substr(left, right-left+1);
}




int main()
{
	string test; cin >> test;
	cout << longestPalindrome(test);
}

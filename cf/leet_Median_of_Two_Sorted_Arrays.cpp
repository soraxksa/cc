#include <bits/stdc++.h>
using namespace std;


double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
	vector<int> a, b;
	if(nums1[nums1.size()-1] > nums2[nums2.size()-1])
	{
		a = std::move(nums2);
		b = std::move(nums1);
	}else{
		a = std::move(nums1);
		b = std::move(nums2);
	}

}



int main()
{

}

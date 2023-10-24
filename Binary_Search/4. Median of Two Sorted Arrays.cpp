/*
4. Median of Two Sorted Arrays 
*/

// TC:O(lgn) SC:O(1)
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        if((m+n)%2 == 1) return FindKthSmallest(nums1,0,nums2,0,(m+n)/2+1);
        else return (FindKthSmallest(nums1,0,nums2,0,(m+n)/2) + FindKthSmallest(nums1,0,nums2,0,(m+n)/2+1))*1.0/2;
    }

    int FindKthSmallest(vector<int>& nums1, int a, vector<int>& nums2, int b, int k){
        //base case
        int m = nums1.size();
        int n = nums2.size();

        if(m-a > n-b) return FindKthSmallest(nums2,b,nums1,a,k);
        if(a == m) return nums2[b+k-1];
        if(k == 1) return min(nums1[a],nums2[b]);


        int k1,k2;
        if(a+k/2 >= m){
            k1 = m-a;
        }
        else k1 = k/2;
        k2 = k-k1;

        if(nums1[a+k1-1] > nums2[b+k2-1]){
            return FindKthSmallest(nums1,a,nums2,b+k2, k-k2);
        }
        else return FindKthSmallest(nums1,a+k1,nums2,b, k-k1);
    }
};

/*
此題是binary search 思想加上遞歸求解題
ex: 求兩個數組的中位數 開始比他們的大小
如果x大 那就把y的那堆全部加入大的幫派繼續遞歸 這次要遞歸的數量就會減去加進來的數目
[xxxxx x0 xxxxx] m
[yyyyy {y0 yyyyyy}]n
(m+n)/2 = k k-k/2
*/

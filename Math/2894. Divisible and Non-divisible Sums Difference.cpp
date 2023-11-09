/*
2894. Divisible and Non-divisible Sums Difference
*/

// TC:O(m*n) SC:O(n)
class Solution {
public:
    int differenceOfSums(int n, int m) {

        vector<bool> nums1(n+1,1);
        int res1 = 0;
        int res2 = 0;
        for(int i = m; i<=n;i++){
            for(int j = 1; j*m<=n; j++){
                nums1[m*j] = false;
            }
        }
        for(int i = 1; i<= n; i++){
            if(nums1[i] == false){
                res1+=i;
            }
            if(nums1[i] == true){
                res2+=i;
            }
        }
        
        return res2-res1;
    }
};

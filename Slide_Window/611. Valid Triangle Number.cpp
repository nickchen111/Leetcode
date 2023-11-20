/*
611. Valid Triangle Number
*/


// TC:O(nlgn+n) SC:O(1)
class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        //只要兩邊之和大於第三邊即可
        sort(nums.begin(),nums.end());
        if(nums.size() < 3) return 0;
        //三指針太麻煩了每次固定一個k會好寫很多
        int res=0;
        for(int k = nums.size()-1; k>=2; k--){
            int i = 0; int j = k-1;
            while(i < j){
                if(nums[i]+nums[j] > nums[k]){
                    res+= (j-i);
                    j--;
                }
                else i++;
            }
        }

        return res;

    }
}; 

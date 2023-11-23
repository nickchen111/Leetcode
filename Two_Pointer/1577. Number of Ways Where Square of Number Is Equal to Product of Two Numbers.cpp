/*
1577. Number of Ways Where Square of Number Is Equal to Product of Two Numbers
*/

// Two pointer
class Solution {
public:
    int numTriplets(vector<int>& nums1, vector<int>& nums2) {
        //各做一次
        sort(nums1.begin(),nums1.end());
        sort(nums2.begin(),nums2.end());
        int res = 0;
        for(int i = 0; i<nums1.size(); i++){
            long long target = (long long)nums1[i]*nums1[i];
            int left = 0; int right = nums2.size()-1;
            while(left < right){
                long long cur = (long long)nums2[left]*nums2[right];
                if(cur > target){
                    right--;
                }
                else if(cur < target){
                    left++;
                }
                else {
                    if(nums2[left] != nums2[right]){
                        int left0 = left; int right0 = right;
                        while(left+1 < right && nums2[left] == nums2[left+1]) left++;
                        while(right-1 > left && nums2[right] == nums2[right-1]) right--;

                        res+=(left-left0+1)*(right0-right+1);
                        left++; right--;
                    }
                    else {
                        int t = right-left+1;
                        res+=(t*(t-1)/2);
                        break;
                    }
                }
            }
        }
        for(int i = 0; i<nums2.size(); i++){
            long long target = (long long)nums2[i]*nums2[i];
            int left = 0; int right = nums1.size()-1;
            while(left < right){
                long long cur = (long long)nums1[left]*nums1[right];
                if(cur > target){
                    right--;
                }
                else if(cur < target){
                    left++;
                }
                else {
                    if(nums1[left] != nums1[right]){
                        int left0 = left; int right0 = right;
                        while(left+1 < right && nums1[left] == nums1[left+1]) left++;
                        while(right-1 > left && nums1[right] == nums1[right-1]) right--;

                        res+=(left-left0+1)*(right0-right+1);
                        left++; right--;
                    }
                    else {
                        int t = right-left+1;
                        res+=(t*(t-1)/2);
                        break;
                    }
                }
            }
        }

        return res;
    }
};

//Hash map 暴力解 TC:O(m*n) SC:O(m+n)
class Solution {
public:
    int numTriplets(vector<int>& nums1, vector<int>& nums2) {
        int res = 0;
        res+=helper(nums1,nums2);
        res+=helper(nums2,nums1);

        return res;
    }

    int helper(vector<int>& nums1, vector<int>& nums2){
        int res = 0;
        for(auto x:nums1){
            long long target = (long long)x*x;
            unordered_map<long long,int> map; // val->freq;
            for(int i = 0; i<nums2.size(); i++){
              //查找會在i之前的
                if(target%nums2[i] == 0){
                    res+=map[target/nums2[i]];
                }
                map[nums2[i]]+=1;
            }
        }

        return res;
    }
};

/*
O(2*(m+n)+nlgn+mlgm)
nums1 = [3 7 7 8], nums2 = [1,2,7,9]
[1,1,1] -> 6 c3 取2 3個
[1 1 1 1] -> c4取2 4*3/2->6個
*/

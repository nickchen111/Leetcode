/*
2541. Minimum Operations to Make Array Equal II
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    long long minOperations(vector<int>& nums1, vector<int>& nums2, int k) {
        int n = nums1.size();
        if(k == 0) return (nums1 == nums2) ? 0:-1;
        vector<int> arr;
        long long diff = 0;
        long long res = 0;
        for(int i = 0; i < n; i++){
            if((nums1[i] - nums2[i]) % k == 0){
                arr.push_back( (nums1[i] - nums2[i])/k );
                diff += arr.back();
                if(arr.back() > 0) res += arr.back();
            }

            else return -1;
        }

        if(diff != 0) return -1;
        else return res;
    }
};

/*
將兩個數組內的元素 變成相同 
可以將第一個數組 + k 另一個數字就要減k
-> nums2[j] - nums1[i] = 2*k
-> nums2[j] == nums1[i] + 2*k
將他跟nums2的差值 % k試試看 如果不行就-1
可以的話就紀錄差值倍數
這樣一來 一個人要想要 + 2 就要找-2的 那麼如果所有數組的值加起來為0 就代表可以  -> 計算 這之中數字正數加總為多少 
*/

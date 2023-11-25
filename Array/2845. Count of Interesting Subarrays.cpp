/*
2845. Count of Interesting Subarrays
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    long long countInterestingSubarrays(vector<int>& nums, int modulo, int k) {
        int n = nums.size();
        int count = 0;

        long long res = 0;
        unordered_map<int, long long> map; //餘數->次數
        map[0] = 1;
        for(int i = 0; i<n; i++){
            count+= (nums[i]%modulo) == k;
            int k1 = count%modulo;
            int k2 = ((k1-k)+modulo)%modulo;
            res+=map[k2];
            map[k1]+=1;
        }

        return res;
    }
};

/*
[x x x x [i x x x j ]x x x]
            k
            總共取餘k1
            需要前面的 k1-k

*/

/*
3164. Find the Number of Good Pairs II
*/

// TC:O(n+m + p*qlglgq) p 為過濾nums1後可以被k整除的數 q為這些數字的平均值 SC:O(n + p)
class Solution {
    using LL = long long;
public:
    long long numberOfPairs(vector<int>& nums1, vector<int>& nums2, int k) {
       
        LL goodpairs = 0;
        unordered_map<int, int> map;
        for(auto num : nums2) {
            map[num] += 1;
        }
        
        vector<int> nums;
        for(auto num : nums1){
            if(num % k == 0){
                nums.push_back(num/k);
            }
        }
        
        for(auto num : nums){
            for(int d = 1; d*d <= num; d++){
                if(num % d == 0){
                    if(map.find(d) != map.end()){
                        goodpairs += map[d];
                    }
                    if(d != num/d && map.find(num/d) != map.end()){
                        goodpairs += map[num/d];
                    }
                }
            }
        }
        
        return goodpairs;
    }
};

/*
會想把nums1 數字拆解 然後看nums2 有多少個這樣的數字
nums1 要大於等於 nums2 才有機會整除
nums1做 因數分解 然後看nums2有沒有這些數字
這一堆數字去做分解
*/

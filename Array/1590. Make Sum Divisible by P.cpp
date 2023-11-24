/*
1590. Make Sum Divisible by P
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int minSubarray(vector<int>& nums, int p) {
        int total =0;
        for(auto num:nums){
            total = (total + num)%p;
        }

        
        unordered_map<int, int> map; // val->index
        map[0] = -1; //一開始什麼都沒有被P除餘0
        long presum = 0;
        int r0 = total%p;
        if(r0 == 0) return 0;
        int res = INT_MAX;
        for(int j = 0; j<nums.size(); j++){
            presum+=nums[j];
            int r = presum%p;
            int rr = (r-r0+p)%p;//防止負數
            if(map.find(rr) != map.end()){
                int i = map[rr]+1;
                res = min(res, j-i+1);
            }
            map[r] = j;
        }

        if(res < nums.size()) return res;
        else return -1;
    }
};

/*
此題是否變相的在問 subarray最長可以滿足
[x x x x[ x x x] x x ]
其他段被p除為零 他被p除要是 sum%p 去找最小的一段
r0 = total%p
[x x x x [i x x j] x x ]
sum[i:j] = presum[j] - presum[i-1];
 r0         r           r-r0
  3.         1.          1-2. +5
希望i 越貼近 j越好
*/

/*
2411. Smallest Subarrays With Maximum Bitwise OR
*/

// TC:O(96*n) SC:O(32)
class Solution {
public:
    vector<int> smallestSubarrays(vector<int>& nums) {
        int n = nums.size();
        vector<int> count(32,0);
        int j = n-1;
        vector<int> res(n);
        for(int i = n-1; i>=0; i--){
            for(int k = 0; k<32; k++){
                count[k]+=((nums[i]>>k)&1);
            }
            while(j > i && isOkRemove(nums[j],count)){
                for(int k =0; k<32; k++){
                    count[k]-=((nums[j]>>k)&1);
                }
                j--;

            }
            res[i] = j-i+1;
        }
        return res;
    }

    bool isOkRemove(int num, vector<int>& count){
        for(int i = 0; i<32; i++){
            if(count[i] == 1 && ((num>>i)&1)) return false;
        }
        return true;
    }
};

// TC:O(64*n) SC:O(32) 2/29
class Solution {
public:
    vector<int> smallestSubarrays(vector<int>& nums) {
        int n = nums.size();
    
        vector<int> count(32,0);
        for(int i = 0; i < n; i++){
            int cur = nums[i];
            int k = 0;
            while((cur >> k) !=  0){
                int now = (cur>>k)&1;
                if(now) count[k] += 1;
                k++;
            }
        }

        int need = 0;
        for(int i =0; i < 32; i++){
            if(count[i] != 0) need += 1;
        }
        
        vector<int> Count(32,0);
        vector<int> res(n,1);
        int j = 0;
        int curNeed = 0;
        for(int i = 0; i < n; i++){
            while(j < n && curNeed < need){
                int k = 0;
                while((nums[j]>>k) != 0){
                    int now = (nums[j]>>k)&1;
                    if(now){
                        Count[k] += 1;
                        if(Count[k] == 1) curNeed += 1;
                    }
                    k++;
                }
                j++;
            }
            if(need == 0){
                res[i] = 1;
            }
            else if(curNeed == need){
                res[i] = (j-i);
            }
            int k = 0;
            int cur = nums[i];
            while((cur >> k) != 0){
                int now = (cur>>k)&1;
                if(now){
                    count[k] -= 1;
                    Count[k] -= 1;
                    if(count[k] == 0) need -= 1;
                    if(Count[k] == 0) curNeed -= 1;
                }
                k++;
            }
        }

        return res;
    }
};


/*
以每個元素作為左邊界 去找右邊的subarray使他的OR運算盡量大 但是subarray盡量短
要從最右邊開始做 這樣才不用重複做 時間複雜度才會是線性
*/

/*
370. Range Addition 🔒
假設有一個長度為n的數組 初始化為0 對他進行k次操作 每一次的操作就類似 [1,3,2] 要你對index 1到3 去加上2 
請返回k次操作後數組的結果
*/


class Solution{
public:
    vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
        vector<int> nums(length, 0); //初始化題目要求的原始數組

        Difference df(nums);//建立差分數組
        
        for(auto update:updates){ //執行加加減減k次操作
            int i = update[0];
            int j = update[1];
            int val = update[2];

            df.increment(i, j, val);
        }

        return df.result();
    }
private:
    class Difference {
        vector<int> diff;
    public:
        assert(nums.size() > 0);
        Difference(vector<int>& nums){
            diff = vector<int>(nums.size(), 0);

            diff[0] = nums[0]; 
            for(int i = 1; i < nums.size(); i++){
                diff[i] = nums[i] - nums[i-1];
            }
        }
    
        void increment(int i, int j, int val){
             diff[i] += val;

            if(j+1 < diff.size()){
                 diff[j+1] -=val;
            }
         }

        vector<int> result(){
             vector<int> ans(diff.size(), 0);//初始化答案數組
             ans[0] = diff[0];

            for(int i = 1; i < diff.size(); i++){
                ans[i] = ans[i-1] + diff[i];
            }
            return ans;
        }
    };
};


/*
解題思維：
求區段加加減減->使用差分數組
*/

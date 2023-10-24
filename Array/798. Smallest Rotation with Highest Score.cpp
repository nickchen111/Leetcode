/*
798. Smallest Rotation with Highest Score
*/

//此題為單獨考量每個元素在走k步之後的狀況 並且在將結果遍歷相加 得出走幾步會有最大值的diff差分數組的應用題
//TC:O(n) SC:O(n)
class Solution {
public:
    int bestRotation(vector<int>& nums) {
        int n = nums.size();
        vector<int> diff(n, 0);

        for(int i = 0; i < n; i++){
            if(nums[i] > i){
                diff[0] += 0;
                diff[(i+1)%n] +=1;
                diff[(i+1+n-nums[i])%n] -=1;
            }
            if(nums[i] <= i){
                diff[0] += 1;
                diff[(i-nums[i]+1)%n] -=1;
                diff[(i+1)%n]+=1;
            }
        }
        int res = 0;//需要走幾步會是最大值
        int sum = 0;
        int K = 0;
        for(int i = 0; i < n; i++){
            sum +=diff[i];
            if(sum > res){
                res = sum;
                K = i;
            }
        }

        return K;

    }
};


/*
index: 0123456
       xx4x2xx
case1: nums[i] <= i
diff[0] 還沒位移時 +=1;
要移到nums[i]-1的位置開始會減少
diff[i-nums[i]+1] -=1;
移到後面開始比我大的時候會在+1
diff[i+1]+=1;

case2: nums[i] > i
diff[0] += 0;
diff[i+1] +=1;
diff[i+1+[(n-1)-(nums[i]-1)]] = diff[i+1+n-nums[i]] -=1;
*/

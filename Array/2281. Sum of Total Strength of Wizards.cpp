/*
2281. Sum of Total Strength of Wizards
*/

// TC:O(n) SC:(n)
class Solution {
    using LL = long long;
    LL M = 1e9+7;

public:
    int totalStrength(vector<int>& nums) {
        int n = nums.size();
        nums.insert(nums.begin(),0);

        vector<LL> presum(n+2,0);
        for(int i = 1; i<=n; i++){
            presum[i] = (presum[i-1]+(LL)nums[i])%M;
        }

        vector<LL> presum2(n+2,0);
        for(int i = 1; i<=n; i++){
            presum2[i] = (presum2[i-1]+(LL)nums[i]*i)%M;
        }
        stack<int> s;
        vector<int> nextSmaller(n+2,n+1);
        vector<int> prevSmaller(n+2,0);

        for(int i = 1; i<=n; i++){
            while(!s.empty() && nums[s.top()] > nums[i]){
                nextSmaller[s.top()] = i;
                s.pop();
            }
            if(!s.empty()) prevSmaller[i]=s.top();
            s.push(i);
        }

        LL res = 0;
        for(int i = 1; i<=n; i++){
            LL a = prevSmaller[i]; LL b = nextSmaller[i];
            LL x = i-a; LL y = b-i;
            LL left = (presum2[i-1]-presum2[a]-(presum[i-1]-presum[a])*a%M+M)%M; // +M是怕相減超過
            LL right = (presum[b-1]-presum[i])*b%M-(presum2[b-1]-presum2[i]+M)%M;
            LL mid = nums[i]*x*y%M;
            res = (res+(left*y%M+right*x%M+mid)*nums[i])%M;
        } 
        return res;
    }
};

/*
不可能遍歷所有的subarray
而是遍歷所有裡面的元素 看能否有什麼更高效的解法

x x x x x i x x x x x 
  a 1 2 3 i 3 2 1 b

nums[a] = previous smaller than i 
nums[b] = next smaller than i 
x = i-a;
y = b-i;
左右邊界只能做xy內滑動 可能性就有x*y
res[i]= 
nums[i]*
{(nums[a+1]*1+nums[a+2]*2+nums[a+3]*3)*y  
+ (nums[i+1]*3+nums[i+2]*2+nums[i+3]*1)*x
+ nums[i]*x*y}

這個要怎麼求呢 看起來與係數正相關 前綴和？
presum2[i] = presum2[1]*1+presum2[2]*2+...有係數的前綴和
presum2[i-1]-presum2[a] = nums[a+1]*(a+1)+nums[a+2]*(a+2)+nums[a+3]*(a+3)
跟我們想要的只差一點!
即只差 presum2[i-1]-presum2[a]-sum[a+1:i-1]*a

presum2[b-1]-presum2[i]= nums[i+1]*(i+1)+nums[i+2]*(i+2)+nums[i+3]*(i+3)
有類似互補的關係 sum[i+1:b-1]*b-上面那串
*/

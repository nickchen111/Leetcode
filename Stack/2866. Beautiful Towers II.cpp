/*
2866. Beautiful Towers II
*/

// TC:O(n+lgn) SC:O(n)
class Solution {
    using LL = long long;
public:
    long long maximumSumOfHeights(vector<int>& maxHeights) {
        maxHeights.insert(maxHeights.begin(),0);
        maxHeights.push_back(0);
        vector<LL> left = helper(maxHeights);
        
        //算右邊因為函式是正著遍歷所以先倒過來
        reverse(maxHeights.begin(),maxHeights.end());
        vector<LL> right = helper(maxHeights);
        reverse(right.begin(),right.end());
        reverse(maxHeights.begin(),maxHeights.end());

        LL res =0;
        for(int i = 0; i<maxHeights.size(); i++){
            res = max(res, left[i]+right[i]-maxHeights[i]);
        }

        return res;

    }
    vector<LL> helper(vector<int>& H){
        stack<int> stack;
        vector<LL> arr(H.size());
        stack.push(0);
        LL sum = 0;
        for(int i = 1; i < H.size(); i++){
            while(!stack.empty() && H[stack.top()] > H[i]){
                int p1 = stack.top();
                stack.pop();
                int p2 = stack.top();
                sum-=(p1-p2)*(LL)H[p1];
            }
            sum+=(LL)(i-stack.top())*(LL)H[i];
            arr[i] = sum;
            stack.push(i);
        }

        return arr;
    }
};

/*
three pass單調棧
每次維護單調棧的時候實際上都是在維護走到i將i當作頂的時候可以達成的最多塔高
另外此題需要注意刪掉某些小塔補上等高的目前塔時 如果他之後又被其他人取代 要利用idx來合理算出要刪掉多少增加多少
[p2 x x x p1 largeNum]-> (p1-p2)*nums[s.top()] + (i-p2)*nums[i]
*/

/*
2334. Subarray With Elements Greater Than Varying Threshold
*/


// TC:O(n) SC:O(n)
class Solution {
public:
    int validSubarraySize(vector<int>& nums, int threshold) {
        //此題的概念跟84題一樣 求最大矩形即可
        nums.push_back(-1);
        nums.insert(nums.begin(),-1);
        int n = nums.size();
        stack<int> s;
        for(int i = 0; i<n; i++){
            while(!s.empty() && nums[s.top()] > nums[i]){
                int h = nums[s.top()];
                s.pop();
                int w = i-s.top()-1;
                int area = h*w;
                if(area > threshold) return (i-s.top()-1);
            }
            s.push(i);
        }
        return -1;
    }
};

// Stack單調棧two pass TC:O(n) SC:O(n)
class Solution {
    using LL = long long;
public:
    int validSubarraySize(vector<int>& nums, int threshold) {
        int n = nums.size();
        stack<int> stack;
        vector<int> nxtSmaller(n,n);
        for(int i = n-1; i >= 0; i--) {
            while(!stack.empty() && nums[stack.top()] >= nums[i]) stack.pop();
            if(!stack.empty()) nxtSmaller[i] = stack.top();
            stack.push(i);
        }
        while(!stack.empty()) stack.pop();
        vector<int> prevSmaller(n, -1);
        for(int i = 0; i < n; i++) {
            while(!stack.empty() && nums[stack.top()] >= nums[i]) stack.pop();
            if(!stack.empty()) prevSmaller[i] = stack.top();
            stack.push(i);
        }
        for(int i = 0; i < n; i++) {
            LL curVal = nums[i];
            // x x x x x 
            LL len = nxtSmaller[i] - prevSmaller[i] - 1;
            if(curVal * len > threshold) return len;
        }
        return -1;
    }
};

// 長度越長 越容易符合 越短越不容易 但是越長要包含的數字越多 這樣也不一定比較好
// 所以根據題目給的思維 我去枚舉合法狀況的最大數字是哪個 如果它所包含的區間 他就是最小的 該thre / 區間的長度 < 最小數字 就會是答案

// Union Find TC:O(n * ⍺(n)) SC:O(n)
class Solution {
    using LL = long long;
public:
    int validSubarraySize(vector<int>& nums, int threshold) {
        int n = nums.size();
        int fa[n + 1], sz[n + 1];
        iota(fa, fa + n + 1, 0);
        memset(sz, 0, sizeof(sz));
        function<int(int)> find = [&](int x) -> int { return fa[x] == x ? x : fa[x] = find(fa[x]); };

        int ids[n];
        iota(ids, ids + n, 0);
        sort(ids, ids + n, [&](int i, int j) { return nums[i] > nums[j]; });
        for (int i : ids) {
            // cout << "當前index:" << i << " 他的下一個index的pa:" << find(i+1) <<  endl;
            int j = find(i + 1);
            fa[i] = j;
            sz[j] += sz[i] + 1;
            if (nums[i] > threshold / sz[j]) return sz[j];
        }
        return -1;
    }
};

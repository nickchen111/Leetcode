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

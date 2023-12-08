/*
2208. Minimum Operations to Halve Array Sum
*/

// TC:O(nlgn) SC:O(n)
class Solution {
public:
    int halveArray(vector<int>& nums) {
        int n = nums.size();

        double total = 0.0;
        priority_queue<double, vector<double>, less<double>> pq;
        for(auto num : nums){
            total += num;
            pq.push(num);
        }
        double target = total/2.0;

        double sum = 0;
        int count = 0;
        while(sum < target){
            double num = pq.top();
            pq.pop();
            double cur = num/2.0;
            sum += cur;
            count += 1;
            pq.push(cur);
        }

        return count;
    }
};

/*
此題說給你一個數組 每次你可以挑任意數字減一半 至少要多少次你減去的量才會大於等於原本sum的一半
-> greedy + PQ 通常都會想先選大的 
*/


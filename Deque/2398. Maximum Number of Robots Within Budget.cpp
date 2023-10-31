/*
2398. Maximum Number of Robots Within Budget
*/


// TC:O(n) SC:O(n)
class Solution {
public:
    int maximumRobots(vector<int>& chargeTimes, vector<int>& runningCosts, long long budget) {
        //滑窗 用deque維護最大值 從charge 中選出最大的 加上k*所有running time並且不能超過budget
        int n = chargeTimes.size();
        deque<int> dq;
        int res = 0;
        long long sum = 0;
        int i = 0;
        int j = 0;
        while(j < n){
            //如果我們累加的值超過budget 就要i++ or 如果最大的charge變了也要改dq的值
            while(!dq.empty() && chargeTimes[dq.back()] < chargeTimes[j]){
                dq.pop_back();
            }
            sum+=runningCosts[j];
            dq.push_back(j);
            while(!dq.empty() && (j-i+1)*sum+chargeTimes[dq.front()] > budget){
                sum-=runningCosts[i];
                if(dq.front() == i) dq.pop_front();
                i++;
            }

            if(!dq.empty() && (j-i+1)*sum+chargeTimes[dq.front()]) res = max(res, j-i+1);
            j++;
        }

        return res;
    }
};

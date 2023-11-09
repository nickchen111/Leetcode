/*
2895. Minimum Processing Time
*/

// TC:O(nlgn) SC:O(1)
class Solution {
public:
    int minProcessingTime(vector<int>& processorTime, vector<int>& tasks) {
        sort(processorTime.begin(),processorTime.end());
        sort(tasks.begin(),tasks.end());
        int m = processorTime.size();
        int n = tasks.size();
        
        int res = 0;
        int j = 0;
        for(int i = m-1; i>=0; i--){
            if(j < n) res = max(res,processorTime[i]+tasks[j]);
            j++;
            if(j < n) res = max(res,processorTime[i]+tasks[j]);
            j++;
            if(j < n) res = max(res,processorTime[i]+tasks[j]);
            j++;
            if(j < n) res = max(res,processorTime[i]+tasks[j]);
            j++;
        }
        return res;
    }
};

/*
n 個 processor每個有4核心cores 共有n*4個工作
*/

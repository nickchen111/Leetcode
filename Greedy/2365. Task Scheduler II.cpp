/*
2365. Task Scheduler II
*/

// TC:O(n) SC:O(n)
class Solution {
    using LL = long long;
public:
    long long taskSchedulerII(vector<int>& tasks, int space) {
        unordered_map<int, LL> time;
        int n = tasks.size();
        LL cur = 0;
        for(int i = 0; i < n; i++){
            if(time.find(tasks[i]) != time.end()){
                cur = max(cur, time[tasks[i]]);
            }
            time[tasks[i]] = cur + space + 1;//此任務下次可以做的時間
            cur++;
        }

        return cur;//表示天數
    }
};

/*
此題規定任務只能按照順序做 不能自己排序 所以每過一個任務就給他冷凍期 表明他下次可以做的時間
此題跟 Task Scheduler I 比起來簡單很多
*/

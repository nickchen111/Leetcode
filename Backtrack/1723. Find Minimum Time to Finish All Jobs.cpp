/*
1723. Find Minimum Time to Finish All Jobs
*/

// Backtrack + Binary Search TC:O(k*2^n) SC:(2^n)
class Solution {
    int k;
public:
    int minimumTimeRequired(vector<int>& jobs, int k) {
        //貪心的想 分成k等分 盡量讓每等分差不多多 
        //但不知道何時工人不能再接job 用二分搜索來判斷
        this->k = k;
        sort(jobs.begin(),jobs.end());
        reverse(jobs.begin(),jobs.end());
        int left = 1;
        int right = accumulate(jobs.begin(),jobs.end(),0);;
        while(left < right){
            vector<int> worker(k,0);
            int mid = left + (right-left)/2;
            if(backtrack(worker, jobs,0, mid)){
                right = mid;
            }
            else left = mid+1;
        }

        return left;
    }
    bool backtrack(vector<int>& worker, vector<int>& jobs, int cur, int mid){
        if(cur == jobs.size()) return true;
        //如果這個job起頭已經有空閒工人試過但不能返回true那之後的空閒工人也不用再試 大家條件都一樣
        bool flag = 0;
        for(int j = 0; j<k; j++){
            if(worker[j]+jobs[cur] > mid) continue;
            if(worker[j] == 0){
                if(flag == 1){
                    return false;
                }
                else flag = 1;
            }
            worker[j]+=jobs[cur];
            if(backtrack(worker,jobs,cur+1,mid)) return true;
            worker[j]-=jobs[cur];
        }

        return false;
    }
};


//狀態壓縮DP  TC:O(k*3^n) SC: O(k*3^n) 
class Solution {
    int dp[13][4096]; // 4096 -> 2^12
    int time[4096];
public:
    int minimumTimeRequired(vector<int>& jobs, int k) {
        int n = jobs.size();
        for(int state = 0; state < (1<<n); state++){
            int sum = 0;
            for(int i = 0; i < n; i++){
                if((state>>i)&1){
                    sum += jobs[i];
                }
            }
            time[state] = sum;
        }

        for(int state = 1;  state < (1<<n); state++){
            dp[0][state] = INT_MAX;
        }
        dp[0][0] = 0;

        for(int i = 1; i <= k; i++){
            
            for(int state = 0; state < (1<<n); state++){
                dp[i][state] = INT_MAX;
                for(int subset = state; subset > 0; subset = (subset-1)&state){
                   dp[i][state] = min(dp[i][state], max(dp[i-1][state-subset], time[subset]));
                }
            }
        }

        return dp[k][(1<<n)-1];
    }
};

/*
此題的難點在於 要將工作合理的配置給k個工人 但因為不曉得如何配置最小的最大工作量給各個工人 所以用二分猜值 去看能否以此工作量合理的讓所有工作可完成 此為第一個考點
接下來要想如何剪枝 首先此題已經無法用之前的模板去做 因為要去計算每個工人的工作量何時到上限會又跟如何決定下一個要選誰會很難做 
所以會在每輪循環中 去個別分配工人工作超過就略過 沒有就從他進入循環去試試能否把工作做完
剪枝策略及如果當前某一任務已經被空閒工人做過並且沒人能返回true代表目前這份工作在此工作量分配下無法做完 
*/

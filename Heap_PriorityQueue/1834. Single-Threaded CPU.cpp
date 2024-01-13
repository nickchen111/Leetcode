/*
1834. Single-Threaded CPU
*/

// TC:O(nlgn) SC:O(n)
class Solution {
    using PII = pair<int,int>;
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        int n = tasks.size();
        priority_queue<PII, vector<PII>, greater<PII>> pq; // spendtime, idx
        for(int i = 0; i < n; i++){
            tasks[i].push_back(i);
        }

        sort(tasks.begin(), tasks.end());

        int curTime = 0;
        int idx = 0;//數組順序
        
        vector<int> res;
        while(idx < n){
            // tasks是否到達
            while(idx < n && curTime >= tasks[idx][0]){
                pq.push({tasks[idx][1], tasks[idx][2]});
                idx++;
            }

            if(!pq.empty()){
                curTime += pq.top().first;
                res.push_back(pq.top().second);
                pq.pop();
            }
            //CPU在idle 
            else curTime = tasks[idx][0];
        }
        //剩下的工作都抵達但還來不及CPU做的 並且已經按照所需時間排好序
        while(!pq.empty()){
            res.push_back(pq.top().second);
            pq.pop();
        }

        return res;
    }
};

/*
ith tasks可以在 xxx時間開始做 並且做 xxxx時間可以完成
1. 如果單執行緒CPU idle 沒有工作執行的話 CPU沒事做
2. 如果單執行緒CPU idle 有工作 CPU選執行時間最短的先做 如果執行時間相同 選index小的
CPU排班演算法 規則 : shortest job first -> first come first serve
*/

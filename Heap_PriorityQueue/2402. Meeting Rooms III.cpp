/*
2402. Meeting Rooms III
*/

// TC:O(mlgm + mlgn) SC:O(n + m)
class Solution {
    using LL = long long;
    using PII = pair<LL,int>;
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        
        vector<int> count(n,0);
        //從start time較早的開始排
        sort(meetings.begin(), meetings.end());
        priority_queue<PII, vector<PII>, greater<PII>> pq; //endTime ,id 
        priority_queue<int, vector<int>, greater<int>> rooms;
        for(int i = 0; i < n; i++){
            rooms.push(i);
        }
        int i = 0;
        LL times = meetings[0][0];
        while(i < meetings.size()){
            times = max(times, (LL)meetings[i][0]);
            //如果當下的會議開始時間 小於 所有正在進行會議的結束時間
            if(!pq.empty() && rooms.empty() && times < pq.top().first){
                times = max(times, pq.top().first);
            }

            while(!pq.empty() && pq.top().first <= times){
                rooms.push(pq.top().second);
                pq.pop();
            }

            count[rooms.top()] += 1;
            pq.push({meetings[i][1]-meetings[i][0] + times, rooms.top()});
            rooms.pop();
            i++;
        
            
        }

        int res = INT_MAX;
        int maxFreq = 0;
        for(int i = 0; i < count.size(); i++){
            if(maxFreq < count[i]){
                res = i;
                maxFreq = count[i];
            }
            else if(maxFreq == count[i]){
                res = min(res, i);
            }
        }
        
        return res;
    }
};

/*
會議廳 0~n-1
每個會議開始時間都是unique
會議會先從數字最低的房間開始舉行 如果沒有房間就會delay進行 進行時間要跟原本一樣
當有空房間時 start最低的優先開始 return 哪一個房間舉辦過最多次的會議 如果有相同次數的狀況 return 數字較小的房間
n = 100
meeting數量 10^5
這題因為要顧兩個狀態 可能meeting來時還沒有房間 可能房間剛釋出 那都要選最小的 start time or number of room
所以會用Dual PQ來模擬這個過程
*/

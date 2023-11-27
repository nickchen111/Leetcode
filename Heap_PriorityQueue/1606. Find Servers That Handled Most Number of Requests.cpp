/*
1606. Find Servers That Handled Most Number of Requests
*/

// TC:O(nlgn+n) SC:O(n)
class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        set<int> free;
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> busy;//花費時間,服務器id
        vector<int> count(k);//紀錄每個服務器執行次數
        for(int i = 0; i<k; i++){
            free.insert(i);
        }

        for(int i=0; i<arrival.size(); i++){
            //將比arrival時間小的加回去free
            while(!busy.empty() && busy.top().first <= arrival[i]){
                free.insert(busy.top().second);
                busy.pop();
            }
            if(free.empty()) continue;

            auto iter = free.lower_bound(i%k);
            if(iter == free.end()) iter = free.begin();


            //將找到的服務器刪掉 加入busy
            int id = *iter;
            count[id]+=1;
            free.erase(id);
            busy.push({arrival[i]+load[i],id});
        }

        vector<int> res;
        int num = 0;
        for(int i =0; i<k; i++){
            if(count[i] > num){
                res = {i};
                num = count[i];
            }
            else if(count[i] == num){
                res.push_back(i);
            }
        }

        return res;

    }
};

/*
此題問說 你有k個服務器 每個一次只能處理一個process 每個工作有他的抵達時間以及需花費時間
在分配任務的時候必須從第i個job 的 i%k個服務器去執行 如果沒有那就一直往後找 都沒有就可以在從頭找
因此可以想到需要一個資料結構去維持free server->他需要可以被快速查找 set
還需要一個busy 表示哪些服務器 正在運行並且還需要多久時間-> PQ 因為每個任務來時必須把已完成的在加入free
*/

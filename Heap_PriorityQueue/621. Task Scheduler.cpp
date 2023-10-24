/*
621. Task Scheduler
*/


// PQ+Greedy TC:O(n+26*lg26) SC:O(26)
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        //greedy+ PQ題型
        //先建立一個map存放頻率
        n++;
        unordered_map<char,int> map;
        for(auto ch:tasks){
            map[ch]++;
        }
        //由於不用打印最佳的可能順序 只需存放進去頻率即可
        priority_queue<int, vector<int>, less<int>> pq;
        for(auto x:map){
            pq.push(x.second);
        }

        int res = 0;
        while(!pq.empty()){
            vector<int> temp;//存放每次被取完後的結果
            int k = min(n,(int)pq.size());//最後一輪的時候可能不到n個
            for(int i = 0; i<k;i++){
                int t = pq.top();
                pq.pop();
                t--;
                if(t != 0) temp.push_back(t);
            }
            if(temp.size() > 0) res+=n;
            else res+=k;

            for(auto x:temp){
                pq.push(x);
            }
        }

        return res;
    }
};

//Tricky Greedy解 TC:O(n) SC:O(26)
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        n++;
        unordered_map<char,int> map;
        for(auto ch:tasks){
            map[ch]++;
        }
        int maxfreq = 0;
        for(auto x:map){
            maxfreq = max(maxfreq,x.second);
        }

        int tail = 0;
        for(auto x:map){
            if(x.second == maxfreq) tail++;
        }

        return max((maxfreq-1)*n+tail,(int)tasks.size());
    }
};


/*
[5a 3b 2c 1d]
每次的間格必須是n = 2 +1 次 不然就要idle n次
所以會希望先取多的 次多....這樣取下去 (greedy)
*/

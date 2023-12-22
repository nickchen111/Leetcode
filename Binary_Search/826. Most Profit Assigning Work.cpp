/*
826. Most Profit Assigning Work
*/

// Heap + Sort: TC:O(nlgn + nlgm) SC:O(n)
class Solution {
    using PII = pair<int, int>;
public:
    int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
        int n = difficulty.size();
        vector<PII> arr;
        for(int i = 0; i < n; i++){
            arr.push_back({profit[i],difficulty[i]}); // profit / diffuculty
        }
        sort(arr.rbegin(), arr.rend());

        
        priority_queue<int, vector<int>, less<int>> pq;
        for(int i = 0; i < worker.size(); i++){
            pq.push(worker[i]);
        }

        int res = 0;
        for(int i = 0; i < n; i++){
            int bonus = arr[i].first;
            int level = arr[i].second;
            while(!pq.empty()){
                int workLevel = pq.top();
                if(workLevel >= level) {
                    res += bonus;
                    pq.pop();
                }
                else {
                    break;
                }
            }
        }

        return res;
    }
};

//Binary Serach + Hash Map TC:O(nlgn + mlgn)
class Solution {
public:
    int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
        int n = difficulty.size();
        map<int, int> map;
       
        for(int i = 0; i < n; i++){
            map[difficulty[i]] = max(map[difficulty[i]], profit[i]);// profit / diffuculty
        }
        
        int maxProfit = 0;
        for(auto &iter : map){
            iter.second = maxProfit = max(maxProfit, iter.second);
        }

        int res = 0;
        for(int i = 0; i < worker.size(); i++){
            int ability = worker[i];
            auto iter = map.upper_bound(ability);
            
            res += prev(iter)->second;
        }

        return res;
    }
};


/*
工作分配工人題目
這題是給你工作難度 工人能力值 且工作可以被重複做 但是工人只能做一次
貪心的想 先找工作profit最高的 看有多少人可以去做
在找次高的 不斷repeat直到沒有人可以做任何工作為止 -> AKA沒工作了
1. 將工作獎勵與他的難度合併並且以獎勵排序
2. 判斷有多少工人比此值高 Binary Search or PQ 後者好維護 前者如果找到了還要一個一個彈出或者標記為使用過 
PQ+Sort 時間： TC:O(nlgn + nlgm) n 為工作數量 m為工人數量
這題算是2071題的基本型 
Binary Search + Map 將工作難度分配給最佳效益狀況 然後直接讓工人去選小於等於他的工作去做
*/

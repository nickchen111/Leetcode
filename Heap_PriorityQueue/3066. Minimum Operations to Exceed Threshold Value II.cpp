/*
3066. Minimum Operations to Exceed Threshold Value II
*/

// TC:O(nlgn) SC:O(n)
class Solution {
    using LL = long long;
public:
    int minOperations(vector<int>& nums, int k) {
        int n = nums.size();
        priority_queue<LL, vector<LL>, greater<LL>> pq;
        unordered_map<LL,int> map;
        for(auto x : nums){
            map[x] += 1;
        }
        
        for(auto p : map){
            pq.push(p.first);
        }
       
        
        int count = 0;
        while(!pq.empty()){
            LL cur = pq.top();
            pq.pop();
            
            if(cur >= k) break;
            if(map[cur] >= 2){
                map[cur] -= 2;
                
                if(map[cur] == 0) map.erase(cur);
                else {
                    pq.push(cur);
                }
                int newVal = cur*2+cur;
                if(map.find(newVal) == map.end()){
                    pq.push((cur*2)+cur);
                }
                
                map[(cur*2)+cur] += 1;
                count += 1;
            }
            
            else if(map[cur] == 1){
                map.erase(cur);
                
                LL nxt = pq.top();
                pq.pop();
                
                map[nxt] -= 1;
                if(map[nxt] == 0) map.erase(nxt);
                else pq.push(nxt);
                
                LL minVal = min(cur, nxt);
                LL maxVal = max(cur,nxt);
                LL newVal = minVal*2 + maxVal;
                if(map.find(newVal) == map.end()){
                    pq.push(newVal);
                }
                
                map[newVal] += 1;
                count += 1;
            }
            
        }
        
        return count;
    }
};

/*
這次需要挑兩個最小的元素 可以挑重複出現的 並且加入新的元素 為 min(x,y)*2 + max(x,y)
問最少需要多少次讓所有元素大於等於k
用一個pq裝
並且只有當元素數量超過2才可以執行此操作

*/

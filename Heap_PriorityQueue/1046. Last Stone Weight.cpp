/*
1046. Last Stone Weight
*/

//TC:O(n) SC:O(n)
class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        int n = stones.size();
        priority_queue<int> pq;
        for(int i = 0; i<n; i++)
            pq.push(stones[i]);
        

        while(!pq.empty()){
            if(pq.size() == 1) return pq.top();
            int x = pq.top();
            pq.pop();
            int y = pq.top();
            pq.pop();

            if(x-y == 0) continue;
            else pq.push(x-y);
        }
        return 0;
    }
};

/*
3091. Apply Operations to Make Sum of Array Greater Than or Equal to k
*/

// TC:O(n) SC:O(lgn)
class Solution {
public:
    int minOperations(int k) {
        
       
       
        queue<pair<int,int>> q; // 綜合多少 當前數字
        pq.push({1,1});
       
        int step = -1;
       
        while(!q.empty()){
            int sz = pq.size();
            step += 1;
            int curVal = INT_MIN;
            while(sz--){
                int sum = q.front().first;
                int cur = q.front().second;
    
                
                q.pop();
                if(sum >= k){
                  return step;  
                } 
                if(sum < curVal) continue;
                curVal = max(curVal, sum);
            
                q.push({sum+1,cur+1}); // ++ 
                q.push({sum+cur,cur});
            }
        }
        
        return -1;
    }
};

/*
起初是1 每次操作可以做某個元素++, or 某個元素複製

問說最少做幾次讓總和大於等於k
BFS
25 -> 1, 2, (2,2)->(2,2,2)->(2,2,3) -> (2,2,4) -> (2,2,4,4) ->
25 -> 8
140
*/

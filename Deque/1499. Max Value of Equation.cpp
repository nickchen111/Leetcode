/*
1499. Max Value of Equation
*/


// TC:O(n) SC:O(n)
class Solution {
public:
    int findMaxValueOfEquation(vector<vector<int>>& points, int k) {
        //Deque 去紀錄x的狀況
        deque<int> dq;//單調遞減的-xi+yi
        int n = points.size();
        int res = INT_MIN;
        for(int i = 0; i<n; i++){
            while(!dq.empty() && points[i][0] - points[dq.front()][0] > k){
                dq.pop_front();
            }
            if(!dq.empty()){
                res = max(res,points[dq.front()][1]-points[dq.front()][0]+points[i][0]+points[i][1]);
            }
            //在把新的元素加進隊伍裡 可能可以彈掉隊尾元素 
            while(!dq.empty() && (points[dq.back()][1]-points[dq.back()][0] < points[i][1]-points[i][0])){
                dq.pop_back();
            }
            dq.push_back(i);
        }

        return res;
    }
};

/*
max{yi+yj-xi+xj}
確定一個j點 找相對應的i點
xj+yj+max(-xi+yi) for |xi-xj| <=k
意即 xi-xj 為 老去的條件
-xi+yi為slide window 想max的東西
*/

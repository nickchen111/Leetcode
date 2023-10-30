/*
1776. Car Fleet II
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    vector<double> getCollisionTimes(vector<vector<int>>& cars) {
        //從後往前看 用一個stack紀錄有可能被撞到的車
        int n = cars.size();
        vector<double> res(n,-1);
        stack<int> s;
        for(int i = n-1; i>=0; i--){
            //如果車子不會相撞的狀況 目前stack裡的車子就不可能跟更前面的發生碰撞
            while(!s.empty() && cars[i][1] <= cars[s.top()][1]){
                s.pop();
            }
            while(!s.empty()){
                int candidate = s.top();
                double t = 1.0*(cars[s.top()][0]-cars[i][0])/(cars[i][1] - cars[s.top()][1]);
                //如果我撞你的時間比你撞前面的還要快或者你根本沒跟其他人撞
                if(t <= res[candidate] || res[candidate] < 0){
                    res[i] = t;
                    break;
                }
                //我可能是跟candidate後面的撞
                s.pop();
            }
            s.push(i);
        }

        return res;
    }
};

/*
853. Car Fleet
*/


//單調棧概念解法 TC:O(n) SC:O(n) 由後到前 直接從循環判斷哪些會撞到 所以不用設定棧
class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        int n = position.size();
        vector<pair<int,int>> q;
        for(int i = 0; i<n; i++){
            q.push_back({position[i],speed[i]});
        }

        //按照位置排序 小到大
        sort(q.begin(), q.end());
        
        int count = 0;
        for(int i = n-1; i>=0; i--){
            double T = (target - q[i].first)*1.0/q[i].second;
            int j = i-1;
            while(j >= 0 && (target - q[j].first)*1.0/q[j].second <= T){
                j--;
            }
            //出來之後的是不會跟i相撞的j
            count+=1;
            i = j+1;//因為for loop會再減一
        }

        return count;
    }
};

//單調棧解 由前到後
class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        int n = position.size();
        vector<pair<int,double>> q;
        for(int i = 0; i<n; i++){
            q.push_back({position[i],(target-position[i])*1.0/speed[i]});
        }

        //按照位置排序 小到大
        sort(q.begin(), q.end());
        
        stack<double> s;
        for(int i = 0; i<n; i++){
            double T = q[i].second;
            //  T是排在靠近終點的車 他抵達的時間 大於我一開始加入隊列的車車 代表會相撞
            while(!s.empty() && T >= s.top()){
                s.pop();
            }
            s.push(T);
        }

        return s.size();
    }
};

/*
973. K Closest Points to Origin
*/

// PQ TC:O(nlgk) SC:O(k) 此題不僅僅是PQ考題 也可以用quick select優化 達到O(n)時間複雜度
class Solution {
    struct state{
        int x;
        int y;
        int dist;
        state(int dist, int x, int y){
            this->dist = dist;
            this->x = x;
            this->y = y;
        }
        bool operator<(const state& other) const{
            if(dist != other.dist)
                return dist < other.dist;
            else return dist < other.dist;
        }
    };
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {

        priority_queue<state, vector<state>, less<state>> pq;
        for(int i = 0; i<points.size(); i++){
            int dist = pow(points[i][0],2) + pow(points[i][1],2);
            pq.push({dist,points[i][0],points[i][1]});
            if(pq.size() > k) pq.pop();
        }

        vector<vector<int>> res;
        
        while(!pq.empty()){
            res.push_back({pq.top().x,pq.top().y});
            pq.pop();
        }

        return res;
    }
};

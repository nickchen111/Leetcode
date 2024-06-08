/*
3175. Find The First Player to win K Games in a Row
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int findWinningPlayer(vector<int>& skills, int k) {
        int n = skills.size();
        if(k >= n){
            int res = -1;
            int maxVal = INT_MIN;
            for(int i = 0; i < n; i++){
                if(skills[i] > maxVal){
                    maxVal = skills[i];
                    res = i;
                }
            }
            
            return res;
        }
        
        deque<pair<int,int>> q; // index, value
        vector<int> count(n,0);
        for(int i = 0; i < n; i++){
            q.push_back({i, skills[i]});
        }
        
        while(!q.empty()){
            int idx1 = q.front().first;
            int val1 = q.front().second;
            q.pop_front();
            int idx2 = q.front().first;
            int val2 = q.front().second;
            q.pop_front();
            if(val1 > val2){
                q.push_front({idx1, val1});
                q.push_back({idx2, val2});
                count[idx1] += 1;
                if(count[idx1] == k) return idx1;
            }
            else {
                q.push_front({idx2, val2});
                q.push_back({idx1, val1});
                count[idx2] += 1;
                if(count[idx2] == k) return idx2;
            }
        }
        
        return -1;
    }
};

/*
這題在問說比較前兩個數字 較小的數字放到隊列尾巴較大的繼續比 看哪個index可以連續贏k次 k 可以到1e9 但是對列元素只會有1e6 
所以如果 k >= n 直接找最大的元素就對了 如果k 小於n 那就直接deque模擬
*/

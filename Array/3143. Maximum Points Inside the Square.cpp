/*
3143. Maximum Points Inside the Square
*/

// TC:O(nlgn) SC:O(n)
class Solution {
public:
    int maxPointsInsideSquare(vector<vector<int>>& points, string s) {
        int n = points.size();
       
        vector<pair<int,int>> arr;
        for(int i = 0; i < n; i++){
            int a = abs(points[i][0]),  b = abs(points[i][1]);
            int take = max(a, b);
            arr.push_back({take, i});
        }
        sort(arr.begin(), arr.end());
        
        int res = INT_MIN;
        
        int square = 0;
        int idx = 0;
        int count = 0;
        unordered_map<int,int> map;
        while(idx < arr.size()){
            bool flag = 0;
            square = max(square, arr[idx].first);
            
            while(idx < n && square >= arr[idx].first){
                int ch = s[arr[idx].second]-'a';
                map[ch] += 1;
                count += 1;
                idx++;
                if(map[ch] >= 2) {
                    flag = 1;
                    break;
                }
            }
            
            if(flag) break;
            
           res = max(res, count);
            
            
        }
        
        return res == INT_MIN ? 0 : res;
        
    }
};

/*
從0 開始出發的點 包起來的正方形 不能包含兩個相同的字母 問最多可以取到多少點
包起來的定義是邊邊跟內含都算
去計算每個點到原點距離取最大的那個邊長 從小排到大 開始判斷
*/

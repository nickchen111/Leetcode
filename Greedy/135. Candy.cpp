/*
135. Candy
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int candy(vector<int>& ratings) {
        
        int n = ratings.size();
        vector<int> f(n,1);
        //分左右兩次two pass去遍歷
        //看他左邊
        for(int i = 1; i<n; i++){
            if(ratings[i] > ratings[i-1]){
                f[i] = max(f[i],f[i-1]+1);
            }
        }
        //看右邊
        for(int i = n-2; i>=0; i--){
            if(ratings[i] > ratings[i+1]){
                f[i] = max(f[i],f[i+1]+1);
            }
        }

        int res = 0;
        for(int i = 0; i<f.size(); i++){
            res+=f[i];
        }

        return res;
    }
};

/*
386. Lexicographical Numbers
*/

// Greedy TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> lexicalOrder(int n) {
        vector<int> res{1};
        int i = 1;
        while(res.size() < n){
            if(i*10 <= n){
                i*=10;
                res.push_back(i);
            }
            else{
                while(i+1 > n || (i%10) == 9) i = i/10;//找前一位數字
                i+=1;
                res.push_back(i);
            }
        }

        return res;
    }
};

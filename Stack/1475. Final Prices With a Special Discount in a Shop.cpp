/*
1475. Final Prices With a Special Discount in a Shop
*/

// Stack  TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> finalPrices(vector<int> prices) {
        //單調棧
        int n = prices.size();
        stack<int> s;//遞增棧 放index
        
        for(int i = 0; i<n; i++){
           while(!s.empty() && prices[s.top()] >= prices[i]){
               prices[s.top()]-=prices[i];
               s.pop();
           }
           s.push(i);
        }

        return prices;
    }
};

//by pointer TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> finalPrices(vector<int> prices) {
        //單調棧
        int n = prices.size();
        stack<int*> s;//遞增棧 放的是指標   
        
        for(int &p:prices){
           while(!s.empty() && *s.top() >= p){
               *s.top()-=p;
               s.pop();
           }
           s.push(&p);//取址
        }

        return prices;
    }
};

/*
1488. Avoid Flood in The City
*/

// TC:O(nlgn+n) SC:O(n)
class Solution {
public:
    vector<int> avoidFlood(vector<int>& rains) {
        int n = rains.size();
        set<int> drySet;
        unordered_map<int,int> fill;// 湖對應的idx
        vector<int> res(n,-1);
        for(int i = 0; i<n; i++){
           int x = rains[i];
           if(x == 0){
               res[i] = 1;
               drySet.insert(i);
           }
           else {
               if(fill.find(x) == fill.end()){
                   fill[x] = i;
               }
               else {
                   auto iter = drySet.lower_bound(fill[x]);
                   if(iter == drySet.end()) return {};
                   else {
                       res[*iter] = x;
                       drySet.erase(iter);
                       fill[x] = i;//這裡記得更新新的這個湖滿了的位置
                   }
                   
               }
           }
        }
        return res;
    }
};


/*
此題限制 每天下雨在不同號的湖上 只有沒下雨日可以選一個湖抽乾水 問有沒有方案是可以防止氾濫
如果下了兩次同個湖那就是氾濫

沒下雨的時候不曉得要對哪天抽水!? 繼續遍歷到fill的某個大於1 要溢出的這個湖後一個dry day那天對滿了的湖抽水

*/

/*
904. Fruit Into Baskets
*/

// TC:O(n) SC:O(2)
class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int res = 0;
        int n = fruits.size();
        unordered_map<int,int> map;
        int j = 0;
        for(int i = 0; i < n; i++){
            while(j < n && map.size() <= 2){
                res = max(res, j-i);
                map[fruits[j]]+=1;
                j++;
            }
            if(map.size() <= 2) res = max(res, j-i);
            map[fruits[i]]-=1;
            if(map[fruits[i]] == 0) map.erase(fruits[i]);
        }
        
        return res;
    }
};

/*
此題限制
1. 只能接受兩種型態水果
2. 每走一棵樹就一定要拿一種型態
3. 如果遇到沒有屬於你裝水果型態的樹 就必須停止
*/

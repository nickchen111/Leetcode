/*
1298. Maximum Candies You Can Get from Boxes
*/

// TC:O(m+n) SC:O(m+n) m : # of box n : # of key
class Solution {
public:
    int maxCandies(vector<int>& status, vector<int>& candies, vector<vector<int>>& keys, vector<vector<int>>& containedBoxes, vector<int>& initialBoxes) {
        //能開的先開先收集好鑰匙 然後去開需要鑰匙的看能否對上 並且不斷更新queue
        unordered_set<int> needkey; // 鑰匙
        queue<int> q;

        for(int i = 0; i <initialBoxes.size(); i++){
            q.push(initialBoxes[i]);
        }

        int res = 0;
        while(true){
            bool flag = 1;
            vector<int> temp;
            while(!q.empty()){
                int curBox = q.front();
                q.pop();
               
                if(status[curBox] == 0 && needkey.find(curBox) == needkey.end()) temp.push_back(curBox);
                else if(status[curBox] == 1 || status[curBox] == 0 && needkey.find(curBox) != needkey.end()){
                    res += candies[curBox];
                    //加入新鑰匙
                    for(auto x : keys[curBox]){
                        needkey.insert(x);
                        flag = 0;
                    }
                    //加入新箱子
                    for(int i = 0; i < containedBoxes[curBox].size(); i++){
                        q.push(containedBoxes[curBox][i]);
                    }
                }
            }
            if(flag) break;
            else {
                for(auto x : temp){
                    q.push(x);
                }
            }
        }

        return res;
    }
};

/*
status : 代表 i th box 打開or 關閉
candies : 代表箱子里的蠟燭數量
key : 是你打開某箱子後可以拿到的鑰匙
contained : 是箱子里包的其他箱子有哪些
我會先去看我有哪些箱子 看他能否打開 可以就直接拿
然後去看他裡面的箱子有哪些以及是否有鑰匙 (加入set1, set2清單之類) 然後再逐一打開重複上面事項 
關著的需要鑰匙 開著的不需要鑰匙
*/

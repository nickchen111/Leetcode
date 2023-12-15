/*
838. Push Dominoes
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    string pushDominoes(string dominoes) {
        int n = dominoes.size();
        vector<int> res(n,-2);

        queue<pair<int,int>> q;
        for(int i =0; i < n; i++){
            if(dominoes[i] == 'L'){
                q.push({i,-1});
                res[i] = -1;
            }
            else if(dominoes[i] == 'R'){
                q.push({i,1});
                res[i] = 1;
            }
        }

        while(!q.empty()){
            int len = q.size();
            unordered_map<int,int> map;
            for(int i = 0; i < len; i++){
                auto [pos,dirs] = q.front();
                q.pop();
                if(dirs == -1 && pos -1 >= 0 && res[pos-1] == -2){
                    map[pos-1] -= 1;
                }
                else if(dirs == 1 && pos + 1 < n && res[pos+1] == -2){
                    map[pos+1] += 1;
                }
            }

            for(auto p : map){
                q.push(p); //有可能站好好的被推倒 他會繼續推倒其他骨牌
                res[p.first] = p.second;
            }
        }

        string str;
        for(int i = 0; i < n; i++){
            if(res[i] == -1){
                str += "L";
            }
            else if(res[i] == 1){
                str += "R";
            }
            else str += ".";
        }

        return str;
        
    }
};

/*
此題給你每個骨牌他在下個瞬間會往哪邊倒 或者沒事 問你最後骨牌的狀況為何
假設站著的骨牌是-2 如果兩邊過來一個 往左邊倒的-1 一個往右邊倒的正一 兩者相加他還是 -2 站著
但如果原本站著 -2 只有一邊-1過來 此位置要變成往左 直接變 -1
如果原本站著 -2 一邊往右倒過來  應該要是 -2 直接變 1 -> 用一個map紀錄各位置狀況
*/

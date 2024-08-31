/*
3273. Minimum Amount of Damage Dealt to Bob
*/

// TC:O(nlgn) SC:O(n)
class Solution {
    using LL = long long;
public:
    long long minDamage(int power, vector<int>& damage, vector<int>& health) {
        int n = damage.size();
        vector<pair<double, int>> enemies(n);
        for(int i = 0; i < n; i++){
            int time = (health[i] + power - 1) / power;
            double eff = (double)damage[i] / time;
            enemies[i] = {eff, i};
        }
        
        sort(enemies.rbegin(), enemies.rend());
        
        LL res = 0;
        LL totalDamage = 0;
        for(int i = 0; i < n; i++){
            totalDamage += damage[i];
        }
        
        for(int i = 0; i < n; i++){
            int idx = enemies[i].second;
            int time = (health[idx] + power - 1) / power;
            res += totalDamage * time;
            totalDamage -= damage[idx];
        }
        
        return res;
    }
};

/*
造成傷害較大的敵人 以及他需要花費的時間 兩個parameter
優先想處理傷害大的 但是它所需時間可能多 
這時候就需要去判斷說 處理某個敵人的話 他需要處理的秒數*這段時間總和 
需 5s 傷害 12 -> 100 + 32 = 132
需 4s 傷害 8 -> 80 + 60 = 140

按照傷害排序 一樣的話就看秒數!? -> fail
62
傷害 80 2s -> (80+79)*2 + 79 = 239+79*2解決當下困難所需時間 + 剩下的damage
傷害 79 1s -> 80+79 + 80*2 = 319
秒數越快越好 傷害越大越先處理  -> eff = 傷害/秒數


*/

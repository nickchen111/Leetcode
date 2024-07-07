/*
3207. Maximum Points After Enemy Battles
*/

// TC:O(nlgn) SC:O(1)
class Solution {
    using LL = long long;
public:
    long long maximumPoints(vector<int>& enemyEnergies, int currentEnergy) {
        LL res = 0;
        sort(enemyEnergies.begin(),  enemyEnergies.end());
        if(enemyEnergies[0] > currentEnergy) return 0;
        else {
            res += 1;
            currentEnergy -= enemyEnergies[0];
        }
        
        int n = enemyEnergies.size();
        
        int i = 0;
        int j = n-1;
        while(i <= j){
            LL divide = currentEnergy / enemyEnergies[i];
            LL mod = currentEnergy % enemyEnergies[i];
            if(divide != 0){
                res += divide;
                currentEnergy = mod;
            }
            else {
                currentEnergy += enemyEnergies[j];
                j--;
            }
        }
        
        return res;
    }
};

// TC:O(n) SC:O(1)
class Solution {
    using LL = long long;
public:
    long long maximumPoints(vector<int>& enemyEnergies, int currentEnergy) {
        LL res = 0;
        int minVal = *min_element(enemyEnergies.begin(), enemyEnergies.end());
        if(currentEnergy < minVal) return 0;
        else return (((LL)currentEnergy + accumulate(enemyEnergies.begin(), enemyEnergies.end(), 0LL)- (LL)minVal) / minVal);
    }
};


/*
敵人還沒選的話 我可以選他 然後減掉自己能量 + 1 pts 敵人也不用mark
如果至少有1分 我可以選一個沒選過的 然後加上他的能量 然後mark
*/

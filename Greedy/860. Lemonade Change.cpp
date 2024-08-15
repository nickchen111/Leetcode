/*
860. Lemonade Change
*/

// TC:O(n) SC:O(m)
class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        unordered_map<int,int> map;
        int n = bills.size();
        for(int i = 0; i < n; i++){
            int need = bills[i] - 5;
            if(need != 0){
                if(need == 15){
                    if(map[10] >= 1 && map[5] >= 1){
                        map[10] -= 1;
                        map[5] -= 1;
                    }
                    else if(map[5] >= 3){
                        map[5] -= 3;
                    }
                    else return false;
                }
                else if(need == 10){
                    if(map[10] >= 1){
                        map[10] -= 1;
                    }
                    else if(map[5] >= 2){
                        map[5] -= 2;
                    }
                    else return false;
                }
                else if(need == 5){
                    if(map[5] >= 1) {
                        map[5] -= 1;
                    }
                    else return false;
                }
            }
            map[bills[i]] += 1;
        }

        return true;
    }
};

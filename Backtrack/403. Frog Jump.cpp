/*
403. Frog Jump
*/


// TC:O(3^n) SC:O(3^n)
class Solution {
    unordered_set<int> set;
    std::set<pair<int, int>> failed;
public:
    bool canCross(vector<int>& stones) {

        for(auto stonePos:stones){
            set.insert(stonePos);
        }

        return DFS(stones, 0, 0);
    }

    bool DFS(vector<int>& stones, int pos, int jump){

        if(pos == stones.back()) return true;
        
        if(failed.find({pos,jump}) != failed.end()) return false;

        if(set.find(pos) == set.end()) return false;
        
        for(int i = -1; i<2; i++){
            int newjump = jump+i;
            if(newjump <= 0) continue;
            int newPos = pos + newjump;
            if(DFS(stones, newPos, newjump)){
                return true;
            }
        }

        failed.insert({pos,jump});

        return false;
    }
};

/*
此題數組內的數字代表石頭所在index 在這之間的都是河流 
給青蛙一些跳躍規則 這次跳１步 下次就只能跳1-1 1 1+1 三種選擇
問能否跳到終點
*/

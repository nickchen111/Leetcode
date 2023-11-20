/*
2391. Minimum Amount of Time to Collect Garbage
*/

// TC:O(n*k) SC:O(n*k) k為字串平均長度
class Solution {
public:
    int garbageCollection(vector<string>& garbage, vector<int>& travel) {
        //presum travel time
        int n = garbage.size();
        vector<int> presum(n);
        presum[0] = 0;
        for(int i = 1; i<n; i++){
            presum[i] = presum[i-1]+travel[i-1];
        }

        unordered_map<char,int> map;
        int endP = n; int endG = n; int endM = n;
        for(int i=0; i<n; i++){
            for(int j = 0; j<garbage[i].size(); j++){
                if(garbage[i][j]=='P'){
                    endP = i;
                }
                else if(garbage[i][j] == 'G'){
                    endG = i;
                }
                else if(garbage[i][j] == 'M'){
                    endM = i;
                }
                map[garbage[i][j]]+=1;
            }
        }
        int res = 0;
        //撿一個花一分鐘
        for(auto x:map){
            res+=x.second;
        }
        //看終點在哪 
        res+=(endP == n) ? 0:presum[endP];
        res+=(endM == n) ? 0:presum[endM];
        res+=(endG == n) ? 0:presum[endG];

        return res;
 
    }
};

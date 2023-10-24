/*
846. Hand of Straights
*/

//Greedy + hash map+ sort TC:O(nlgn) SC:O(n)
class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        int n = hand.size();
        if(n%groupSize != 0) return false;
        
        unordered_map<int,int> map;
        for(int i = 0; i<n; i++){
            map[hand[i]]+=1;
        }
        sort(hand.begin(),hand.end());

        for(int i = 0; i <n; i++){
            if(map[hand[i]] == 0) continue;//已經跟別人組隊組完了
            for(int j = 0; j<groupSize; j++){
                int cur = hand[i]+j;
                if(map[cur] == 0) return false;
                map[cur]-=1;
            }
        }
        return true;
    }
};

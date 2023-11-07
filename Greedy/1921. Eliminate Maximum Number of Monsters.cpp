/*
1921. Eliminate Maximum Number of Monsters
*/

//TC:O(nlgn) SC:O(n)
class Solution {
public:
    int eliminateMaximum(vector<int>& dist, vector<int>& speed) {
        int n = dist.size();

        vector<double> time;
        for(int i=0; i<n; i++){
            time.push_back((double)dist[i]/speed[i]);
        }

        sort(time.begin(),time.end());
        int res = 0;
        for(int i = 0; i<n; i++){
            if((double)i < time[i]) res++;
            else break;
        }
        return res;
    }
};

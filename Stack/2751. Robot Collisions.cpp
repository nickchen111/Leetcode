/*
2751. Robot Collisions
*/


// TC:O(nlgn) SC:O(n)
class Solution {
public:
    vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {
        int n = positions.size();
        vector<vector<int>> arr;
        for(int i = 0; i < n; i++){
            if(directions[i] == 'R') arr.push_back({positions[i], healths[i], 1, i});
            else arr.push_back({positions[i], healths[i], -1, i});
        }

        sort(arr.begin(), arr.end());
        vector<vector<int>> right;
        vector<pair<int,int>> res;
        for(int i = 0; i < n; i++){
            int pos = arr[i][0], hel = arr[i][1], dir = arr[i][2], idx = arr[i][3];
            if(dir == 1) {
                right.push_back({idx,hel,1});
            }
            else {
                while(!right.empty() && right.back()[2] == 1){
                    if(hel > right.back()[1]){
                        hel -= 1;
                        right.pop_back();
                    }
                    else if(hel == right.back()[1]){
                        right.pop_back();
                        hel = 0;
                        break;
                    }
                    else {
                        right.back()[1] -= 1;
                        hel = 0;
                        break;
                    }
                }

                if(hel != 0){
                    right.push_back({idx,hel, -1});
                }
            }
        }

        sort(right.begin(), right.end());
        vector<int> ret;
        for(int i = 0; i < right.size(); i++){
            ret.push_back(right[i][1]);
        }


        return ret;
    }
};

/*
1847. Closest Room
*/

// TC:O(nlgn+m+mlgm) SC:O(n)
class Solution {
    static bool cmp(vector<int>& a, vector<int>& b){
        return a[1] > b[1];
    }
public:
    vector<int> closestRoom(vector<vector<int>>& rooms, vector<vector<int>>& queries) {
        
        sort(rooms.begin(),rooms.end(),cmp);
        //將query的idx加進去自己
        for(int i = 0; i<queries.size(); i++){
           queries[i].push_back(i);
        }
        sort(queries.begin(),queries.end(),cmp);

        set<int> set;//裝可以的roomid
        int i = 0; 
        vector<int> res(queries.size(),-1);
        for(int j = 0; j<queries.size(); j++){
            int prefer = queries[j][0], minsize = queries[j][1];
            while(i < rooms.size() && rooms[i][1] >= minsize){
                set.insert(rooms[i][0]);
                i++;        
            }

            int diff = INT_MAX;
            int ans = -1;
            auto iter = set.lower_bound(prefer);
            if(iter != set.end()){
                if(abs(*iter-prefer) <= diff){
                    diff = abs(*iter-prefer);
                    ans = *iter;
                }
            }
            if(iter != set.begin()){
                auto iter2 = prev(iter,1);
                if(abs(*iter2-prefer) <= diff){
                    ans = *iter2;
                }
            }

            res[queries[j][2]] = ans;
        }

        return res;
        
    }
};

/*
此題限制 
1. 房間大小至少要比query的大->從越大的要求開始
2. 房間id-preferid要盡量小-> 會想要一個heap 二分搜索
*/

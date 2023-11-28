/*
2736. Maximum Sum Queries
*/


// TC:O(N*Q) SC:O(N+Q)
class Solution {
public:
    vector<int> maximumSumQueries(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {
        map<int, set<pair<int,int>>> map;
        //由小到大query
        for(int i = 0; i<queries.size(); i++){
            int x = queries[i][0], y = queries[i][1];
            map[x].insert({y,i});
        }
        vector<vector<int>> nums;
        for(int i = 0; i<nums1.size(); i++){
            nums.push_back({nums1[i]+nums2[i],nums1[i],nums2[i]});
        }
        //sum由大到小
        sort(nums.rbegin(),nums.rend());
        vector<int> res(queries.size(),-1);

        for(auto &e:nums){
            int sum = e[0], a = e[1], b = e[2];
            auto iter = map.begin();
            // x 的數值
            while(iter != map.end() && iter->first <= a){
                //在看y的數值
                set<pair<int,int>>& s = iter->second;//這樣子才不用複製一份並且可提供修改
                auto iter2 = s.begin();
                while(iter2 != s.end() && iter2->first <=b){
                    res[iter2->second] = sum;
                    s.erase(iter2++);
                }

                if(s.empty()){
                    map.erase(iter++);
                }
                else iter++;
            }
        }

        return res;
    }
};

/*
這道題還是挺難一次想對的 此題給的限制是給你一堆{x,y}的query 求數組內nums1 nums2 有哪些pair是滿足的之中 求pair相加最大的那項
如果是對query排序 從最大的x or y去找出有哪些對 很容易刪除掉不滿足的x or y 但是在處理另外一個變量時 x or y
會發現還要考慮x+y這個變量 這時要按照哪個變量排序感覺都不是很對
所以換個念想 對nums1 + nums2排序 去求query有哪些是符合他的 那此sum必定為這些query的答案
那麼就可以先對query x排序 在對y排序並且記錄他的index by 什麼資料結構  map<int,set<pair<int,in>>> map x->{y,idx}

*/

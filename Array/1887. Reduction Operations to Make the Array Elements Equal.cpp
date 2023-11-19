/*
1887. Reduction Operations to Make the Array Elements Equal
*/

// TC:O(n) SC:O(k)
class Solution {
public:
    int reductionOperations(vector<int>& nums) {
        map<int,int> map;
        for(auto num:nums){
            map[num]+=1;
        }
        vector<int> freq;
        for(auto x:map){
            freq.push_back(x.second);
        }
        int res = 0;
        int count=0;
        //最後一個不算
        for(int i = freq.size()-1; i>=1; i--){
            count+=freq[i];
            res+=count;
        }

        return res;
    }
};
/*
1 1 1 2 2 2 3 3 3
      s     e
1 1 1 2 2 2 2 3 3 3 4 4 4 5 5 5 
2->4 
3->3
4->3
*/

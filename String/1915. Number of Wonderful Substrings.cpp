/*
1915. Number of Wonderful Substrings
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    long long wonderfulSubstrings(string word) {
        long long res = 0;
        vector<int> count(10,0);
        unordered_map<int,vector<int>> map; // val->index
        map[0].push_back(-1);
        for(int i = 0; i<word.size(); i++){
            count[word[i]-'a']+=1;
            //狀態壓縮
            int key = convert2key(count);
            if(map.find(key) != map.end()){
                res+=map[key].size();
            }
            for(int k = 0; k<10; k++){
                int newkey = key;
                if((key>>k)&1 == 1){
                    newkey -=(1<<k);
                }
                else newkey+=(1<<k);
                if(map.find(newkey) != map.end()){
                    res+=map[newkey].size();
                }
            }
            map[key].push_back(i);
        }

        return res;
    }
    int convert2key(vector<int>& count){
        int key = 0;
        for(int i = 0; i<count.size(); i++){
            if(count[i]%2 == 1){
                key+=(1<<i);
            }
        }

        return key;
    }
};

/*
sum[i:j] = presum[1:j]-presum[1:i-1]
偶數          這裡的奇偶數就要相同
字母從a~j 10個
prefix sum
hash table val -> index 
[1 2 3 4 5 6 7 8 9]
[x x x x x x x i x x x x j x x x x]
1. a:5 b:3 c:6 ->536 110.     0000010111   key: 0000010111
2. a:3 b:1 c:4 -> 314 110.    abcdefghij
*/

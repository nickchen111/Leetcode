/*
954. Array of Doubled Pairs
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    bool canReorderDoubled(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        unordered_map<int, int> map; // val -> freq
        
        // two pass
        for(int i = 0; i < arr.size(); i++){
            map[arr[i]] += 1;
        }

        for(int i = 0; i < arr.size(); i++){
            if(map[arr[i]] != 0 && map[2*arr[i]] != 0){
                map[arr[i]] -= 1;
                map[2*arr[i]] -= 1;
            }
        }

        for(auto p : map){
            if(p.second != 0) return false;
        }

        return true;
    }
};

/*
2i+1 = 2倍的 2i
i = 0: 1 -> 0
i = 1: 3 -> 2
i = 2: 5 -> 4
i = 3: 7 -> 6
要找到一對一對的
每一對 後者會是前者的兩倍
[1,2,4,8]
*/

/*
869. Reordered Power of 2
*/

// TC:O(32* 9lg9) SC:O(1) 
class Solution {
public:
    bool reorderedPowerOf2(int N) {
        string n = to_string(N);
        sort(n.begin(),n.end());
        for(int i = 0; i < 32; i++){
            int cur = (1 << i);
            string str = to_string(cur);
            sort(str.begin(),str.end());
            if(str == n) return true;
        }

        return false;
    }
};


/*
1 2 4 8 16 32 64 128 256 .... 總共就是32種
將所有可能性列出來排序 跟目前n排序後比較看能否找到相同的
*/

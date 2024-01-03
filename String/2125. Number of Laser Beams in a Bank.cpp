/*
2125. Number of Laser Beams in a Bank
*/

// TC:O(m*n) SC:O(1)
class Solution {
public:
    int numberOfBeams(vector<string>& bank) {
        int prev = 0;
        int res = 0;
        for(auto row : bank){
            int count = 0;
            for(auto ch : row){
                if(ch == '1') count += 1;
            }
            if(prev != 0){
                res += prev*count;
            }
            if(count != 0) prev = count;
        }

        return res;
    }
};

/*
上下兩層看有多少條線
*/

/*
1561. Maximum Number of Coins You Can Get
*/

// TC:O(n+nlgn) SC:O(1)
class Solution {
public:
    int maxCoins(vector<int>& piles) {
        sort(piles.begin(),piles.end());
        //每次都選最大兩個跟最小的一個 每次都可拿到中間那項數字
        //[1 2 2 4 7 8] 1 4 7....  [1 2 3 4 5 6 7 8 9]
        int sum = 0;
        int n = piles.size();
        int left = 0;
        int right = n-1;
        while(left < right){
            left++;
            right-=2;
            sum+= piles[right+1];
        }

        return sum;
    }
};

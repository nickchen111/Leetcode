/*
1105. Filling Bookcase Shelves
*/

// TC:O(n^2) SC:O(n)
class Solution {
public:
    int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
        int n = books.size();
        vector<int> dp(n+1,INT_MAX);
        books.insert(books.begin(),{-1,-1});
        dp[0] = 0;
        for(int i = 1; i <= n; i++){
            int maxVal = 0;
            int totalWidth = 0;
            for(int j = i; j >= 1; j--){
                maxVal = max(maxVal, books[j][1]);
                totalWidth += books[j][0];
                if(totalWidth > shelfWidth) break;
                dp[i] = min(dp[i], dp[j-1] + maxVal);
            }
        }

        return dp[n];
    }
};


/*
題目有限定的寬度 但是不限定高度
問說怎麼擺一堆書能讓他的總高度最小
->意味著最小化每一層的最大高度 -> 分割成任意子數組求最小化他們的最大高度之和
*/

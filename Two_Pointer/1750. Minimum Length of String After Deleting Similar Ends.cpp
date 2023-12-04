/*
1750. Minimum Length of String After Deleting Similar Ends
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int minimumLength(string s) {
        int n = s.size();
        int left = 0; int right = n-1;
        while(left < right){
            if(s[left] == s[right]){
                while(left < right && s[left] == s[left+1]){
                    left++;
                }
                while(right > left && s[right] == s[right-1]){
                    right--;
                }
                left++;
                right--;
            }
            else return right-left+1;
        }

        if(left == right) return 1;// c b c
        else return 0; // a a a 
    }
};
/*
此題限制
1.選定一段prefix 裡面元素都要相同   
2.選定一段suffix 裡面元素都要相同  且這兩段不能有idx重疊到 這兩段元素相同
3.不斷將這兩段刪減掉 求最後可以刪減出的最短長度
a a a 
c b c 
*/

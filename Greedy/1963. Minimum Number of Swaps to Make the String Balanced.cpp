/*
1963. Minimum Number of Swaps to Make the String Balanced
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int minSwaps(string s) {
        int n = s.size();
        int res = 0;
        int count = 0;
        stack<int> stack;
        for(int i = 0; i < n; i++){
            if(s[i] == '['){
                stack.push(i);
            }
        }

        for(int i = 0; i < n; i++){
            if(s[i] == '[') count++;
            else count--;
            if(count == -1){
                swap(s[i], s[stack.top()]);
                stack.pop();
                count = 1;
                res += 1;
            }
        }

        return res;

    }
};

/*
此題給你一定合法數量的左括號又括號 問說最少交換幾次讓他合法
我的想法是遇到左括號不及 直接累加  又括號讓我變-1再去找最遠的左括號交換

[][]
*/

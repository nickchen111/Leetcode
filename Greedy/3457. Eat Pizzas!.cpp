// TC:O(n) SC:O(1) 
class Solution {
public:
    long long maxWeight(vector<int>& pizzas) {
        ranges::sort(pizzas);
        int n = pizzas.size();
        int m = n / 4;
        int oddCount = (m+1) / 2;
        int evenCount = m / 2;
        int right = n-1;
        long long ans = 0;
        for(int i = 0; i < oddCount; i++) {
            ans += (long long) pizzas[right--];
        }
        for(int i = 0; i < evenCount; i++) {
            ans += pizzas[--right];
            right --;
        }
        return ans;
    }
};

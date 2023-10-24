/*
875. Koko Eating Bananas
*/

//TC:O(n) SC:O(1)
class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int n = piles.size();
        int left = 1;
        int right = 0;
        for(auto x:piles){
            right = max(right,x);
        }
        while(left < right){
            int mid = left + (right-left)/2;
            if(eat(piles,mid) > h){
                left = mid+1;
            }
            else right = mid;
        }
        
        return left;
    }

    int eat(vector<int>& piles, int mid){
        int h = 0;
        for(auto x:piles){
            //剛好吃完
            if(x%mid == 0){
                h+=x/mid;
            } 
            else{
                h+=x/mid+1;
            }
        }

        return h;
    }
};
/*
很明顯要用二分的基礎題
*/

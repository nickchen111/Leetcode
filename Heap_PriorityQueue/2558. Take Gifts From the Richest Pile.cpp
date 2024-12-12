/*
2558. Take Gifts From the Richest Pile
*/

// TC:O(klgn + n) SC:O(n)
class Solution {
    using LL = long long;
public:
    long long pickGifts(vector<int>& gifts, int k) {
        priority_queue<LL> maxHeap(gifts.begin(), gifts.end());
        while (k--) {
            LL mx = maxHeap.top();
            maxHeap.pop();        
            maxHeap.push(sqrt(mx));
        }
        LL res = 0;
        while (!maxHeap.empty()) {
            res += maxHeap.top();
            maxHeap.pop();
        }
        return res;
    }
};

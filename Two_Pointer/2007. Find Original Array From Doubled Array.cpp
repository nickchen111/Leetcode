/*
2007. Find Original Array From Doubled Array
*/

// 次優解Multiset: TC:O(nlgn + n/2 * lg(n/2)) SC:O(n)
class Solution {
public:
    vector<int> findOriginalArray(vector<int>& changed) {
        int n = changed.size();
        if(n % 2 == 1) return {};
        multiset<int> set(changed.begin(), changed.end());
        
        vector<int> res;
        while(set.size() != 0) {
            int num = *set.rbegin();
            if(num % 2 != 0) return {};
            if(set.find(num/2) == set.end()) return {};
            else {
                res.push_back(num/2);
                set.erase(set.lower_bound(num));
                set.erase(set.lower_bound(num/2));
            }
        }

        return res;

    }
};

//最優解 Two pointer TC:O(nlgn + n/2) SC:O(n)
class Solution {
public:
    vector<int> findOriginalArray(vector<int>& changed) {
        int n = changed.size();
        if(n % 2 == 1) return {};

        sort(changed.begin(), changed.end());
        vector<int> res;
        vector<int> used(n);
        int left = 0; int right = 0;
        for(int i = 0; i < n/2; i++){
            while(left < n && used[left]){
                left++;
            }
            if(left == n) return {};
            res.push_back(changed[left]);
            used[left] = 1;
            while(right < n && (used[right] || changed[left]*2 != changed[right])){
                right++;
            }
            if(right == n) return {};
            used[right] = 1;
        }

        return res;

    }
};

// Sliding Window TC:O(n * U) SC:O(U)
class Solution {
public:
    vector<int> getSubarrayBeauty(vector<int>& nums, int k, int x) {
        const int BASE = 50;
        vector<int> arr(BASE*2+1);
        int cnt = 0;
        vector<int> ans;
        int n = nums.size();
        int i = 0;
        for(int j = 0; j < n; j++) {
            arr[nums[j] + BASE] += 1;
            cnt += (nums[j] < 0);
            if(j - i + 1 == k) {
                if(cnt < x) {
                    ans.push_back(0);
                }
                else {
                    int tmp = 0;
                    for(int i = 0; i < BASE; i++) {
                        tmp += arr[i];
                        if(tmp >= x) {
                            ans.push_back(i - BASE);
                            break;
                        }
                    }
                }
                arr[nums[i] + BASE] -= 1;
                cnt -= (nums[i] < 0);
                i++;
            }
        }

        return ans;
    }
};

// Sliding Window + multiset TC:O(nlgn) SC:O(n)
class Solution {
public:
    vector<int> getSubarrayBeauty(vector<int>& nums, int k, int x) {
        multiset<int> set1;
        multiset<int> set2;
        vector<int> ans;
        int n = nums.size();
        int i = 0;
        for(int j = 0; j < n; j++) {
            if(set1.size() < x) set1.insert(nums[j]);
            else {
                if(nums[j] < *set1.rbegin()) {
                    int tmp = *set1.rbegin();
                    set1.erase(--set1.end());
                    set1.insert(nums[j]);
                    set2.insert(tmp);
                }
                else set2.insert(nums[j]);
            }
            if(j - i + 1 == k) {
                int tmp = *set1.rbegin();
                if(tmp < 0) ans.push_back(tmp);
                else ans.push_back(0);
                if(set1.find(nums[i]) != set1.end()) {
                    set1.erase(set1.lower_bound(nums[i]));
                    if(!set2.empty()) {
                        int tmp1 = *set2.begin();
                        set1.insert(tmp1);
                        set2.erase(set2.begin());
                    }
                }
                else {
                    set2.erase(set2.lower_bound(nums[i]));
                }
                i++;
            }
        }

        return ans;
    }
};

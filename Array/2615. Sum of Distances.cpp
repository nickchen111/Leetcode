/*
2615. Sum of Distances
*/

// Presum數學關係式 TC:O(n) SC:O(n)
class Solution {
    using LL = long long;
public:
    vector<long long> distance(vector<int>& nums) {
        int n = nums.size();
        vector<LL> res(n);
        unordered_map<LL, vector<LL>> map; // val -> pos
        for(int i = 0; i < n; i++){
            map[nums[i]].push_back(i);
        }

        for(auto p : map){
            if(p.second.size() == 1) res[p.second[0]] = 0;
            // 先遍歷一遍構造出presum 數組
            // [1,3,6]
            else {
                int m = p.second.size();
                vector<LL> presum(m+1);
                for(int i = 1; i <= m; i++){
                    presum[i] = presum[i-1] + p.second[i-1];
                }

                for(int i = 0; i < m; i++){
                    LL idx = p.second[i];
                    res[idx] = (idx*i - presum[i]) + (presum[m]-presum[i+1]-idx*(m-i-1));
                }
            }
        }

        return res;
    }
};

// 數學推導  TC:O(n) SC:O(n)
class Solution {
    using LL = long long;
public:
    vector<long long> distance(vector<int>& nums) {
        int n = nums.size();
        vector<LL> res(n);
        unordered_map<LL, vector<LL>> map; // val -> pos
        for(int i = 0; i < n; i++){
            map[nums[i]].push_back(i);
        }

        for(auto p : map){
            if(p.second.size() == 1) res[p.second[0]] = 0;
            // 先遍歷一遍構造出presum 數組
            // [1,3,6]
            else {
                int m = p.second.size();
                LL sum = 0;
                for(int i = 0; i < m; i++){
                    sum += p.second[i] - p.second[0];
                }
                res[p.second[0]] = sum;
                
                for(int i = 1; i < m; i++){
                    sum += (p.second[i] - p.second[i-1])*i;
                    sum -= (p.second[i] - p.second[i-1])*(m-i);
                    res[p.second[i]] = sum;
                }
            }
        }

        return res;
    }
};


/*
跟其他類似題比起來只是多套了一層比較關係 要找出所有在數組中相同的數字 然後讓當下的數字 i
去剪掉其他pos上的index 之和 |i - j|
ex : 1, 3, 6 -> |1 - 3| + |1 - 6| = 7 
3-1 + |3-6| = 2 + 3 = 5
1. presum解1*(i) - presum[i] + presum[n]-presum[i+1]-pos[i]*(n-i-1);
2. 數學推導or (nums[i]-nums[i-1])*i - (nums[i]-nums[i-1])*(n-i)
*/

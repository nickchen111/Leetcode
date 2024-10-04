/*
2491. Divide Players Into Teams of Equal Skill
*/


// TC:O(n) SC:O(n)
class Solution {
    using LL = long long;
public:
    long long dividePlayers(vector<int>& skill) {
        int n = skill.size();
        if(n % 2) return -1;
        if(n == 2) return (LL)(skill[0]*skill[1]);

        LL total = accumulate(skill.begin(), skill.end(), 0LL);
        if(total % (n/2)) return -1;
        LL pair_sum = (total*(LL)2)/n;
        unordered_map<LL, int> map;
        for(auto &s : skill){
            map[s] += 1;
        }

        LL res = 0;
        for(int i = 0; i < n; i++){
            if(map[skill[i]] == 0) continue;
            LL num = skill[i];
            map[num] -= 1;
            
            if(map[pair_sum - num] == 0) return -1;
            
            res += num * (pair_sum - num);
            map[pair_sum - num] -= 1;
        }

        return res;
    }
};

/*
兩兩一組 讓所有組數字和一樣
然後去將每一組數字相乘加總
一開始看到覺得很像背包 但後來想到似乎可以用map去解
n = 1e5
1 <= val <= 1000
total = 18, n = 6 -> 18/6 = 3 -> 3*2 = 6 每組加總要是6
*/

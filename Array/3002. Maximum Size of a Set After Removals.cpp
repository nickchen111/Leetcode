/*
3002. Maximum Size of a Set After Removals
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int maximumSetSize(vector<int>& nums1, vector<int>& nums2) {
        int num1 = 0;
        unordered_map<int,int> map1;
        for(auto x : nums1){
            map1[x] += 1;
        }
        
        for(auto x : map1){
            if(x.second >= 2){
                num1 += (x.second-1);
                x.second = 1;
            }
            if(num1 >= (nums1.size()/2)) break;
        }
        
        int num2 = 0;
        unordered_map<int,int> map2;
        for(auto x : nums2){
            map2[x] += 1;
        }
        for(auto x : map2){
            if(x.second >= 2){
                num2 += (x.second-1);
                x.second = 1;
            }
            if(num2 >= nums2.size()/2) break;
        }
        
        if(num1 >= nums1.size()/2 && num2 >= nums2.size()/2){
            unordered_set<int> set;
            for(auto p : map1){
                set.insert(p.first);
            }
            for(auto p :map2){
                set.insert(p.first);
            }
            return set.size();
        }
        
        // 如果他們之間有重複的可能並且某一方還沒刪除完 最佳策略刪除重複的
        vector<int> temp1;
        if(num1 < nums1.size()/2){
            for(auto p : map1){
                if(map2.find(p.first) != map2.end()){
                    num1 += 1;
                    temp1.push_back(p.first);
                    p.second -= 1;
                }
                if(num1 >= nums1.size()/2) break;
            }
            for(auto x : temp1){
                map1.erase(x);
            }
        }
        
        
        //檢查num2
        vector<int> temp2;
        if(num2 < nums2.size()/2){
            for(auto p : map2){
                if(map1.find(p.first) != map1.end()){
                    num2 += 1;
                    temp2.push_back(p.first);
                    p.second -= 1;
                }
                if(num2 >= nums2.size()/2) break;
            }
            for(auto x : temp2){
                map2.erase(x);
            }
        }
        
        //最佳策略做完仍然刪除不足 任意刪除皆不影響答案
        temp1.clear();
        temp2.clear();
        if(num1 < nums1.size()/2){
            for(auto p : map1){
                p.second -= 1;
                num1 += 1;
                temp1.push_back(p.first);
                if(num1 == nums1.size()/2) break;
            }
        }
        if(num2 < nums2.size()/2){
            for(auto p : map2){
                p.second -= 1;
                num2 += 1;
                temp2.push_back(p.first);
                if(num2 == nums2.size()/2) break;
            }
        }
        for(auto x : temp1) map1.erase(x);
        for(auto x : temp2) map2.erase(x);
        
        int res = 0;
        unordered_set<int> set;
        for(auto p : map1){
            set.insert(p.first);
        }
        for(auto p : map2){
            set.insert(p.first);
        }
        
        return set.size();
    }
};

/*
這題要你將每個array都去掉一半的元素 
並且讓他剩下的獨特元素加總數量最多
我的想法是
1.每個array都先計算他一定可以刪除的重複量 
2.如果還不足 就去看說對方有沒有跟他重複元素 有的話他就可以去掉 並且在map中也要去掉
3. 如果還是不足 任意刪除一個元素
4.另一個數組也做一樣的事情
5.最後將答案在用set裝起來去重 
*/

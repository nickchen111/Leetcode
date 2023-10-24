/*
380. Insert Delete GetRandom O(1)
*/

class RandomizedSet {
    vector<int> nums;
    unordered_map<int,int> nums2pos;
public:
    RandomizedSet() {
        
    }
    
    bool insert(int val) {
        if(nums2pos.find(val) != nums2pos.end()) return false;
        nums.push_back(val);
        nums2pos[val] = nums.size()-1;
        return true;
    }
    
    bool remove(int val) {
        if(nums2pos.find(val) == nums2pos.end()) return false;
        int pos = nums2pos[val];
        nums[pos] = nums.back();
        nums2pos[nums.back()] = pos;
        nums.pop_back();
        nums2pos.erase(val);
        return true;
    }
    
    int getRandom() {
        int r = rand()%nums.size();
        return nums[r];
        
    }
};

/*
這題跟之前的設計LRU LFU挺像的 
都是哈西表結合其他連續容器來達到insert remove O(1)
*/

// TC:O(1) SC:O(n)
class ProductOfNumbers {
private:
    vector<int> nums;
public:
    ProductOfNumbers() {
        this->nums = nums;
        nums.push_back(1);
    }
    
    void add(int num) {
        if(num == 0) {
            nums.clear();
            nums.push_back(1);
            return;
        }
        nums.push_back(nums.back() * num);
    }
    
    int getProduct(int k) {
        // x x x x x 
        if(nums.size()-1 < k) return 0;
        return nums.back() / nums[nums.size() - k  - 1];
    }
};

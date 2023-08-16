
//medium 現在變成可以最多容納兩個相同項  idea: 一個count 最多不超過2?!

#include <iostream>
#include <vector>
using namespace std;

class Solution{
public:
   int removeElement(vector<int>& nums){
    int count = 2;   //count指向第一個無效的位址
    for(int i = 2; i < nums.size(); i++){ //i = 2 因為前面兩項肯定是過關的
       if(nums[i] != nums[count-2]){
        nums[count] = nums[i];
        count++;
       }
   }
   for(int j = 0; j < count; j++){
   cout << nums[j] << endl;
   }
   return count;
   }
};

int main(){
    vector<int> nums = {0, 0, 1, 1, 1, 1, 2, 3, 3};
    Solution a;
    cout<< a.removeElement(nums);
}



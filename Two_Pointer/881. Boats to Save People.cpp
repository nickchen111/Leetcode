/*
881. Boats to Save People
*/

// TC:O(nlgn + n) SC:O(1)
class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        sort(people.begin(), people.end());
        int count = 0;
        int left = 0;
        int right = people.size()-1;

        while(left <= right){
            if(left == right){
                count++;
                break;
            }
            if(people[left] + people[right] > limit){
                right--;
                count++;
            }
            else if(people[left] + people[right] <= limit){
                left++;
                right--;
                count++;
            }
        }

        return count;
    }
};

/*
給你一堆人與他們的體重 有無限的船 
每艘船限重limit大小 並且只能最多兩個人
請找出最少需要多少船在所有人
*/

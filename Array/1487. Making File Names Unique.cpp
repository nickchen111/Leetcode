/*
1487. Making File Names Unique
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    vector<string> getFolderNames(vector<string>& names) {
        vector<string> res;
        unordered_map<string, int> map; 
        for(int i = 0; i<names.size(); i++){
            if(map.find(names[i]) != map.end()){
                int k = map[names[i]];
                string str;
                do{
                    str = names[i]+"(";
                    str+=to_string(k);
                    str +=")";
                    map[names[i]]+=1;
                    k++;
                }while(map.find(str) != map.end());
                map[str]+=1;
                res.push_back(str);
            }
            else {
                map[names[i]]++;
                res.push_back(names[i]);
            }
        }

        return res;
    }
};

/*
00 11 22 33 gta(1)
gta(0) gta(1) gta(2) gta(3) gta(4)
gta gta(1) gta(2) gta(4) gta(0)
00     11      2     4
*/

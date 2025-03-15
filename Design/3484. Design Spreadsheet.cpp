// TC:O(1) SC:O(1)
class Spreadsheet {
    vector<vector<int>> nums;
public:
    Spreadsheet(int rows) {
        nums.resize(26);
        for(int i = 0; i < 26; i++) nums[i].resize(rows+1, 0);
    }
    
    void setCell(string cell, int value) {
        int row = cell[0] - 'A';
        int col = stoi(cell.substr(1));
        nums[row][col] = value;
    }
    
    void resetCell(string cell) {
        int row = cell[0] - 'A';
        int col = stoi(cell.substr(1));
        nums[row][col] = 0;
    }
    
    int getValue(string formula) {
        int n = formula.size();
        int pos = 0;
        string num1;
        for(int i = 1; i < n; i++) {
            if(formula[i] == '+') {
                pos = i;
                break;
            }
            num1 += formula[i];
        }
        string num2 = formula.substr(pos+1);
        int number1 = 0, number2 = 0;
        if(!isdigit(num1[0])) {
            int row = num1[0] - 'A';
            int col = stoi(num1.substr(1));
            number1 = nums[row][col];
        }
        else {
            number1 = stoi(num1);
        }
        if(!isdigit(num2[0])) {
            int row = num2[0] - 'A';
            int col = stoi(num2.substr(1));
            number2 = nums[row][col];
        }
        else {
            number2 = stoi(num2);
        }
        return number1 + number2;
    }
};

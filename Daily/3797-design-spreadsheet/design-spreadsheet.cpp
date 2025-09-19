class Spreadsheet {
    unordered_map<string, int> mp;
public:
    Spreadsheet(int rows) {
        
    }
    
    void setCell(string cell, int value) {
        mp[cell] = value;
    }
    
    void resetCell(string cell) {
        mp[cell] = 0;
    }
    
    int getValue(string formula) {
        formula = formula.substr(1);
        int left = 0, right = 0;
        int n = formula.size();
        int pos = -1;
        string tmp;
        for (int i = 0; i < n; i++) {
            if (formula[i] == '+') {
                pos = i;
                break;
            }
            tmp += formula[i];
        }
        if (formula[0] >= 'A' && formula[0] <= 'Z') left = mp[tmp];
        else left = stoi(tmp);
        

        tmp = formula.substr(pos + 1);
        if (formula[pos + 1] >= 'A' && formula[pos + 1] <= 'Z') right = mp[tmp];
        else right = stoi(tmp);
        
        return left + right;
    }
};

/**
 * Your Spreadsheet object will be instantiated and called as such:
 * Spreadsheet* obj = new Spreadsheet(rows);
 * obj->setCell(cell,value);
 * obj->resetCell(cell);
 * int param_3 = obj->getValue(formula);
 */
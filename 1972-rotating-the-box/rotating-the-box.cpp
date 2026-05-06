class Solution {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& boxGrid) {
       int row = boxGrid.size();
       int col = boxGrid[0].size();
       vector<vector<char>> grid(col,vector<char>(row));
       for(int i = 0; i<row ; i++){
            for(int j = 0 ; j<col ; j++){
                grid[j][i] = boxGrid[i][j];
            }
        }
       for(auto &i : grid){
            reverse(i.begin(),i.end());
        }
       for(int i = 0 ; i<row ;i++){
            int less = col-1;
            for(int  k = col-1;k>=0;k--){
                if(grid[k][i] == '*'){
                less = k-1;
                continue;
            }
            if(grid[k][i] == '#'){
                grid[k][i] = '.';
                grid[less][i] = '#';
                less--;
            }
        }
       }
       return grid;
    }
};
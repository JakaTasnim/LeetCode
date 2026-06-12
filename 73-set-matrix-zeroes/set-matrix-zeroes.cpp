class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {

        int rows = matrix.size();
        int cols = matrix[0].size();

        int col0 = 1;

        // marking
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){

                if(matrix[i][j]==0){

                    matrix[i][0]=0;

                    if(j!=0)
                        matrix[0][j]=0;
                    else
                        col0=0;
                }
            }
        }

        // fill from back
        for(int i=rows-1;i>=0;i--){
            for(int j=cols-1;j>=1;j--){

                if(matrix[i][0]==0 || matrix[0][j]==0)
                    matrix[i][j]=0;
            }

            if(col0==0)
                matrix[i][0]=0;
        }
    }
};
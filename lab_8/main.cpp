#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

int SelectRow(std::vector<std::vector<double>>& matrix, int columnIndex, int m, int n) {
    double lowestPrice = std::numeric_limits<double>::max();
    int selectedRow = -1;

    for (int row = columnIndex; row < m; ++row) {
        if ((matrix[row][columnIndex] != 0.0) && (matrix[row][n] < lowestPrice)) {
            selectedRow = row;
            lowestPrice = matrix[row][n];
        }
    }

    return selectedRow;
}


void EliminateBelow(std::vector<std::vector<double>>& matrix, int pivotRow,int m, int n) {
    for (int currentRow = pivotRow + 1; currentRow < m; ++currentRow) {
        if (matrix[pivotRow][pivotRow] == 0.0) continue; 
        double factor = matrix[currentRow][pivotRow] / matrix[pivotRow][pivotRow];
        for (int col = pivotRow; col < n; ++col) {
            matrix[currentRow][col] -= factor * matrix[pivotRow][col];
        }
    }
}

int main(){
    int m,n;
    std::cin >> m >> n;
    std::vector<std::vector<double>> matrix(m,std::vector<double>(n+2));
    std::vector<int> ans;
    for(int i=0 ;i<m; i++){
        for(int j=0;j<n+1;j++){
            std::cin >> matrix[i][j];
        }
        matrix[i][n+1] = i;
    }

        for (int i = 0; i < n; ++i) {
        int index = SelectRow(matrix, i,m,n);
        if (index == -1) {
            std::cout << "-1" << std::endl;
            return 0;
        }

        std::swap(matrix[i], matrix[index]);
        ans.push_back(matrix[i][n + 1]);
        EliminateBelow(matrix, i,m,n);
    }

    std::sort(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); ++i) {
        std::cout << ans[i] + 1;
        if (i == ans.size() - 1) {
            std::cout << std::endl;
        } else {
            std::cout << " ";
        }
    }





    return 0;
}
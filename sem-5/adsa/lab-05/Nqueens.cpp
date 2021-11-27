#include <iostream>

bool possible(int n, int board[][10], int row, int col) 
{ 
    int i, j; 
    for (i = 0; i < col; i++) 
        if (board[row][i]) 
            return false; 
 
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--) 
        if (board[i][j]) 
            return false; 
    for (i = row, j = col; j >= 0 && i < n; i++, j--) 
        if (board[i][j]) 
            return false; 
   
    return true; 
} 
 
bool solq(int n, int board[][10], int col) 
{ 
    if (col >= n) 
        return true; 
   
    
    for (int i = 0; i < n; i++) { 
      
        if (possible(n,board, i, col)) { 
          
            board[i][col] = 1; 
   
          
            if (solq(n,board, col + 1)) 
                return true; 
 
            board[i][col] = 0; 
        } 
    } 
   
    
    return false; 
} 
 
int main() 
{ 
    int size{};
    std::cin >> size;
    
    int board[10][10];
    
    for(int i = 0;i < size; i++)
        for(int j = 0;j < size; j++)
            board[i][j] = 0;
    if (solq(size,board, 0) == false) { 
        std::cout << "Solution does not exist"; 
        return 0; 
    } 
   
    for (int i = 0; i < size; i++) { 
        for (int j = 0; j < size; j++) 
            std::cout << board[i][j]; 
        std::cout <<"\n"; 
    } 
    
    return 0; 
} 
#include "sudoku.h"
// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {
  assert(i>=0 && i<9); //i is the CONSTANT row
  for(int j = 0; j < 9; j++){ //j is column, checks if sudoku row...
    if(sudoku[i][j] == val)//if WHOLE ROW OR sudoku[col 1 to 9] == val or not...
    {return 1;} //return 1 if it IS (then CAN'T put)
  }
  return 0; //otherwise return (CAN put in)
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {
  assert(j>=0 && j<9); //j is the constant column
  for(int i = 0; i < 9; i++){ //i is row, checks if sudoku column...
    if(sudoku[i][j] == val)//if WHOLE COLUMN OR sudoku[row 1 to 9] == val or not...
    {return 1;} //return 
  }
  return 0; //otherwise return 0
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
  assert(i>=0 && i<9);
  int startRow = (i / 3) * 3; //declare startRow which will serve as starting value row for the matrix (multiples of 3)
  int startCol = (j / 3) * 3; //declare startCol which will serve as the starting value column for the matrix (multiples of 3)
  for(int row = startRow; row < startRow + 3; row++){ //outer row for loop
    for(int col = startCol; col < startCol + 3; col++){ //inner column for loop
      //!(row == i && col == j)){ //...excluding the particular cell that the program is currently on...
      if(sudoku[row][col] == val) //if sudoku[row][col] == the particular guess value..
      return 1; //return 1
    }
  }
  return 0; //otherwise return 0
}

// Function: is_val_valid
// Return true if the val can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {
  assert(i>=0 && i<9 && j>=0 && j<9);
//for all these functions, if there's at least one duplicate of the value in the bordering row, col, or 3x3 zone...
  if(is_val_in_row(val, i, sudoku) == 0 && is_val_in_col(val, j, sudoku) == 0 && is_val_in_3x3_zone(val, i, j, sudoku) == 0)
    return 1; //return 1
  else
    return 0; //otherwise return 0
}

int solve_sudoku(int sudoku[9][9]){ //function solve_sudoku starts
  int i, j; //declare row and col indices i and j
  int flag = 1; //declare and initialize flag to 1;
  //below basically represents base case
  for(i = 0; i < 9; i++){ //outer row for loop
    for(j = 0; j < 9; j++){ //inner col for loop
      if(sudoku[i][j] == 0) //the moment it finds a non-filled cell (0)...
        {
          flag = 0;//sets flag to 0
          break; //break out of first loop
        }
    }
    if(flag == 0)//break out of outer for loop given condition flag == 0
      break;
  }
  if(flag == 1) //if flag remains 1, then all cells in board is filled with numbers...
    return 1; //thus return 1

  for(int num = 1; num <= 9; num++){ //for loop or try numbers 1-9
    int x = is_val_valid(num, i, j, sudoku); 
    if(x == 1){ //if return value of is_val_valid is 1 or is valid...
      sudoku[i][j] = num; //set the specific sudoku cell to that num
      if (solve_sudoku(sudoku) == 1) //recursive call 
        return 1; //return 1 if solve_sudoku is solved
      sudoku[i][j] = 0; //if it doesn't work out, backtrack by setting the original sudoku cell to unfilled or 0
    }
  }
  return 0;
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}
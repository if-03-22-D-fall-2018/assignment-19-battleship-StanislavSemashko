/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			battleship.c
 * Author(s):		Peter Bauer
 * Due Date:		#due#
 *-----------------------------------------------------------------------------
 * Description:
 * <your description here>
 *-----------------------------------------------------------------------------
*/
#include <stdio.h>

#include "battleship.h"

CellContent my_cell_content [FIELDSIZE][FIELDSIZE];
CellContent other_cell_content [FIELDSIZE][FIELDSIZE];
CellContent guess_cell_content [FIELDSIZE][FIELDSIZE];

void load_game()
{

  FILE* fd_my = fopen("battleship.my", "r");
  FILE* fd_op = fopen("battleship.op", "r");

  fread(my_cell_content,sizeof(CellContent),100,fd_my);
  fread(other_cell_content,sizeof(CellContent),100,fd_op);

for (int i = 0; i < FIELDSIZE; i++)
{
  for (int j = 0; j < FIELDSIZE; j++)
  {
    guess_cell_content[i][j] = Unknown;
  }
}

}

/**
*** @param row The row where we get the shot.
*** @param col The col where we get the shot.
*** @return The value of cell indicated by row and column of the own field (filled
*** with the values of battleship.my). If row/col point outside the field the
*** value OutOfRange is returned.
*/
CellContent get_shot(int row, int col)
{
  if (row >= FIELDSIZE || col >= FIELDSIZE || col < 0 || row < 0)
  {
    return OutOfRange;
  }
  return my_cell_content[row][col];
}

/**
*** Sets the row and column of the my guesses table to the value held in the
*** opponents field. If this is a boat all surrounding cells are marked as water.
*** @param row The row where we place the shot
*** @param col The columnt where we place the shot.
*** @return True if target field is valid, i.e., inside the field, False otherwise.
*/
bool shoot(int row, int col)
{
  if (row >= FIELDSIZE || col >= FIELDSIZE || col < 0 || row < 0)
  {
    return false;
  }
  if (other_cell_content[row][col] == Boat)
  {

    for (int i = row-1; i <= row+1; i++)
    {
      for (int j = col-1; j <= col+1; j++)
      {
        if (i < 0 || i >= FIELDSIZE || j < 0 || j >= FIELDSIZE)
        {

        }
        else if (i != row || col != j)
        {
          guess_cell_content[i][j] = Water;
        }
        else
        {
          guess_cell_content[row][col] = other_cell_content[row][col];
        }

      }
    }
    return true;
  }
  guess_cell_content[row][col] = other_cell_content[row][col];
  return true;
}

/**
*** @param row The row where we want to get our own guess.
*** @param col The column where we want to get our own guess.
*** @return The value of the table with my guesses at row and column. If row/col
*** is outside the field OutOfRange is returned.
*/
CellContent get_my_guess(int row, int col)
{
  if (row >= FIELDSIZE || col >= FIELDSIZE || col < 0 || row < 0)
  {
    return OutOfRange;
  }
  return guess_cell_content[row][col];
}

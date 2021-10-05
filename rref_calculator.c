#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

/***********************************************************************************************/

void printArray (int r, int c, double dat[r][c]);

int main() {

    bool sameSign = false;
    bool algPerformed;
    int rows;
    int cols;
    int currentRow = 0;
    int currentCol = 0;
    float divideBy;
    float multiplyBy;

    printf("Enter the number of rows: ");
    scanf("%d", &rows);

    printf("Enter the number of columns: ");
    scanf("%d", &cols);

    double matrix[rows][cols];
    double tempArray[cols];

    // max number of pivot points is the number of rows and only 1 pivot point per row
    // number in 2d array is representative of pivot column
    int pivotPoint[rows][1];

    // filling pivotPoint with zeroes for later checking of pivot points
    for (int i = 0; i < rows; i++){
        pivotPoint[i][0] = 0;
    }

    // getting numbers for matrix
    printf("Enter %d numbers: ", rows * cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%lf", &matrix[i][j]);
        }
    }

    // loop until echelon form achieved
    while (currentRow < rows && currentCol < cols) {

        algPerformed = false;

        // checking to make sure there is a usable number in diagonal spots of matrix (aka not zero) (positions 11 22 33 etc)
            
        // break out of row swapping if no further row swaps required
        if (matrix[currentRow][currentCol] == 0) {
            for(int i = currentRow; i < rows; i++) {
                
                // one row with usable number is found, swap current row with first row
                if (matrix[i][currentCol] != 0) {
                    for (int k = 0; k < cols; k++) {
                        tempArray[k] = matrix[currentRow][k];
                        matrix[currentRow][k] = matrix [i][k];
                        matrix[i][k] = tempArray[k];
                    }
                }
            }
        }

        // if row was swapped or non-zero value already existed in spot, perform row reducing algorithm
        if (matrix[currentRow][currentCol] != 0) {

            // add currentCol number to correspond with the currentRow (because it has a pivot point if algorithm / swap occurs)
            pivotPoint[currentRow][0] = currentCol + 1;

            // if there is not already a 1 in the current spot, reduce entire row so current spot is 1
            if (matrix[currentRow][currentCol] != 1) {
                divideBy = matrix[currentRow][currentCol];

                for (int i = currentCol; i < cols; i++) {
                    matrix[currentRow][i] /= divideBy;
                }
            }

            for (int i = currentRow; i < rows; i++) {

                // if no more rows, move on
                if (i + 1 == rows) {
                    break;
                }

                // if one of following rows has zero in same column, skip it
                else if (matrix[i + 1][currentCol] == 0) {
                    continue;
                }

                // else row reduce
                else {
                    multiplyBy = matrix[i + 1][currentCol];

                    sameSign =  (((matrix[currentRow][currentCol] < 0) && (matrix[i + 1][currentCol] < 0)) || 
                                ((matrix[currentRow][currentCol] > 0) && (matrix[i + 1][currentCol] > 0))) ? true : false;

                    // subtract rows if same sign
                    if (sameSign) {
                        for (int j = currentCol; j < cols; j++) {
                            matrix[i + 1][j] -= multiplyBy * matrix[currentRow][j];
                        }
                    }

                    // add rows if different signs
                    else {
                        for (int j = currentCol; j < cols; j++) {
                            matrix[i + 1][j] += (-1 * multiplyBy) * matrix[currentRow][j];
                        }
                    }
                }
            }

            algPerformed = true;
        }
        

        // move one column right if no algorithm performed (either reducing or swapping)
        if (!algPerformed) {
            currentCol++;
        }

        // move to next spot diagonal down-right if algorithm was performed
        else {
            currentRow++;
            currentCol++;
        }
    }

    printf("\nEchelon form:\n");
    printArray(rows, cols, matrix);
    printf("\n"); 

    // print pivot point locations
    printf("Pivot point at:\n");
    for (int i = 0; i < rows; i++) {
        if (pivotPoint[i][0] != 0) {
            printf("Row: %d\tCol: %d\n", i + 1, pivotPoint[i][0]);
        }
    }
    printf("\n");

    // converting echelon to row-reduced echelon form
    // sorting through all rows in pivot point except the first row (regardless if row doesn't have pivot point)
    for (int r = rows - 1; r > 0; r--) {
        currentRow = r;
        // using pivot points to go back to start at correct location in matrix
        if (pivotPoint[currentRow][0] != 0) {

            currentCol = pivotPoint[r][0] - 1;

            for (int i = currentRow; i > 0; i--) {
                
                // if one of following rows has zero in same column, skip it
                if (matrix[i - 1][currentCol] == 0) {
                    continue;
                }

                // else row reduce
                else {
                    multiplyBy = matrix[i - 1][currentCol];

                    sameSign =  (((matrix[currentRow][currentCol] < 0) && (matrix[i - 1][currentCol] < 0)) || 
                                ((matrix[currentRow][currentCol] > 0) && (matrix[i - 1][currentCol] > 0))) ? true : false;

                    // subtract rows if same sign
                    if (sameSign) {
                        matrix[i - 1][currentCol] -= multiplyBy * matrix[currentRow][currentCol];
                    }

                    // add rows if different signs
                    else {
                        matrix[i - 1][currentCol] += (-1 * multiplyBy) * matrix[currentRow][currentCol];
                    }
                }
            }
        }
    }

    printf("Row reduced echelon form:\n");
    printArray(rows, cols, matrix);
    printf("\n");

    return 0;
}

/***********************************************************************************************/
//                                      Functions                                              //

// prints a 2d array. args are (rows, columns, matrix)
void printArray(int r, int c, double arr[r][c]) {
    int count;
    for (int i = 0; i < r; i++) {
        count = 0;
        for (int j = 0; j < c; j++) {
            if (count == 0) {
                printf("%5.2lf", arr[i][j]);
                count++;
            }
            else {
                printf(", %5.2lf", arr[i][j]);
            }
        }
        printf("\n");
    }
}
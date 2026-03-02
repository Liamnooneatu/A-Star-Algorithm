#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define ROW 5
#define COL 5

typedef struct {
    int parentX, parentY;
    int f, g, h;
} Cell;

bool isValid(int row, int col) {
    return (row >= 0 && row < ROW && col >= 0 && col < COL);
}

bool isUnBlocked(int grid[ROW][COL], int row, int col) {
    return grid[row][col] == 0;
}

bool isDestination(int row, int col, int dest[2]) {
    return row == dest[0] && col == dest[1];
}

int calculateH(int row, int col, int dest[2]) {
    return abs(row - dest[0]) + abs(col - dest[1]); // Manhattan distance
}

void tracePath(Cell cellDetails[ROW][COL], int dest[2]) {
    int row = dest[0];
    int col = dest[1];

    printf("\nPath:\n");

    while (!(cellDetails[row][col].parentX == row &&
        cellDetails[row][col].parentY == col)) {
        printf("(%d,%d) <- ", row, col);
        int tempRow = cellDetails[row][col].parentX;
        int tempCol = cellDetails[row][col].parentY;
        row = tempRow;
        col = tempCol;
    }

    printf("(%d,%d)\n", row, col);
}

void aStar(int grid[ROW][COL], int start[2], int dest[2]) {
    if (!isValid(start[0], start[1]) || !isValid(dest[0], dest[1])) {
        printf("Invalid start or destination\n");
        return;
    }

    if (!isUnBlocked(grid, start[0], start[1]) ||
        !isUnBlocked(grid, dest[0], dest[1])) {
        printf("Start or destination blocked\n");
        return;
    }

    bool closedList[ROW][COL] = { false };
    Cell cellDetails[ROW][COL];

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            cellDetails[i][j].f = 10000;
            cellDetails[i][j].g = 10000;
            cellDetails[i][j].h = 10000;
            cellDetails[i][j].parentX = -1;
            cellDetails[i][j].parentY = -1;
        }
    }

    int i = start[0], j = start[1];
    cellDetails[i][j].f = 0;
    cellDetails[i][j].g = 0;
    cellDetails[i][j].h = 0;
    cellDetails[i][j].parentX = i;
    cellDetails[i][j].parentY = j;

    while (true) {
        int minF = 10000;
        int row = -1, col = -1;

        // Find lowest F cost
        for (int r = 0; r < ROW; r++) {
            for (int c = 0; c < COL; c++) {
                if (!closedList[r][c] && cellDetails[r][c].f < minF) {
                    minF = cellDetails[r][c].f;
                    row = r;
                    col = c;
                }
            }
        }

        if (row == -1) {
            printf("No path found\n");
            return;
        }

        closedList[row][col] = true;

        int directions[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

        for (int d = 0; d < 4; d++) {
            int newRow = row + directions[d][0];
            int newCol = col + directions[d][1];

            if (isValid(newRow, newCol)) {
                if (isDestination(newRow, newCol, dest)) {
                    cellDetails[newRow][newCol].parentX = row;
                    cellDetails[newRow][newCol].parentY = col;
                    tracePath(cellDetails, dest);
                    return;
                }
                else if (!closedList[newRow][newCol] &&
                    isUnBlocked(grid, newRow, newCol)) {

                    int gNew = cellDetails[row][col].g + 1;
                    int hNew = calculateH(newRow, newCol, dest);
                    int fNew = gNew + hNew;

                    if (cellDetails[newRow][newCol].f == 10000 ||
                        cellDetails[newRow][newCol].f > fNew) {

                        cellDetails[newRow][newCol].f = fNew;
                        cellDetails[newRow][newCol].g = gNew;
                        cellDetails[newRow][newCol].h = hNew;
                        cellDetails[newRow][newCol].parentX = row;
                        cellDetails[newRow][newCol].parentY = col;
                    }
                }
            }
        }
    }
}

int main() {
    int grid[ROW][COL] = {
        {0,0,0,0,0},
        {0,1,1,1,0},
        {0,0,0,1,0},
        {0,1,0,0,0},
        {0,0,0,0,0}
    };

    int start[2] = { 0, 0 };
    int dest[2] = { 4, 4 };

    aStar(grid, start, dest);

    return 0;
}
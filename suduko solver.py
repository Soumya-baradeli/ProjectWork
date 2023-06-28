m=9
def puzzel(a):
    for i in range(m):
        for j in range(m):
            print(a[i][j],end=" ")
        print( )
def solve(grid,row,col,num):
    for x in range(m):
        if grid[row][x]==num:
            return False
    for x in range(m):
        if grid[x][col]==num:
            return False
    startrow=row-row%3
    startcol=col-col%3
    for i in range(3):
        for j in range(3):
            if grid[i+startrow][j+startcol]==num:
                return False
    return True
def suduko(grid,row,col):
    if row==m-1 and col==m:
        return True
    if col==m:
        row+=1
        col=0
    if grid[row][col]>0:
        return suduko(grid,row,col+1)
    for num in range(1,m+1,1):
        if solve(grid,row,col,num):
            grid[row][col]=num
            if suduko(grid,row,col+1):
                return True
        grid[row][col]=0
    return False

grid = [[2, 5, 0, 0, 3, 0, 9, 0, 1],
        [0, 1, 0, 0, 0, 4, 0, 0, 0],
    [4, 0, 7, 0, 0, 0, 2, 0, 8],
    [0, 0, 5, 2, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 9, 8, 1, 0, 0],
    [0, 4, 0, 0, 0, 3, 0, 0, 0],
    [0, 0, 0, 3, 6, 0, 0, 7, 2],
    [0, 7, 0, 0, 0, 0, 0, 0, 3],
    [9, 0, 3, 0, 0, 0, 6, 0, 4]]
 
if (suduko(grid, 0, 0)):
    puzzel(grid)
else:
    print("Solution does not exist:(")

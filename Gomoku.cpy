MAX_ROW=15;
MAX_COL=15;
PLAYER=0;
COMPUTER=1;
EMPTY=-1;
LAST_POS=[0,0];

fn initBoardList()
{
    boardList=[];
    for(i=0;i<MAX_ROW;i++)
    {
        towList=[EMPTY]*MAX_COL;
        boardList.append(towList);
    }
    return boardList;
}

chessBoardList=initBoardList();

fn num2str(num)
{
    if(num<10)
    {
        return " "+str(num);
    }
    else
    {
        return str(num);
    }
}

fn board()
{
    upStr="";
    for(i=1;i<=MAX_COL;i++)
    {
        upStr+="  "+num2str(i);
    }
    upStr+="\n";
    edgeStr="  +---"+"+---"*14+"+\n";
    boardStr=" "+upStr;
    for(i=1;i<=MAX_ROW;i++)
    {
        lineStr=num2str(i);
        for(j=1;j<=MAX_COL;j++)
        {
            lineStr+="| ";
            if(chessBoardList[i-1][j-1]==EMPTY)
            {
                lineStr+=" ";
            }
            elif(chessBoardList[i-1][j-1]==PLAYER)
            {
                lineStr+="O";
            }
            elif(chessBoardList[i-1][j-1]==COMPUTER)
            {
                lineStr+="X";
            }
            lineStr+=" ";
        }
        lineStr+="|\n";
        boardStr+=edgeStr+lineStr;
    }
    boardStr+=edgeStr;
    return boardStr;
}

fn isInBoard(row,col)
{
    return (row>=1)&&(row<=MAX_ROW)&&(col>=1)&&(col<=MAX_COL);
}

fn isOccupied(row,col)
{
    return (chessBoardList[row-1][col-1]!=EMPTY);
}

fn setChess(row,col,obj)
{
    chessBoardList[row-1][col-1]=obj;
    LAST_POS[0]=row;
    LAST_POS[1]=col;
    return null;
}

fn checkRow(LAST_ROW,LAST_COL)
{
    LAST_OBJ=chessBoardList[LAST_ROW-1][LAST_COL-1];
    for(move=0;move<=4;move++)
    {
        count=0;
        for(i=LAST_COL;i>=LAST_COL-4;i--)
        {
            if(isInBoard(LAST_ROW,i+move))
            {
                if(chessBoardList[LAST_ROW-1][i+move-1]==LAST_OBJ)
                {
                    count++;
                }
            }
        }
        if(count==5)
        {
            return LAST_OBJ;
        }
    }
    return null;
}

fn checkCol(LAST_ROW,LAST_COL)
{
    LAST_OBJ=chessBoardList[LAST_ROW-1][LAST_COL-1];
    for(move=0;move<=4;move++)
    {
        count=0;
        for(i=LAST_ROW;i>=LAST_ROW-4;i--)
        {
            if(isInBoard(i+move,LAST_COL))
            {
                if(chessBoardList[i+move-1][LAST_COL-1]==LAST_OBJ)
                {
                    count++;
                }
            }
        }
        if(count==5)
        {
            return LAST_OBJ;
        }
    }
    return null;
}

fn checkUpDiag(LAST_ROW,LAST_COL)
{
    LAST_OBJ=chessBoardList[LAST_ROW-1][LAST_COL-1];
    for(move=0;move<=4;move++)
    {
        count=0;
        for(i=LAST_ROW,j=LAST_COL;i>=LAST_ROW-4,j<=LAST_COL+4;i--,j++)
        {
            if(isInBoard(i+move,j-move))
            {
                if(chessBoardList[i+move-1][j-move-1]==LAST_OBJ)
                {
                    count++;
                }
            }
        }
        if(count==5)
        {
            return LAST_OBJ;
        }
    }
    return null;
}

fn checkDownDiag(LAST_ROW,LAST_COL)
{
    LAST_OBJ=chessBoardList[LAST_ROW-1][LAST_COL-1];
    for(move=0;move<=4;move++)
    {
        count=0;
        for(i=LAST_ROW,j=LAST_COL;i<=LAST_ROW+4,j<=LAST_COL+4;i++,j++)
        {
            if(isInBoard(i-move,j-move))
            {
                if(chessBoardList[i-move-1][j-move-1]==LAST_OBJ)
                {
                    count++;
                }
            }
        }
        if(count==5)
        {
            return LAST_OBJ;
        }
    }
    return null;
}

fn checkWinner()
{
    result=checkRow(LAST_POS[0],LAST_POS[1]);
    if(result!=null)
    {
        return result;
    }
    result=checkCol(LAST_POS[0],LAST_POS[1]);
    if(result!=null)
    {
        return result;
    }
    result=checkUpDiag(LAST_POS[0],LAST_POS[1]);
    if(result!=null)
    {
        return result;
    }
    result=checkDownDiag(LAST_POS[0],LAST_POS[1]);
    if(result!=null)
    {
        return result;
    }
    return null;
}

fn playerTurn()
{
    while(true)
    {
        print("input: row-col\n");
        print("Computer : ",LAST_POS[0],"-",LAST_POS[1],"\n");
        pos=input("Your turn: ").split("-");
        if(pos.len()!=2)
        {
            print("Invalid input!\n");
            continue;
        }
        row=int(pos[0]);
        col=int(pos[1]);
        if(!isInBoard(row,col))
        {
            print("Invalid input!\n");
            continue;
        }
        elif(isOccupied(row,col))
        {
            print("Invalid input!\n");
            continue;
        }
        setChess(row,col,PLAYER);
        break;
    }
    return null;
}

fn evalPosition(row,col,obj)
{
    dirs = [[0,1],[1,0],[1,1],[1,-1]];
    totalScore = 0;

    for (dir=0;dir<4;dir++) 
    {
        consecutive = 1;
        blocked = [false, false];
        for (step = 1; true ;++step) 
        {
            nrow = row - dirs[dir][0] * step;
            ncol = col - dirs[dir][1] * step;
            if(!isInBoard(nrow,ncol))
            {
                blocked[0] = true;
                break;
            }
            elif(chessBoardList[nrow-1][ncol-1]!=obj)
            {
                if(chessBoardList[nrow-1][ncol-1]==EMPTY)
                {
                    blocked[0] = false;
                }
                else
                {
                    blocked[0] = true;
                }
                break;
            }
            consecutive++;
        }

        for (step = 1; true ; ++step)
        {
            nrow = row + dirs[dir][0] * step;
            ncol = col + dirs[dir][1] * step;
            if(!isInBoard(nrow,ncol))
            {
                blocked[1] = true;
                break;
            }
            elif(chessBoardList[nrow-1][ncol-1]!=obj)
            {
                if(chessBoardList[nrow-1][ncol-1]==EMPTY)
                {
                    blocked[1] = false;
                }
                else
                {
                    blocked[1] = true;
                }
                break;
            }
            consecutive++;
        }

        if (consecutive >= 5) 
        {
            totalScore += 1000000;
        } 
        else 
        {
            if (consecutive == 4) 
            {
                if (!blocked[0] && !blocked[1])
                {
                    totalScore += 100000;
                }
                elif (!blocked[0] || !blocked[1])
                {
                    totalScore += 5000
                }
            } 
            elif (consecutive == 3) 
            {
                if (!blocked[0] && !blocked[1])
                {
                    totalScore += 6000;
                }
                elif (!blocked[0] || !blocked[1])
                {
                    totalScore += 400;
                }
            } 
            elif (consecutive == 2) 
            {
                if (!blocked[0] && !blocked[1])
                {
                    totalScore += 200;
                }
                elif (!blocked[0] || !blocked[1])
                {
                    totalScore += 50;
                }
            } 
            elif (consecutive == 1) 
            {
                if (!blocked[0] && !blocked[1])
                {
                    totalScore += 100;
                }
                elif (!blocked[0] || blocked[1])
                {
                    totalScore += 50;
                }
                elif(blocked[0] || !blocked[1])
                {
                    totalScore += 50;
                }
                elif(blocked[0] && blocked[1])
                {
                    totalScore -= 1000;
                }
            }
        }
    }
    return totalScore;
}

fn findBestPos()
{
    MAX_SCORE=-1000000;
    BEST_MOVE=[-1,-1];

    for (i = 1; i <= MAX_ROW; ++i) 
    {
        for (j = 1; j <= MAX_COL; ++j) 
        {
            if (chessBoardList[i-1][j-1] != EMPTY)
            {
                continue;
            }

            attackScore = evalPosition(i, j, COMPUTER);
            defendScore = evalPosition(i, j, PLAYER);
            totalScore = attackScore + defendScore;

            if (totalScore >= MAX_SCORE) 
            {
                MAX_SCORE = totalScore;
                BEST_MOVE[0] = i;
                BEST_MOVE[1] = j;
            }
        }
    }
    return BEST_MOVE;
}

fn computerTurn()
{
    BEST_POS=findBestPos();
    row=BEST_POS[0];
    col=BEST_POS[1];
    if(isInBoard(row,col))
    {
        setChess(row,col,COMPUTER);
    }
    return null;
}

fn isFull()
{
    for(i=1;i<=MAX_ROW;i++)
    {
        for(j=1;j<=MAX_COL;j++)
        {
            if(chessBoardList[i-1][j-1]==EMPTY)
            {
                return false;
            }
        }
    }
    return true;
}

fn game()
{
    while(true)
    {
        system("cls");
        print(board());

        playerTurn();
        system("cls");
        print(board());

        if(checkWinner()!=null)
        {
            return PLAYER;
        }

        computerTurn();
        system("cls");
        print(board());

        if(checkWinner()!=null)
        {
            return COMPUTER;
        }

        if(isFull())
        {
            return PLAYER;
        }
    }
    return PLAYER;
}

while(true)
{
    print("Gomoku Game: Human vs. Computer\n");
    print("+--------------+\n");
    print("|     input    |\n");
    print("+--------------+\n");
    print("| '1' to start |\n");
    print("| '2' to exit  |\n");
    print("+--------------+\n");
    while(true)
    {
        inp=input("Please input: ");
        if(inp=="1")
        {
            if(game()==PLAYER)
            {
                print("you are winner!\n");
            }
            else
            {
                print("you are loser!\n");
            }
            system("pause");
            system("cls");
            break;
        }
        elif(inp=="2")
        {
            exit();
        }
        else
        {
            print("Invalid input!\n");
        }
    }
}

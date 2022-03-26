//Lalith Vaishnav Elangovan
//This is the function to check the input and if ships overlap
bool validityCheck(int rows, int columns, int orientation, int *size,int board[BOARDROWS+1][BOARDCOLS+1],bool getUserInput){
//True false variable to help within the ppopulating function    
    bool flag=false;
//If statement to check inputs of the user    
    if ((rows<1 || rows > 9) || (orientation > 1 || orientation <0) || (columns < 1 || columns > 11)){
        if (getUserInput==true)
            printf("Invalid Input\n");
        *size=*size+1;
        flag=true;
    }
//If statement to check each orientation and if the ship can fit in space        
    else if (orientation==1&&(rows+(*size)-1)>9){
        if (getUserInput==true)
            printf("Invalid Input\n");
        *size=*size+1;
        flag=true;
    }    
    else if (orientation==0&&(columns+(*size)-1)>11){
        if (getUserInput==true)
            printf("Invalid Input\n");
        *size=*size+1;
        flag=true;
    }
//If statement to check conflicts with other ships for each orientation    
    if (orientation==1 && flag==false){
        for (int vertical= 0; vertical <= (*size)-1; vertical++){
            if (board[rows+vertical][columns]!=0){
                if (getUserInput==true)
                    printf("Conflicts with ship already placed\n");
                (*size)=(*size)+1;
                flag=true;
                break;
            }
        }}
    else if (orientation==0 && flag==false){
        for (int horizontal= 0; horizontal <= (*size)-1; horizontal++){
            if (board[rows][columns+horizontal]!=0){
                if (getUserInput==true)
                    printf("Conflicts with ship already placed\n");
                (*size)=(*size)+1;
                flag=true;
                break;
            }
        }
    }
    return flag;
}

void populateBoard(bool getUserInput, int board[BOARDROWS+1][BOARDCOLS+1]){

    //******* YOUR CODE GOES HERE TO POPULATE THE BOARDS
    int rows, columns, orientation,size;
    bool flag=false;
//To determine if to populate user board or computer board    
    if (getUserInput==1)
    { printf ("Rows are 1 - 9, Columns are 1 - 11\nOrientation is 0 for across, 1 for down\n");
//for loop to repeat the printf statement and to go from 5 to 1
    for (size = 5; size > 0; size--)
    {
        printf("Give starting row, starting column and orientation (3 inputs) for ship of size=%d:",size);
        scanf("%d %d %d", &rows,&columns,&orientation);
//Calling the checking function, for the inputs        
        flag=validityCheck(rows,columns,orientation,&size,board,getUserInput);
//if statement for no errors and to place the boat in either orientation        
        if (flag==false){
        if (orientation==1){
            for (int vertical= 0; vertical <= size-1; vertical++)
            {
                board[rows+vertical][columns]= size;
            }        
        }
        else{
            for (int horizontal= 0; horizontal <= size-1; horizontal++)
            board[rows][columns+horizontal] = size;
        }  
        }
    }
    }
//The other option which is to poulate the computer board    
    else{
        for (size = 5; size > 0; size--){
//The functions used are to get the random numbers to populate the computer board
            rows=getRand(1,9);
            columns=getRand(1,11);
            orientation=getRand(0,1);
//Calls function to ensure no conflicts with ships and populates the computer board            
            flag=validityCheck(rows,columns,orientation,&size,board,getUserInput);
            if (flag==false){
                if (orientation==1){
                    for (int vertical= 0; vertical <= size-1; vertical++)
                    {
                        board[rows+vertical][columns]= size;
                    }        
                }
                else{
                    for (int horizontal= 0; horizontal <= size-1; horizontal++)
                        board[rows][columns+horizontal] = size;
                }  
            }
        }
    }
}

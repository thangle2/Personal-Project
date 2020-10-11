class Grid{
  int[][] grid;
  int row,answer,point;
  boolean endgame;
  private int move;
  ArrayList<Integer> result=new ArrayList<Integer>();
  NumberGenerator numbergenerator= new NumberGenerator();
  MoveRight moveright= new MoveRight();
  MoveLeft moveleft= new MoveLeft();
  MoveUp moveup= new MoveUp();
  MoveDown movedown= new MoveDown();

  public Grid(){
    grid=new int[4][4];
    for(int i=0;i<4;i++){
      for (int j=0;j<4;j++){
        grid[i][j]=0;
      }

  }
     for(int j=0;j<2;j++){
   row=(int)random(0,4);
   result=numbergenerator.alltheZeroes(row,grid);
   answer=numbergenerator.randomize(result);
   grid[row][answer]=(int)(random(1,3))*2;
   }
    move=0;
    point=0;
}
  public Grid(int[][] grid){
    this.grid=grid;
  }
 void makenumber(){
       for(int x=0;x<4;x++){
      for (int y=0;y<4;y++){
        if((grid[x][y]>0)&&(grid[x][y]<10)){
        fill(255,255,204);
        stroke(0);
        rect(x*100,y*100,100,100);
        textSize(100);
        fill(255,204,153);
        text(grid[x][y],x*100+17.5,y*100+90);
        }
        else if((grid[x][y]>0) && (grid[x][y]>10)&& (grid[x][y]<100)){
         fill(204,255,255);
        stroke(0);
        rect(x*100,y*100,100,100);
        textSize(75);
        fill(204,204,255);
        text(grid[x][y],x*100,y*100+80);
        }
        else if((grid[x][y]>0) && (grid[x][y]>100)&&(grid[x][y]<1000)){
        fill(153,255,255);
        stroke(0);
        rect(x*100,y*100,100,100);
        textSize(50);
        fill(0,0,255);
        text(grid[x][y],x*100,y*100+70);
        }
        else if((grid[x][y]>0) && (grid[x][y]>1000)){
        fill(204,255,204);
        stroke(0);
        rect(x*100,y*100,100,100);
        textSize(35);
        fill(153,204,255);
        text(grid[x][y],x*100+5,y*100+65);
      }
         }
       }
 }
 int getMove(){
   return move;
 }
   void display(){
  
    for(int i=0;i<4;i++){
      for (int j=0;j<4;j++){
        fill(255);
        stroke(0);
        rect(i*100,j*100,100,100);
}
    }
    textSize(70);
    fill(0);
    text("Move:",0,500);
    textSize(70);
    fill(0);
    text(move,200,500);
   }
 void newnumber(){
   row=(int)random(0,4);
   result=numbergenerator.alltheZeroes(row,grid);
   while(result.size()==0){
   row=(int)random(0,4);
   result=numbergenerator.alltheZeroes(row,grid);
   }
   answer=numbergenerator.randomize(result);
   grid[row][answer]=(int)(random(1,3))*2;
   textSize(100);
   fill(0);
  text(grid[row][answer],row*100,answer*100);
 
 }
 void moveRight(){
   if((moveright.slideable(grid))||(moveright.combinalbe(grid))){
      moveright.slide(grid);   
     moveright.slide(grid);
     moveright.slide(grid);
   moveright.combine(grid,point);
        newnumber();
         move+=1;
   }
 }
 void moveLeft(){
    if((moveleft.slideable(grid))||(moveleft.combinalbe(grid))){
     moveleft.slide(grid);  
      moveleft.slide(grid);
   moveleft.slide(grid);
   moveleft.combine(grid,point);
     newnumber();
      move+=1;
   }
   }
 
 void moveUp(){
    if((moveup.slideable(grid)) || (moveup.combinalbe(grid))){
   moveup.slide(grid);
    moveup.slide(grid);
    moveup.slide(grid);
    moveup.combine(grid,point);
    newnumber();
     move+=1;
    }
 }
 void moveDown(){
   if((movedown.slideable(grid)) || (movedown.combinalbe(grid))){
    movedown.slide(grid); 
    movedown.slide(grid);
    movedown.slide(grid);
   movedown.combine(grid,point);
   newnumber();
    move+=1;
   }

 }
 boolean checkerBoardFill(){
    if((!movedown.slideable(grid)) && (!movedown.combinalbe(grid)) && (!moveup.slideable(grid)) && (!moveup.combinalbe(grid))&&(!moveleft.slideable(grid))&&(!moveleft.combinalbe(grid))&&(!moveright.slideable(grid))&&(!moveright.combinalbe(grid))){
     return true;
    }
    else{
    return false;
    }
 }
boolean winGame(){
   for(int i=0;i<4;i++){
      for (int j=0;j<4;j++){
        if (grid[i][j]==2048){
         return true; 
        }
   
}
   }
   return false;
}
}
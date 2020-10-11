class MoveLeft implements Movement{
  
    void slide(int[][] grid){
        for(int i=3;i>0;i--){
      for (int j=0;j<4;j++){
       if(grid[i-1][j]==0){
        grid[i-1][j]=grid[i][j];
        grid[i][j]=0;
      }
      }
    }
   }
   void combine(int[][] grid,int point){
   for(int i=0;i<3;i++){
        for (int j=3;j>=0;j--){
          if(grid[i][j]==grid[i+1][j]){
            point+=grid[i][j] +grid[i+1][j];
            grid[i][j]= grid[i][j] +grid[i+1][j];
            grid[i+1][j]=0;
            slide(grid);
          }
     }
   }
   }
   boolean slideable(int[][] grid){
     for(int i=0;i<3;i++){
      for (int j=0;j<4;j++){
       if((grid[i+1][j]>0)&&(grid[i][j]==0)){
         return true;
       }
      }
     }
     return false;
   }
    boolean combinalbe(int[][] grid){
       for(int i=0;i<3;i++){
        for (int j=3;j>=0;j--){
          if((grid[i][j]>0)&&(grid[i][j]==grid[i+1][j])){
            return true;
          }}}
          return false;
    }
}
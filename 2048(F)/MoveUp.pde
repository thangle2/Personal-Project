class MoveUp implements Movement{
   void slide(int[][] grid){
        for(int i=0;i<4;i++){
      for (int j=3;j>0;j--){
       if(grid[i][j-1]==0){
        grid[i][j-1]=grid[i][j];
        grid[i][j]=0;
      }
      }
      
    }
    ;
   }
   void combine(int[][] grid,int point){
        for(int i=3;i>=0;i--){
        for (int j=0;j<3;j++){
          if(grid[i][j]==grid[i][j+1]){
            point+=grid[i][j] +grid[i][j+1];
            grid[i][j+1]= grid[i][j] +grid[i][j+1];
            grid[i][j]=0;
            slide(grid);
         }
     }
   }
}
boolean slideable(int[][] grid){
  for(int i=0;i<4;i++){
      for (int j=3;j>0;j--){
       if((grid[i][j]>0)&&(grid[i][j-1]==0)){
         return true;
       }}}
       return false;
}
 boolean combinalbe(int[][] grid){
   for(int i=3;i>=0;i--){
        for (int j=3;j>0;j--){
          if((grid[i][j]>0)&&(grid[i][j]==grid[i][j-1])){
            return true;
          }}}
          return false;
 }
}
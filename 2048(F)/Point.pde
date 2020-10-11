class Point{
  int point;
  public Point(){
    point=0;
  }
  void startingPoint(int[][] grid){
     for(int x=0;x<4;x++){
      for (int y=0;y<4;y++){
        point+=grid[x][y];
      }
     }
  }
}
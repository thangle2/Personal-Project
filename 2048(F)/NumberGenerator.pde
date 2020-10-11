class NumberGenerator{
   int random1,random2;
  public NumberGenerator(){
    random1=((int)random(1,3))*2;
    random2=((int)random(1,3))*2;
  }
  ArrayList<Integer> alltheZeroes(int row,int[][] array){
    ArrayList<Integer> result=new ArrayList<Integer>();
    for(int i=0;i<4;i++){
      if (array[row][i]==0){
        result.add(i);
    }
    }
    return result;
 
  }
  
  int randomize(ArrayList<Integer> array){
    int index=(int)random(0,array.size());  
    int result=array.get(index);
    return result;
    
  }
  
  
}
Grid grid;
NumberGenerator numbergenerator;
MoveRight moveright;
Point point;
boolean start;
void setup(){
  size(400,500);
  frameRate(25);
    grid=new Grid();
    start=false;
  numbergenerator= new NumberGenerator();
   point=new Point();
}
void draw(){
   if(start==true){
    background(255);
  grid.display();
  grid.makenumber();
   }
  if(grid.checkerBoardFill()){
   background(0);
   textSize(35);
   fill(0,255,0);
   text("Game Over",100,100);
   textSize(75);
   fill(255,0,0);
   text("YOU",120,180);
   textSize(75);
   fill(255,0,0);
   text("FAILED!",70,255);
    textSize(100);
   fill(255,0,0);
   text("</3",100,350);
   textSize(75);
   fill(255);
   text("Move:"+grid.getMove(),0,450);
  }
    if(grid.winGame()){
   background(255,255,0);
   textSize(35);
   fill(0);
   text("Congratulation",80,100);
   textSize(75);
   fill(0,0,255);
   text("YOU",120,180);
   textSize(75);
   fill(0,255,0);
   text("WON! ",110,255);
    textSize(75);
   fill(255,0,0);
   text("<3",130,330);
    textSize(0);
   fill(0);
   text("Move:"+grid.getMove(),0,450);
  }
   
  
   if(start==false){
    background(224,224,224);
    textSize(35);
     fill(255,153,153);
     text("Welcome to 2048!",55,150);
     textSize(35);
     fill(255,0,0);
     text("Press 'S' to start ",70,250);
   }
}
void keyPressed(){
  if(keyCode== RIGHT){
    if(start==true){
    grid.moveRight();
    }
  }
  if(keyCode== LEFT){
    if(start==true){
    grid.moveLeft();
    }
  }
   if(keyCode== UP){
     if(start==true){
    grid.moveUp();
     }
  }
    if(keyCode== DOWN){
      if(start==true){
    grid.moveDown();
      }
  }
  if (keyCode=='S'){
   start=true; 
  }
}
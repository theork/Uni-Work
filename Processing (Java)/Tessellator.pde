final int CON_WIDTH = 5;
final int CON_HEIGHT = 5;
final int WALL_WIDTH = 5;
final int WALL_HEIGHT = 8;
int [][] controller = createBlank(CON_WIDTH, CON_HEIGHT);
int [][] wallpaper = createWallpaper(controller);
int colour = 0;

void setup() {
  size(1000, 1000);
  background(255);
  
  update();
}

void draw(){  
}

void update(){
  drawController(controller);
  wallpaper = createWallpaper(controller);
  drawWallpaper(wallpaper);
}

void drawController(int[][] array) {
  stroke(150);
  fill(255);

  for (int i = 0; i < CON_WIDTH; i++) {
    for (int j = 0; j < CON_HEIGHT; j++) {
      setColour(array[i][j]);

      int x = i * 10 + 10;
      int y = j* 10 + 10;

      rect(x, y, 10, 10);
    }
  }
  
  int startY = (CON_HEIGHT * 10) + 30;
  setColour(colour);
  rect(10, startY, 30, 30);
}

int[][] createWallpaper(int[][] array){
  int totalW = WALL_WIDTH * CON_WIDTH;
  int totalH = WALL_HEIGHT * CON_HEIGHT;
  int wCount = 0;
  int hCount = 0;
  int [][] wallArray = new int[totalW][totalH];
  
  for(int i = 0; i < totalW; i++){
    for(int j = 0; j < totalH; j++){
      wallArray[i][j] = array[wCount][hCount];
      hCount++;
      
      if(hCount >= CON_HEIGHT){
        hCount = 0;
      }      
    }
    wCount++;
    if(wCount >= CON_WIDTH){
        wCount = 0;
      }    
  }
  return wallArray;
}

void drawWallpaper(int[][] array){
  int totalW = WALL_WIDTH * CON_WIDTH;
  int totalH = WALL_HEIGHT * CON_HEIGHT;
  int startX = (CON_WIDTH * 10) + 30;
  
  noStroke();
  for(int i = 0; i < totalW; i++){
    for(int j = 0; j < totalH; j++){
      
      setColour(array[i][j]);

      int x = i * 10 + startX;
      int y = j * 10 + 10;

      rect(x, y, 10, 10);
    }
  }
}

int[][] createBlank(int w, int h){
  int[][] array = new int[w][h];
  for(int i = 0; i < w; i++){
    for(int j = 0; j < h; j++){
      array[i][j] = 0;
    }
  }
  return array;
}

void mouseClicked(){  
  int xPos = floor(mouseX / 10);
  int yPos = floor(mouseY / 10);
  //println("x= " + xPos + " y= "+ yPos);
  
  if(xPos > 0 && yPos > 0 && xPos <= CON_WIDTH && yPos <= CON_HEIGHT){
    if(controller[xPos - 1][yPos - 1] == 0){
      controller[xPos - 1][yPos - 1] = colour;
    }
    else{
      controller[xPos - 1][yPos - 1] = 0;
    }
    
    update();       
  }
  
  int colourBoxY = (CON_HEIGHT * 10) + 30;
  if((xPos*10 > 10 && xPos*10 < 30) && (yPos*10 > colourBoxY && yPos*10 < colourBoxY + 30)){
    if(mouseButton == LEFT){
      colour++;
      if(colour > 8){
        colour = 0;
      }
    }
    else if(mouseButton == RIGHT){
      colour--;
      if(colour < 0){
        colour = 8;
      }
    }
    
    update();
  }
}

void setColour(int col){
  switch(col){
    case 0:
      fill(255);
      break;
    case 1:
      fill(0);
      break;
    case 2:
      fill(255, 0, 0);
      break;
    case 3:
      fill(255, 127, 0);
      break;
    case 4:
      fill(255, 255, 0);
      break;
    case 5:
      fill(0, 255, 0);
      break;
    case 6:
      fill(0, 0, 255);
      break;
    case 7:
      fill(75, 0, 130);
      break;
    case 8:
      fill(148, 0, 211);
      break;
    default:
      fill(255);    
  }
}

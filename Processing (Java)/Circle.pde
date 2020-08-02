final int arrayWidth = 50;
final int arrayHeight = 50;

void setup() {
  size(500, 500);
  background(255);
  stroke(200);
  int [][] myData = new int[arrayWidth][arrayHeight];
  myData = myClearData(myData);
  myData = myCircle(myData, 20,20, 21);
  myDraw(myData);
}

void myDraw(int [][] array2d) {
  int x, y, i, j;
  for (i = 0; i < arrayWidth; i++) {
    for (j = 0; j < arrayHeight; j++) {
      if (array2d[i][j] == 0) {
        fill(255);
      } else if (array2d[i][j] == 1) {
        fill(0);
      }
      x = i * 10;
      y = j * 10;

      rect(x, y, 10, 10);
    }
  }
}

int[][] myClearData(int [][] myArray) {
  int i, j;
  for (i = 0; i < arrayWidth; i++) {
    for (j = 0; j < arrayHeight; j ++) {
      myArray[i][j] = 0;
    }
  }
  return myArray;
}

int[][] myRandomSet(int[][] myArray, int points) {
  int count = 0;

  while (count < points) {
    int x = (int) (random(arrayWidth));
    int y = (int) (random(arrayHeight));

    if (myArray[x][y] == 0) {
      myArray[x][y] = 1;
      count++;
    }
  }
  return myArray;
}

int [][] myRect(int[][]myArray, int startX, int startY, int w, int h) {
  int i, j;
  for (i = startX; i < (w + startX); i++) {
    for (j = startY; j < (h + startY); j++) {
      myArray[i][j] = 1;
    }
  } 
  return myArray;
}

int [][] myLine(int[][] myArray, int x1, int y1, int x2, int y2){
  if(x1 > arrayWidth || x2 > arrayWidth || y1 > arrayWidth || y2 > arrayWidth){
    println("ERROR values greater than array width");
    return myArray;
  }
  else if(x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0){
    println("ERROR values less than array");
    return myArray;
  }
  else if(x1 > arrayHeight || x2 > arrayHeight || y1 > arrayHeight || y2 > arrayHeight){
    println("ERROR values greater than array height");
    return myArray;
  }
  double dy = y2 - y1;
  double dx = x2 - x1;
  double m = dy / dx;
  double c = y1 - m * x1;
    
  for(int x = x1; x < x2; x++){    
    double y = m * x + c ;
    int ry = round((float)(y));
    myArray[x][ry] = 1;
  }
  
  return myArray;
}

int[][] myCircle(int[][] myArray, int startX, int startY, float r){
  
  if(startX + r > arrayWidth || startY + r > arrayHeight){
    println("ERROR - array size too small");
    return myArray;
  }
  else if(startX - r < 0 || startY - r < 0){
    println("ERROR - inputted circle less than zero");
    return myArray;
  }
  
  for(int i = 0; i < 360; i++){
    float rad = radians(i);
    int x = (int)(startX + cos(rad) * r);
    int y = (int)(startY + sin(rad) * r);
    myArray[x][y] = 1;
  }
  
  return myArray;
}

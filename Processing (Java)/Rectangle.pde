final int arrayWidth = 50;
final int arrayHeight = 50;

void setup(){
  size(500,500);
  background(255);
  stroke(200);
  int [][] myData = new int[arrayWidth][arrayHeight];
  myData = myClearData(myData);
  myData = myRect(myData, -1, 0, 50, 50);
  myDraw(myData);
}

void myDraw(int [][] array2d){
  int x,y,i,j;
  for(i = 0; i < arrayWidth; i++){
    for(j = 0; j < arrayHeight; j++){
      if(array2d[i][j] == 0){
        fill(255);
      }
      else if(array2d[i][j] == 1){
        fill(0);
      }
      x = i * 10;
      y = j * 10;
      
      rect(x,y,10,10);
    }
  }
}

int[][] myClearData(int [][] myArray){
  int i,j;
  for(i = 0; i < arrayWidth; i++){
    for(j = 0; j < arrayHeight; j ++){
      myArray[i][j] = 0;
    }
  }
  return myArray;
}

int[][] myRandomSet(int[][] myArray, int points){
  int count = 0;
  
  while(count < points){
    int x = (int) (random(arrayWidth));
    int y = (int) (random(arrayHeight));
    
    if(myArray[x][y] == 0){
      myArray[x][y] = 1;
      count++;
    }    
  }
  return myArray;
}

int [][] myRect(int[][]myArray, int startX, int startY, int w, int h){
  if(startX + w > arrayWidth || startY + h > arrayHeight){
    println("ERROR - values greater than array dimensions");
    return myArray;
  }
  else if(startX < 0 || startY < 0){
    println("ERROR - start less than array");
    return myArray;
  }
  else if(w < 1 || h < 1){
    println("ERROR - height and width cannot be that small");
  }
  
  int i, j;
  for(i = startX; i < (w + startX) ; i++){
    for(j = startY; j < (h + startY); j++){
      myArray[i][j] = 1;
    }
  }
  
  
  return myArray;
}

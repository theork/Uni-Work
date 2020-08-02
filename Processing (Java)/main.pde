
/*
TODO
 -ui X
 -slide change X
 -general speech bubble ui 
 -basic particle system implementation X
 -start Reeves' five steps X
 -slides X
 -include interactive mode X
 -extend with more variables
 */

int slide_no = 1;
final int NO_OF_SLIDES = 11;
float x, y;
ParticleSystem example, noRng, changeable;
boolean drawParticles = true;
boolean rng = true;
HScrollbar scrXVelocity, scrYVelocity, scrLifetime;
boolean first = true;

void setup() {
  size(900, 700);
  background(255);  
  
  //draws the UI
  fill(200);  
  stroke(200);
  rect(0, height - height / 10, width, height / 10);
  fill(255, 0, 0);  
  stroke(0);
  rect(width / 18, height - height / 17, width / 9, height / 50);
  triangle(width / 16, height - height / 14, width / 30, height - height / 21, 
    width / 16, height - height / 45);
  //right arrow (mirrored)
  rect(width - width / 18, height - height / 17, width / - 9, height / 50);
  triangle(width - width / 16, height - height / 14, width - width / 30, 
    height - height / 21, width - width / 16, height - height / 45);
  updateSlide();
  
}

void draw() {
  //probably inefficient...
  switch(slide_no) {
    case 2:
      rect(width / 2, height / 2.2, 200, 200);
      x += random(-5, 5);
      y += random(-5, 5);
      if (x > (width / 2) + 95)
        x -= 5;
      else if (x < (width / 2) - 95)
        x += 5;
      else if (y > (height / 2.2) + 95)
        y -= 5;
      else if (y < (height / 2.2) - 95)
        y += 5;      
      fill(0);
      ellipse(x, y, 10, 10);
      fill(255);
      break;
    case 3:
      fill(255);
      rect(width / 2, height / 2.5, 700, 500);
      example.newParticle();
      example.update();
      break;        
    case 6:
      fill(255);
      rect(width / 2, height / 2.5, 700, 500);
      example.newParticle();
      example.update();
      
      for (int i = 0; i < example.particles.size(); i++){
        Particle part = example.particles.get(i);
        if (part.lifetime < 10){
          part.colour = color(255, 0, 0);
        }        
      }
      break;
    case 7:        
    case 8:
      fill(255);
      rect(width / 2, height / 2.5, 700, 500);
      example.newParticle();
      example.update();      
      break;
    case 9:
      fill(255);
      rect(width / 2, height / 2.5, 700, 500);
      noRng.newParticle();
      noRng.update();
      break;     
    case 11:


      
      fill(200);  
      stroke(200);
      rect(0, height - height / 10, width, height / 10);
      fill(255);
      stroke(255);
      rectMode(CORNER);
      rect(0, 0, width, height - height / 10);
      textAlign(CENTER);
      rectMode(CENTER);
      fill(200); 
      stroke(200);
      rect(width / 2, height - height / 27, 100, 50);
      textSize(30);
      String slideText = slide_no + "/" + NO_OF_SLIDES;
      fill(0);
      text(slideText, width / 2, height - height / 27);
      rectMode(CORNER);
      textSize(17);
      fill(255, 0, 0);  
      stroke(0);
      rect(width / 18, height - height / 17, width / 9, height / 50);
      triangle(width / 16, height - height / 14, width / 30, height - height / 21, 
        width / 16, height - height / 45);
      //right arrow (mirrored)
      rect(width - width / 18, height - height / 17, width / - 9, height / 50);
      triangle(width - width / 16, height - height / 14, width - width / 30, 
        height - height / 21, width - width / 16, height - height / 45);
        
      
      scrXVelocity.update();
      scrYVelocity.update();
      scrLifetime.update();
      scrXVelocity.display();
      scrYVelocity.display();
      scrLifetime.display();
      float xVelocityPos =  2 * ( (scrXVelocity.getPos() - 115.51056) / (833.5374 - 115.51056) ) - 1 ;
      float yVelocityPos =  2 * ( (scrYVelocity.getPos() - 115.51056) / (833.5374 - 115.51056) ) - 1 ;
      float lifetimePos = (scrLifetime.getPos() - 115.51056) / (833.5374 - 115.51056);
      changeable.lifetimeMean = lifetimePos * 150; 
      changeable.velocityMean.x = xVelocityPos * 20;
      changeable.velocityMean.y = yVelocityPos * 20;
      changeable.newParticle();
      changeable.update();
      fill(0);
      slide11();
      
      break;
  }
  
}


void mouseClicked() {
  float areaWidth = (height - height / 13.5) + (height / 18);
  if (mouseX > width / 31 && mouseX < (width / 31) + (width / 7) &&
    mouseY > height - height / 13.5 && mouseY < areaWidth) {
    if (slide_no > 1) {
      slide_no--;
      updateSlide();
    }
  } else if (mouseX < width - width / 31 && mouseX > (width - width / 31) + (width / -7) &&
    mouseY > height - height / 13.5 && mouseY < areaWidth) {
    if (slide_no < NO_OF_SLIDES) {
      slide_no++;
      updateSlide();
    }
  }
}

void updateSlide() {

  
  fill(255);
  stroke(255);
  rectMode(CORNER);
  rect(0, 0, width, height - height / 10);
  textAlign(CENTER);
  rectMode(CENTER);
  fill(200); 
  stroke(200);
  rect(width / 2, height - height / 27, 100, 50);
  textSize(30);
  String slideText = slide_no + "/" + NO_OF_SLIDES;
  fill(0);
  text(slideText, width / 2, height - height / 27);
  rectMode(CORNER);
  textSize(17);
  


  callSlide();  
}

void callSlide(){
  switch(slide_no) {
    case 1:
      slide1();
      break;
    case 2:
      slide2();
      break;
    case 3:
      slide3();
      break;
    case 4:
      slide4();
      break;
    case 5:
      slide5();
      break;
    case 6:
      slide6();
      break;
    case 7:
      slide7();
      break;
    case 8:
      slide8();
      break;
    case 9:
      slide9();
      break;
    case 10:
      slide10();
      break;
    case 11:
      slide11();
      break;
    
    
    
    default:
      println("This should not happen - slide out of range - callSlide()");
    
  }
  
}

void slide1(){
  text("This is an interactive animation.\n Use the arrows at the bottom of the screen to progress.", width / 2, height / 2.5);
}

void slide2(){
  text("A particle can be thought of as a small shape that doesn't do much on it's own...", width / 2, height - height / 9);
  fill(255);
  rectMode(CENTER);
  stroke(0);
  x = width / 2;
  y = height / 2.2;
}

void slide3(){
  text("...however, when multiple particles are put together, they create a particle system. \n" +
  "William Reeves was the man who introduced particle systems and\n" +
  "he devised five basic steps in order to create them.", width / 2, height - height / 5);
  PVector start_pos = new PVector(width / 2, height / 2.5);
  PVector meanVelocity = new PVector(0, 0);
  PVector meanAccel = new PVector(0, 0);
  example = new ParticleSystem(start_pos, 0.1, 4, 0.1, meanVelocity, 60, meanAccel);
  rectMode(CENTER);
}

void slide4(){
  text("Step one - generate new particles.", width / 2, height - height / 9);
  noLoop();
  for (int i = 0; i < 100; i++){
    example.newParticle();
    example.update();
  }
  rectMode(CENTER);
  fill(255);
  rect(width / 2, height / 2.5, 700, 500);
  
  example.newParticle();
  example.update();
  loop();
}

void slide5(){
  text("Step two - assign properties to each of the new particles.", width / 2, height - height / 9);
  noLoop();
  for (int i = 0; i < 100; i++){
    example.newParticle();
    example.update();
  }
  rectMode(CENTER);
  fill(255);
  rect(width / 2, height / 2.5, 700, 500);
  
  example.newParticle();
  example.update();
  
  stroke(255, 0, 0);
  fill(255, 0, 0);
  Particle p = example.getParticle(0);
  String[] data = p.getData();
  text("Position: x = " + data[0] + ", y = " + data[1] + " | Velocity: x = " + data[2] + ", y = " + 
  data[3] + "\nAcceleration: x = " + data[4] + ", y = " + data[5], width / 2, height - height / 5);
  line(width / 2, height - height / 4.5, float(data[0]), float(data[1]));
  ellipse(float(data[0]), float(data[1]), 12, 12);
  loop();
}

void slide6(){
  text("Step three - remove any particles that have exceeded their lifetime." + 
  "\nHere particles that are about to expire are shown in red.", width / 2, height - height / 6);
  rectMode(CENTER);
  fill(255);
}

void slide7(){
  text("Step four - transform the particles based on their attributes"
  + "\n e.g. velcoity transforms postition, acceleration transforms velocity...", width / 2, height - height / 6);
  rectMode(CENTER);
  fill(255);
}

void slide8(){
  rng = true;
  text("Step five - render an image of the particles to the frame buffer" + 
  "\n this is what you see now", width / 2, height - height / 6);
  rectMode(CENTER);
  fill(255);
  
}

void slide9(){
  text("The variables are all randomly generated." +
  "\nYou can only change the mean and varience of each of the variables." + 
  "\nThis is what a particle system without randomly generated variables looks like.", width / 2, height - height / 5);
  rng = false;
  PVector start_pos = new PVector(width / 4, height / 4.5);
  PVector meanVelocity = new PVector(12, 0);
  PVector meanAccel = new PVector(-0.1, 0.2);
  noRng = new ParticleSystem(start_pos, 1, 1, 1, meanVelocity, 55, meanAccel);
  rectMode(CENTER);
}

void slide10(){
  rng = true;
  text("Now have a go at changing the properties of the particle system yourself." +
  "\nOn the next slide, adjust the sliders to change the variables.", width / 2, height - height / 2);
  PVector start_pos = new PVector(width / 2, height / 2.5);
  PVector meanVelocity = new PVector(0, 0);
  PVector meanAccel = new PVector(0, 0);
  changeable = new ParticleSystem(start_pos, 0.1, 4, 0.1, meanVelocity, 60, meanAccel);
  
}

void slide11(){
  textSize(15);
  text("X Velocity\nY Velocity\nLifetime", width / 15, height - height / 7 - 30);
  
  if (first){
    scrXVelocity = new HScrollbar(width / 8, height - height / 7 - 30, width - width / 5, 15, 15);
    scrYVelocity = new HScrollbar(width / 8, height - height / 7 - 10, width - width / 5, 15, 15);
    scrLifetime = new HScrollbar(width / 8, height - height / 7 + 10, width - width / 5, 15, 15);
    first = false;
  }
}

class ParticleSystem {  
  float velocityVar, lifetimeVar, accelerationVar, positionVar;
  PVector velocityMean, accelerationMean;
  float lifetimeMean;
  ArrayList<Particle> particles;
  PVector spawn;
  
  //initialised constructor
  ParticleSystem(PVector init_spawn, float init_velocityVar, float init_lifetimeVar, float init_accelerationVar, 
      PVector init_velocityMean, float init_lifetimeMean, PVector init_accelerationMean){
    spawn = init_spawn;
    velocityVar = init_velocityVar;
    lifetimeVar = init_lifetimeVar;
    accelerationVar = init_accelerationVar;
    
    velocityMean = init_velocityMean;
    lifetimeMean = init_lifetimeMean;
    accelerationMean = init_accelerationMean;
    
    particles = new ArrayList<Particle>();
    
  }
  
  void newParticle(){
    particles.add(new Particle(this));
  }
  
  void update(){
    for (int i = 0; i < particles.size(); i++){
      Particle part = particles.get(i);
      part.update();
      if (drawParticles)
        part.display();
      if (!part.checkLife())
        particles.remove(i);
    }
  }
  
  Particle getParticle(int i){
    Particle p = particles.get(i);    
    return p;
  }
}


class Particle {
  PVector pos, velocity, acceleration;
  float lifetime;
  float radius = 10;
  color colour = color(0, 0, 0);
  
  Particle(ParticleSystem ps){
    if(rng){
    pos = new PVector(ps.spawn.x + random(-1, 1) * ps.positionVar, ps.spawn.y + random(-1, 1) * ps.positionVar);
    velocity = new PVector(ps.velocityMean.x + random(-1, 1) * ps.velocityVar, ps.velocityMean.y + random(-1, 1) * ps.velocityVar);
    acceleration = new PVector(ps.accelerationMean.x + random(-1, 1) * ps.accelerationVar, ps.accelerationMean.y + random(-1, 1) * ps.accelerationVar);
    lifetime = ps.lifetimeMean + random(-1, 1) * ps.lifetimeVar;
    } else {
      pos = new PVector(ps.spawn.x, ps.spawn.y);
      velocity = new PVector(ps.velocityMean.x, ps.velocityMean.y);
      acceleration = new PVector(ps.accelerationMean.x, ps.accelerationMean.y );
      lifetime = ps.lifetimeMean;
    }

  }
  
  void update(){
    velocity.add(acceleration);
    pos.add(velocity);
    lifetime -= 1;
  }
  
  void display(){
    stroke(colour);
    fill(colour);
    ellipse(pos.x, pos.y, radius, radius);
  }
  
  boolean checkLife(){
    if(lifetime < 0)
      return false;
    else
      return true;
  }

  String[] getData(){
    String[] data = new String[9];
    data[0] = str(pos.x);
    data[1] = str(pos.y);
    data[2] = str(velocity.x);
    data[3] = str(velocity.y);
    data[4] = str(acceleration.x);
    data[5] = str(acceleration.y);
    data[6] = str(lifetime);
    data[7] = str(radius);
    data[8] = str(colour);
    return data;
  }
  
    
}


//THIS IS NOT MY CODE
//this is class is imported from the processing examples list
//URL: https://processing.org/examples/scrollbar.html
class HScrollbar {
  int swidth, sheight;    // width and height of bar
  float xpos, ypos;       // x and y position of bar
  float spos, newspos;    // x position of slider
  float sposMin, sposMax; // max and min values of slider
  int loose;              // how loose/heavy
  boolean over;           // is the mouse over the slider?
  boolean locked;
  float ratio;

  HScrollbar (float xp, float yp, int sw, int sh, int l) {
    swidth = sw;
    sheight = sh;
    int widthtoheight = sw - sh;
    ratio = (float)sw / (float)widthtoheight;
    xpos = xp;
    ypos = yp-sheight/2;
    spos = xpos + swidth/2 - sheight/2;
    newspos = spos;
    sposMin = xpos;
    sposMax = xpos + swidth - sheight;
    loose = l;
  }

  void update() {
    if (overEvent()) {
      over = true;
    } else {
      over = false;
    }
    if (mousePressed && over) {
      locked = true;
    }
    if (!mousePressed) {
      locked = false;
    }
    if (locked) {
      newspos = constrain(mouseX-sheight/2, sposMin, sposMax);
    }
    if (abs(newspos - spos) > 1) {
      spos = spos + (newspos-spos)/loose;
    }
  }

  float constrain(float val, float minv, float maxv) {
    return min(max(val, minv), maxv);
  }

  boolean overEvent() {
    if (mouseX > xpos && mouseX < xpos+swidth &&
       mouseY > ypos && mouseY < ypos+sheight) {
      return true;
    } else {
      return false;
    }
  }

  void display() {
    noStroke();
    fill(204);
    rect(xpos, ypos, swidth, sheight);
    if (over || locked) {
      fill(0, 0, 0);
    } else {
      fill(102, 102, 102);
    }
    rect(spos, ypos, sheight, sheight);
  }

  float getPos() {
    // Convert spos to be values between
    // 0 and the total width of the scrollbar
    return spos * ratio;
  }
}

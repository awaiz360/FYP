import processing.serial.*;               // imports library for serial communication

Serial myPort;                         // defines Object for Serial
String ang="";
String distance="";
String data="";
int angle, dist;
static float prev_x = 0, prev_y = 0;
static int i = 0;

void setup() {
   size (1700, 900); 
   myPort = new Serial(this,"COM2", 115200);   // starts the serial communication. Changfe this to suit your serial monitor on Arduino
   myPort.bufferUntil('.');    // reads the data from the serial port up to the character '.' before calling serialEvent
   background(0);
}

void draw() {
      drawText();
      drawRadar(); 
      drawObject();
      if(angle==165 || angle == 15){
      background(0,0,0);
      }
                      
      fill(0,5);              
      noStroke(); 
      noStroke();
      fill(0,255);
      rect(0,height*0.93,width,height);                   // so that the text having angle and distance doesnt blur out     
}

void serialEvent (Serial myPort) {                                                     // starts reading data from the Serial Port
                                                                                      // reads the data from the Serial Port up to the character '.' and puts it into the String variable "data".
      data = myPort.readStringUntil('.');
      data = data.substring(0,data.length()-1);
      
      int index1 = data.indexOf(",");                                                    
      ang= data.substring(0, index1);                                                 
      distance= data.substring(index1+1, data.length());                            
      
      angle = int(ang);
      dist = int(distance);
      System.out.println(angle);
}

void drawRadar()
{
    pushMatrix();
    noFill();
    stroke(10,255,10);        //green
    strokeWeight(1);
    translate(width/2,height-height*0.06);
    line(-width/2,0,width/2,0);
    arc(0,0,(width*0.25),(width*0.25),PI,TWO_PI);
    arc(0,0,(width*0.15),(width*0.15),PI,TWO_PI);
    arc(0,0,(width*0.35),(width*0.35),PI,TWO_PI);
    arc(0,0,(width*0.45),(width*0.45),PI,TWO_PI);
    arc(0,0,(width*0.55),(width*0.55),PI,TWO_PI);
    arc(0,0,(width*0.65),(width*0.65),PI,TWO_PI);
    arc(0,0,(width*0.75),(width*0.75),PI,TWO_PI);
    arc(0,0,(width*0.85),(width*0.85),PI,TWO_PI);
    arc(0,0,(width*0.95),(width*0.95),PI,TWO_PI);
    line(0,0,(-width/2)*cos(radians(90)),(-width/2)*sin(radians(90)));
    popMatrix();
}
void drawObject() {
    strokeWeight(7);
    stroke(255,0,0);
    translate(width/2,height-height*0.06);
    float pixleDist = (dist/199.0)*(width);                        // covers the distance from the sensor from cm to pixels     
    float x=-pixleDist*cos(radians(angle));
    float y=-pixleDist*sin(radians(angle));
    if(dist<=199)                                                  // limiting the range to 40 cms
    {                 
       point(-x,y);
    }
    //if(i == 1)
    //{
    //  prev_x = 0;
    //  prev_y = 0;
    //  i = 0;
    //}
    //else
    //{
    //  prev_x = x;
    //  prev_y = y;
    //}
    //i++;
    //int diff = int(sqrt((prev_x-x)*(prev_x-x) + (prev_y-y)*(prev_y-y)));
    //if((prev_x != 0) && (prev_y != 0) && (diff < 5))
    //{
    //  line(prev_x, prev_y, x, y);
    //}
}

void drawText()
{
    pushMatrix();
    fill(100,200,255);
    textSize(25);
    text("20cm",(width/2)+(width*0.04),height*0.93);
    text("40cm",(width/2)+(width*0.09),height*0.93);
    text("60cm",(width/2)+(width*0.14),height*0.93);
    text("80cm",(width/2)+(width*0.19),height*0.93);
    text("100cm",(width/2)+(width*0.24),height*0.93);
    text("120cm",(width/2)+(width*0.29),height*0.93);
    text("140cm",(width/2)+(width*0.34),height*0.93);
    text("160cm",(width/2)+(width*0.39),height*0.93);
    text("180cm",(width/2)+(width*0.44),height*0.93);
    translate(width/2,height-height*0.06);
    textSize(25);
    text(" 30°",(width/2)*cos(radians(30)),(-width/2)*sin(radians(30)));
    text(" 60°",(width/2)*cos(radians(60)),(-width/2)*sin(radians(60)));
    text("90°",(width/2)*cos(radians(91)),(-width/2)*sin(radians(90)));
    text("120°",(width/2)*cos(radians(123)),(-width/2)*sin(radians(118)));
    text("150°",(width/2)*cos(radians(160)),(-width/2)*sin(radians(150)));
    popMatrix();  
}

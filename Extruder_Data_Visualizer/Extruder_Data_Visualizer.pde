
//Extruder Data Visualizer  by Matt Rogge April 2, 2017


import java.util.*;
import processing.serial.*; 
import org.gicentre.utils.stat.*;    // For chart classes.

import java.util.ArrayList;
import static java.util.Arrays.asList;
import java.util.List;

Serial serial;    // The serial port
boolean serialInited;
int now;

String inString;  // Input string from serial port
int linefeed = 10;      // ASCII linefeed 
boolean starting = true;
boolean extruding = false;

//Chart Variables
int secondsDisplayed = 100;
int dataIndex = 0;
XYChart diaChart;
XYChart QCDiaChart;
XYChart controlChart;
float[] dataX = new float[secondsDisplayed];//The data for the x axis
float[] diaVals = new float[secondsDisplayed];
float[] QCDiaVals = new float[secondsDisplayed];
float[] controlVals = new float[secondsDisplayed];
float diameter;
float qcDiameter;
float controlVal;

PrintWriter rawDataWriter;


void setup() {
  rawDataWriter = createWriter("rawData.txt");

  frameRate(60);
  size(1000, 700);
  //Serial port setup
  // List all the available serial ports: 
  printArray(Serial.list());

  //Chart Setup
  textFont(createFont("Arial", 10), 10);

  // Both x and y data set here.  
  diaChart = new XYChart(this);
  diaChart.setData(dataX, diaVals);

  // Axis formatting and labels.
  diaChart.showXAxis(true); 
  diaChart.showYAxis(true); 
  diaChart.setMinY(1);
  diaChart.setMaxY(5);
  diaChart.setMinX(0);
  diaChart.setMaxX(secondsDisplayed);
  // Symbol colours
  diaChart.setPointSize(5);
  diaChart.setLineWidth(2);
  diaChart.setYAxisLabel("Diameter (mm)");
  diaChart.setXAxisLabel("Time (s)");


  // Both x and y data set here.  
  QCDiaChart = new XYChart(this);
  QCDiaChart.setData(dataX, QCDiaVals);

  // Axis formatting and labels.
  QCDiaChart.showXAxis(true); 
  QCDiaChart.showYAxis(true); 
  QCDiaChart.setMinY(1.2);
  QCDiaChart.setMaxY(2);
  QCDiaChart.setMinX(0);
  QCDiaChart.setMaxX(secondsDisplayed);
  // Symbol colours
  QCDiaChart.setPointColour(color(22, 229, 0, 100));
  QCDiaChart.setLineColour(color(22, 229, 0, 100));
  QCDiaChart.setPointSize(5);
  QCDiaChart.setLineWidth(2);
  QCDiaChart.setYAxisLabel("Diameter (mm)");
  QCDiaChart.setXAxisLabel("Time (s)");

  // Both x and y data set here.  
  controlChart = new XYChart(this);
  controlChart.setData(dataX, controlVals);

  // Axis formatting and labels.
  controlChart.showXAxis(true); 
  controlChart.showYAxis(true); 
  controlChart.setMinY(0);
  controlChart.setMaxY(15);
  controlChart.setMinX(0);
  controlChart.setMaxX(secondsDisplayed);
  // Symbol colours
  controlChart.setPointColour(color(229, 42, 0, 100));
  controlChart.setLineColour(color(229, 42, 0, 100));
  controlChart.setAxisValuesColour(color(229, 42, 0, 100));
  controlChart.setPointSize(5);
  controlChart.setLineWidth(2);
  controlChart.setYAxisLabel("Diameter (mm)");
  controlChart.setXAxisLabel("Time (s)");

  // Open the port that the arduino uses.
  initSerial();
  delay(1000);
  serial.write('C');
  serial.write('C');
  serial.write('C');
  serial.write('B');
  serial.write('B');
  serial.write('B');
  serial.write('B');
  serial.write('B');
  serial.write('B');
  serial.write('B');
  serial.write('B');
  serial.write('B');
  serial.write('B');
  serial.write('C');
  serial.write('B');
  serial.write('B');
  serial.write('B');
  serial.write('B');
  serial.write('B');
  serial.write('B');
  serial.write('B');
  serial.write('B');
  serial.write('B');
  serial.write('B');
  serial.write('B');
  serial.write('B');
  serial.write('B');
  serial.write('C');
} 

void draw() { 

  background(255);
  textSize(9);

  diaChart.draw(15, 15, (width-30), (height)/2-40);
  QCDiaChart.draw(15, 15, (width-30), (height)/2-40);
  controlChart.draw(15, 15, (width-30), (height)/2-40);

  // Draw a title over the top of the chart.

  textSize(11);

  text("Diameter:", 15, 380);
  text(diameter, 115, 380);
  text("qcDiameter:", 15, 395);
  text(qcDiameter, 115, 395);
  text("controlVal:", 15, 410);
  text(controlVal, 115, 410);  

  // Draw a title over the top of the chart.
  fill(120);
  textSize(20);
  text("Diameter Sensor", 70, 30);
} 



void serialEvent(Serial p) { 
  try {
    inString = p.readString();
    print(inString);
    rawDataWriter.print(inString);
    if (inString.equals("Stop\r\n")) {
      println("stopping");
      rawDataWriter.flush();
      rawDataWriter.close();
      exit();
    }
    serial.clear();
    String[] valStrings = split(inString, '\t');
    float[] newData = new float[8];
    for (int i=0; i<valStrings.length; i++) {
      newData[i] = float(valStrings[i]);
      if (i == newData.length-1) {
        break;
      }
    }
    diameter = newData[1];
    qcDiameter = newData[2];
    controlVal = newData[3];
    if (starting && newData[0] != 0.0) {
      return;
    } else if (starting && newData[0] ==0.0) {
      starting = false;
    }
    //Shift  existing data if current time is larger than secondsDisplayed
    if (newData[0] >= secondsDisplayed) {
      //Shift Data
      arrayCopy(dataX, 1, dataX, 0, secondsDisplayed-1);
      arrayCopy(diaVals, 1, diaVals, 0, secondsDisplayed-1);
      arrayCopy(QCDiaVals, 1, QCDiaVals, 0, secondsDisplayed-1);
      arrayCopy(controlVals, 1, controlVals, 0, secondsDisplayed-1);

      //Add new Seconds Value
      dataX[secondsDisplayed-1] = newData[0];

      //Add new Diameter value
      diaVals[secondsDisplayed-1] = newData[1];

      //Add new QC Diameter value
      QCDiaVals[secondsDisplayed-1] = newData[2];

      //Add new QC Diameter value
      controlVals[secondsDisplayed-1] = newData[3];

      //for (int i=0; i<secondsDisplayed; i++) {
      //  println(dataX[i]+"\t"+diaVals[i]+" "+QCDiaVals[i]+" "+controlVals[i]);
      //}
      //println();


      //Reset the min and max on the x axis
      diaChart.setMinX(dataX[0]);
      diaChart.setMaxX(dataX[secondsDisplayed-1]);
      QCDiaChart.setMinX(dataX[0]);
      QCDiaChart.setMaxX(dataX[secondsDisplayed-1]);
      controlChart.setMinX(dataX[0]);
      controlChart.setMaxX(dataX[secondsDisplayed-1]);
      
      //Reset the data for the chart
      diaChart.setData(dataX, diaVals);
      QCDiaChart.setData(dataX, QCDiaVals);
      controlChart.setData(dataX, controlVals);
    } else {
      //println("not filled yet");
      //Haven't filled the graph yet Just fill in from the beginning
      dataX[(int)newData[0]]= newData[0];
      diaVals[(int)newData[0]] = newData[1];
      QCDiaVals[(int)newData[0]] = newData[2];
      controlVals[(int)newData[0]] = newData[3];

      float[] tempX = new float[(int)newData[0]];
      float[] tempY = new float[(int)newData[0]];
      float[] QCTemp = new float[(int)newData[0]];
      float[] controlTemp = new float[(int)newData[0]];

      for (int i=0; i<(int)newData[0]; i++) {
        tempX[i] = dataX[i];
        tempY[i] = diaVals[i];
        QCTemp[i] = QCDiaVals[i];
        controlTemp[i] = controlVals[i];
      }

      //for (int i=0; i<secondsDisplayed; i++) {
      //  println(dataX[i]+"\t"+diaVals[i]+" "+QCDiaVals[i]+" "+controlVals[i]);
      //}
      //println();

      diaChart.setMinX(0);
      diaChart.setMaxX(secondsDisplayed-1);
      diaChart.setData(tempX, tempY);

      QCDiaChart.setMinX(0);
      QCDiaChart.setMaxX(secondsDisplayed-1);
      QCDiaChart.setData(tempX, QCTemp);

      controlChart.setMinX(0);
      controlChart.setMaxX(secondsDisplayed-1);
      controlChart.setData(tempX, controlTemp);
    }
    //println();
    //println();
  }
  catch (Exception e) {
    println(e);
    println("error");
  }
} 


void keyPressed() {
  switch (key) {
  case 'r':

    break;
  }
}

void initSerial () {
  try {

    serial = new Serial(this, Serial.list()[3], 250000); 
    serial.bufferUntil(linefeed); 
    serialInited = true;
  } 
  catch (RuntimeException e) {
    if (e.getMessage().contains("<init>")) {
      System.out.println("port in use, trying again later...");
      serialInited = false;
    }
  }
}
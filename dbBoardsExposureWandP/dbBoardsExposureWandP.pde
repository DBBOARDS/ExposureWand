/*-----------------------------------------------------------------------------------------------------------
  dbBoardsExposureWandA.pde
    Use with dbBoardsExposureWand.ino

  Summary:
    This program uses the 75x50 pixel exposureWand.jpg in the sketchfolder to render a simulation of the
    Exposure Wand's long exposure photo. It also creates exposureWand.txt in the sketchfolder which holds
    the Arduino Memory array of the red, green, and blue values of the image. Copy and Paste this to the top
    of dbBoardsExposureWand.ino to replace the current arrays.

  Programmer:
    Duncan Brandt @ DB Boards, LLC
    Created: Jan 19, 2018
  
  Development Environment Specifics:
    Processing 3.3.6
  
  Hardware Specifications:
    DB Boards 50 pixel LED Strip, DB7003
    Arduino Drawing Board (UNO) DB1000
    Soft Push Button DB7004

  Beerware License:
    This program is free, open source, and public domain. The program is distributed as is and is not
    guaranteed. However, if you like the code and find it useful I would happily take a beer should you 
    ever catch me at the local.
*///---------------------------------------------------------------------------------------------------------
PImage img;                                      // Name the image variable to hold our jpeg, img
int w = 75, h = 50;                              // The image saved as exposureWand.jpg should be 75 x 50 pixels
int[] r = new int[w*h];                          // This array stores all of the red pixel values
int[] g = new int[w*h];                          // This array stores all of the green pixel values
int[] b = new int[w*h];                          // This array stores all of the blue pixel values
//-----------------------------------------------------------------------------------------------------------
void setup(){                                    // Setup runs once to initiate the sketch
  size(225,150);                                 // Make the screen 225 x 150 pixels
  img = loadImage("exposureWand.jpg");           // Load the exposureWand.jpg file from the sketchfolder
}
//-----------------------------------------------------------------------------------------------------------
void draw(){                                     // Only needs to run once, but will continue to loop
  loadPixels();                                  // Prep and Load the pixels for the display
  img.loadPixels();                              // Load the pixels from the input image
  for(int p = 0; p < w*h; p++) {                 // Step through every pixel in the image
    r[p] = int(red(img.pixels[p]));              // Load and store the pixels red value   
    g[p] = int(green(img.pixels[p]));            // Load and store the pixels green value 
    b[p] = int(blue(img.pixels[p]));             // Load and store the pixels blue value 
  }
  // This loop triples the size of the image and adds simulation lines between the LEDs
  for(int y = 0; y < h; y++){
    for(int x = 0; x < w; x++){
      pixels[9*w*y+x*3] =  color(r[y*w+x],g[y*w+x],b[y*w+x]);
      pixels[9*w*y+x*3+w*3] =  color(r[y*w+x],g[y*w+x],b[y*w+x]);
      pixels[9*w*y+x*3+w*6] =  color(0,0,0);
      pixels[9*w*y+x*3+1] =  color(r[y*w+x],g[y*w+x],b[y*w+x]);
      pixels[9*w*y+x*3+w*3+1] =  color(r[y*w+x],g[y*w+x],b[y*w+x]);
      pixels[9*w*y+x*3+w*6+1] =  color(0,0,0);  
      pixels[9*w*y+x*3+2] =  color(r[y*w+x],g[y*w+x],b[y*w+x]);
      pixels[9*w*y+x*3+w*3+2] =  color(r[y*w+x],g[y*w+x],b[y*w+x]);
      pixels[9*w*y+x*3+w*6+2] =  color(0,0,0);  
    }
  }
  updatePixels();                                // Show the simulated image
  String[] print = new String[3];                // Used to build red, green, and blue arrays
  String[] save = new String[3];                 // Used to store the Arduino arrays for dbBoardsExposureWandA.ino
  print[0] = "const PROGMEM  uint16_t r[]  = {"; // Fill in the needed Arduino variable call
  print[1] = join(nf(r, 0), ", ");               // Create , seperated integer array for red
  print[2] = "};";                               // Close the Arduino array
  String list = join(print, "");                 // Combine the text for this array
  save[0] = list;                                // Save the entire Arduino array String
  print[0] = "const PROGMEM  uint16_t g[]  = {"; // Fill in the needed Arduino variable call
  print[1] = join(nf(g, 0), ", ");               // Create , seperated integer array for green
  print[2] = "};";                               // Close the Arduino array
  list = join(print, "");                        // Combine the text for this array
  save[1] = list;                                // Save the entire Arduino array String
  print[0] = "const PROGMEM  uint16_t b[]  = {"; // Fill in the needed Arduino variable call
  print[1] = join(nf(b, 0), ", ");               // Create , seperated integer array for blue
  print[2] = "};";                               // Close the Arduino array
  list = join(print, "");                        // Combine the text for this array
  save[2] = list;                                // Save the entire Arduino array String
  saveStrings("exposureWand.txt", save);         // Save all three String into exposureWand.txt in the sketchfolder
}
//-----------------------------------------------------------------------------------------------------------

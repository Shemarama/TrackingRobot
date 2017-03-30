/***
* This example expects the serial port has a loopback on it.
*
* Alternatively, you could use an Arduino:
*
* <pre>
*  void setup() {
*    Serial.begin(<insert your baudrate here>);
*  }
*
*  void loop() {
*    if (Serial.available()) {
*      Serial.write(Serial.read());
*    }
*  }
* </pre>
*/
/**
 * @file objectDetection2.cpp
 * @author A. Huaman ( based in the classic facedetect.cpp in samples/c )
 * @brief A simplified version of facedetect.cpp, show how to load a cascade classifier and how to find objects (Face + eyes) in a video stream - Using LBP here
 */

#include <string>
#include <iostream>
#include <cstdio>

// OS Specific sleep
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

// serial
#include "serial/serial.h"

// opencv
#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>
#include <stdio.h>

#include <chrono>

using namespace std;
using namespace cv;

using std::string;
using std::exception;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;


/** Global variables */
//String face_cascade_name = "/home/barbie/Documents/python/opencv/opencv/data/haarcascades/haarcascade_frontalface_default.xml";
String face_cascade_name = "/home/barbie/lbp_face.xml";
//String face_cascade_name = "/home/barbie/Documents/python/opencv/opencv/data/lbpcascades/lbpcascade_frontalface_improved.xml";
String eyes_cascade_name = "/home/barbie/Documents/python/opencv/opencv/data/haarcascades/haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
String window_name = "Capture - Face detection";

unsigned char LSB = 0;
unsigned char MSB = 0;
short MSBLSB = 0;

auto start = std::chrono::steady_clock::now();
// do something
auto finish = std::chrono::steady_clock::now();
double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double> >(finish - start).count();


/** Function Headers */
void detectAndDisplay( Mat frame );

void my_sleep(unsigned long milliseconds) {
#ifdef _WIN32
     Sleep(milliseconds); // 100 ms
#else
     usleep(milliseconds*1000); // 100 ms
#endif
}

vector<unsigned char> intToBytes(int paramInt)
{
     vector<unsigned char> arrayOfByte(4);
     for (int i = 0; i < 4; i++)
         arrayOfByte[3 - i] = (paramInt >> (i * 8));
     return arrayOfByte;
}

void print_usage()
{
   cerr << "Usage: test_serial {-e|<serial port address>} ";
   cerr << "<baudrate> [test string]" << endl;
}

int setup(int argc, char **argv)
{
 if(argc < 2) {
   print_usage();
   return 1;
 }

 if( argc < 3 ) {
   print_usage();
   return 1;
 }
  return 0;
}


/**
 * @function main
 */
int main(int argc, char **argv)
{
    if (setup(argc,argv) == 1)
        return 0;
    // Argument 1 is the serial port or enumerate flag
    string port(argv[1]);

    // Argument 2 is the baudrate
    unsigned long baud = 0;
#if defined(WIN32) && !defined(__MINGW32__)
    sscanf_s(argv[2], "%lu", &baud);
#else
    sscanf(argv[2], "%lu", &baud);
#endif

    // port, baudrate, timeout in milliseconds
    serial::Serial arduino(port, baud, serial::Timeout::simpleTimeout(1000));

    cout << "Is the serial port open?";
    if(arduino.isOpen())
      cout << " Yes." << endl;
    else
      cout << " No." << endl;

    /*
    // Get the Test string
    int count = 0;
    string test_string;
    if (argc == 4) {
      test_string = argv[3];
    } else {
      test_string = "Testing.";
    }
    */

    
    VideoCapture capture;
    Mat frame;

    //-- 1. Load the cascade
    if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading face cascade\n"); return -1; };
    if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading eyes cascade\n"); return -1; };

    //-- 2. Read the video stream
    capture.open( -1 );
    if ( ! capture.isOpened() ) { printf("--(!)Error opening video capture\n"); return -1; }

    start = std::chrono::steady_clock::now();

    while ( capture.read(frame) )
    {
        if( frame.empty() )
        {
            printf(" --(!) No captured frame -- Break!");
            break;
        }

        //-- 3. Apply the classifier to the frame
        std::vector<Rect> faces;
        Mat frame_gray;

        cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
        equalizeHist( frame_gray, frame_gray );

        //-- Detect faces
        //face_cascade.detectMultiScale( frame_gray, faces, 1.4, 2, 0, Size(30, 30) );
        face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0, Size(80, 80) );

        unsigned int x;
        unsigned int y;

        for( size_t i = 0; i < faces.size(); i++ )
        {
            /*LSB = (faces[i].x) & 0xff;
            MSB = ((faces[i].x) >> 8) & 0xff;
            arduino.write(MSB+"");
            arduino.write(LSB+"");
            LSB = (faces[i].y) & 0xff;
            MSB = ((faces[i].y) >> 8) & 0xff;
            arduino.write(MSB+"");
            arduino.write(LSB+"");

            cout << "x: " << faces[i].x << endl;
            */
            x = faces[i].x;
            y = faces[i].y;

            /*
            Mat faceROI = frame_gray( faces[i] );
            std::vector<Rect> eyes;
            
            //-- In each face, detect eyes
            //eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );
            eyes_cascade.detectMultiScale( faceROI, eyes, 1.4, 3, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );
            //if( eyes.size() == 2)
            {
                //-- Draw the face
                Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
                //ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 0 ), 2, 8, 0 );
                rectangle( frame, Rect(faces[i].x,faces[i].y,faces[i].width,faces[i].height), Scalar( 255, 0, 0), 2, 8, 0 );

                for( size_t j = 0; j < eyes.size(); j++ )
                { //-- Draw the eyes
                    Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
                    int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
                    //circle( frame, eye_center, radius, Scalar( 255, 0, 255 ), 3, 8, 0 );
                    rectangle( frame, Rect(faces[i].x+eyes[i].x,faces[i].y+eyes[i].y,eyes[i].width,eyes[i].height), Scalar( 0, 255, 0), 2, 8, 0 );
                }
            }
            */


            //-- Draw the face
            Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
            //ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 0 ), 2, 8, 0 );
            rectangle( frame, Rect(faces[i].x,faces[i].y,faces[i].width,faces[i].height), Scalar( 255, 0, 0), 2, 8, 0 );
            

        }
        
        finish = std::chrono::steady_clock::now();
        elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double> >(finish - start).count();
        
        if (elapsed_seconds > 0.2) {
            if ( (x > 0) && (x < 640) && (y > 0) && (y < 480) )
            {
                cout << "x: " << x;
                arduino.write(std::to_string(x));
                arduino.write("\n");
                cout << "   y: " << y << endl;
                arduino.write(std::to_string(y));
                arduino.write("\n");
            }
            start = std::chrono::steady_clock::now();
        }

        
        //-- Show what you got
        imshow( window_name, frame );

        //-- bail out if escape was pressed
        char c = (char)waitKey(10);
        if( c == 27 ) { break; }
    }
    return 0;
}


#include <cstdio>
#include <iostream>
#include <string>

// OS Specific sleep
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

// serial
#include "serial/serial.h"

// opencv
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"

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
String face_cascade_name = "/home/barbie/Documents/python/opencv/robot/resources/lbp_face.xml";
CascadeClassifier face_cascade;

String window_name = "Capture - Face detection";

unsigned int x;
unsigned int y;
unsigned int centerx;
unsigned int centery;

auto start = std::chrono::steady_clock::now();
auto finish = std::chrono::steady_clock::now();
double elapsed_seconds =
  std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();


/** Functions */

void my_sleep(unsigned long milliseconds)
{
#ifdef _WIN32
  Sleep(milliseconds); // 100 ms
#else
  usleep(milliseconds * 1000); // 100 ms
#endif
}

void print_usage()
{
  cerr << "Usage: test_serial {<serial port address>} ";
  cerr << "<baudrate> [test string]" << endl;
}

int checkArgs(int argc, char** argv)
{
  if (argc < 2) {
    print_usage();
    return 1;
  }

  if (argc < 3) {
    print_usage();
    return 1;
  }

  return 0;
}

/*  MAIN FUNCTION */
int main(int argc, char** argv)
{
  if (checkArgs(argc, argv) == 1)
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
  if (arduino.isOpen())
    cout << " Yes." << endl;
  else
    cout << " No." << endl;

  VideoCapture capture;
  Mat frame;

  //-- 1. Load the cascade
  if (!face_cascade.load(face_cascade_name)) {
    printf("--(!)Error loading face cascade\n");
    return -1;
  };
  
  //-- 2. Read the video stream
  capture.open(-1);
  if (!capture.isOpened()) {
    printf("--(!)Error opening video capture\n");
    return -1;
  }

  start = std::chrono::steady_clock::now();

  std::vector<Rect> faces;
  Mat frame_gray;

  while (capture.read(frame)) {
    if (frame.empty()) {
      printf(" --(!) No captured frame -- Break!");
      break;
    }

    //-- 3. Apply the classifier to the frame
    //std::vector<Rect> faces;
    //Mat frame_gray;

    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    //-- Detect faces
    //face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0, Size(80, 80));
    face_cascade.detectMultiScale(frame_gray, faces, 1.3, 3, 0, Size(80, 80));

    for (size_t i = 0; i < faces.size(); i++) {
      // get xy coord for face
      x = faces[i].x;
      y = faces[i].y;
      centerx = faces[i].x + int(faces[i].width/2);
      centery = faces[i].y + int(faces[i].height/2);

      //-- Draw the face
      Point center(faces[i].x + faces[i].width / 2,
                   faces[i].y + faces[i].height / 2);
      rectangle(frame,
                Rect(faces[i].x, faces[i].y, faces[i].width, faces[i].height),
                Scalar(255, 0, 0), 2, 8, 0);
    }
    
    finish = std::chrono::steady_clock::now();
    elapsed_seconds =
      std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();

    // send xy coord every 200 ms
    if (elapsed_seconds > 0.2) {
      // if not garbage xy coord
      if ((x > 0) && (x < 640) && (y > 0) && (y < 480)) {
        cout << "x: " << centerx;
        //arduino.write(std::to_string(x));
        arduino.write(std::to_string(centerx));
        arduino.write("\n");
        
        cout << "   y: " << centery << endl;
        //arduino.write(std::to_string(y));
        arduino.write(std::to_string(centery));
        arduino.write("\n");
      }
      start = std::chrono::steady_clock::now();
    }

    //-- Show what you got
    imshow(window_name, frame);

    //-- bail out if escape was pressed
    char c = (char)waitKey(10);
    if (c == 27) {
      break;
    }
  }
  
  return 0;
}

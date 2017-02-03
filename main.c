//
//  main.cpp
//  Rubik's cube color detection
//
//  Created by Harsh Thaker on 04/01/16.
//  Copyright (c) 2016 Harsh Thaker. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "opencv2/core/core.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/legacy/legacy.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "iostream"

using namespace cv;
using namespace std;

int red =0,blue=0,green =0;

int main( int argc, char** argv ){
    
    Mat image,hsv_img;
    image = imread("/Users/hardikthaker/Desktop/rubiks.jpg", CV_LOAD_IMAGE_COLOR);   // Read the file
    
    cvtColor(image,hsv_img,COLOR_BGR2HSV);
    
    Mat lower_red_hue_range;
    Mat upper_red_hue_range;
    Mat lower_green_hue_range,upper_green_range;
    Mat lower_blue,upper_blue;
    
    inRange(hsv_img, cv::Scalar(0, 100, 100), cv::Scalar(10, 255, 255), lower_red_hue_range);
    //inRange(hsv_img, cv::Scalar(160, 100, 100), cv::Scalar(179, 255, 255), upper_red_hue_range);
    inRange(hsv_img, Scalar(85,64,200), Scalar(170,255,255), lower_blue);
    //inRange(hsv_img, Scalar(34,50,50), Scalar(80,255,200), upper_blue);
    inRange(hsv_img, Scalar(53,74,160), Scalar(85,203,255), lower_green_hue_range);
    
    
    
    
    namedWindow( "Display window", WINDOW_NORMAL );// Create a window for display.
    resizeWindow("Display", 512, 512);
    imshow( "Display window", lower_green_hue_range ); // Show our image inside it.
    
    
    //this is for contours
    Mat canny_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    
    /// Detect edges using canny
    Canny( lower_red_hue_range, canny_output,100,200, 3 );
    /// Find contours
    findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
    
    RNG rng(12345);
    
    /// Draw contours
    Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
    
    for( int i = 0; i< contours.size(); i++ ){
        //Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255),rng.uniform(0,255) );
        Scalar color = Scalar(0,0,255);
        drawContours( drawing, contours, i,color, 2, 8, hierarchy, 0, Point() );
        red++;
    }
    
    /// Show in a window
    namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
    imshow( "Contours", drawing );
    
    /// Detect edges using canny
    Canny( lower_blue, canny_output,50, 150, 3 );
    /// Find contours
    findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
    
    for( int i = 0; i< contours.size(); i++ ){
        //Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255),rng.uniform(0,255) );
        Scalar color = Scalar(255,0,0);
        drawContours( drawing, contours, i,color, 2, 8, hierarchy, 0, Point() );
        blue++;
    }
    
    /// Detect edges using canny
    Canny( lower_green_hue_range, canny_output,100, 150, 3 );
    /// Find contours
    findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
    
    for( int i = 0; i< contours.size(); i++ ){
        //Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255),rng.uniform(0,255) );
        Scalar color = Scalar(0,255,0);
        drawContours( drawing, contours, i,color, 2, 8, hierarchy, 0, Point() );
        green++;
    }
    
    /// Show in a window
    namedWindow( "Contours2", CV_WINDOW_AUTOSIZE );
    imshow( "Contours2", drawing );
    
    printf("%lu", contours.size());
    printf("R: %d, G: %d, B: %d", red, blue, green);
    waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
}

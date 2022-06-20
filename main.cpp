//Hayatu Abdullahi - 10614230
//James Rogers Jan 2021 (c) Plymouth University
#include<iostream>
#include <fstream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#define PI 3.14159265

int main()
{

    VideoCapture InputStream("C:/AINT308Lib/Data/Task2 Video.mp4"); //Load in the video as an input stream
    const Point Pivot(592,52);                                      //Pivot position in the video

    //Open output file for angle data
    ofstream DataFile;
    DataFile.open ("C:/AINT308Repository/Task2/Data.csv");

    //loop through video frames
    while(true){

        //load next frame
        Mat Frame;
        InputStream.read(Frame);

        Mat FrameHSV;
        InputStream.read(Frame);

        //if frame is empty then the video has ended, so break the loop
        if(Frame.empty()){
            break;
        }

        //video is very high resolution, reduce it to 720p to run faster
        resize(Frame,Frame,Size(1280,720));

        //======================================================Your code goes here====================================================
        //this code will run for each frame of the video. your task is to find the location of the swinging green target, and to find
        //its angle to the pivot. These angles will be saved to a .csv file where they can be plotted in Excel.

        //Convert RGB to HSV for smaller changes. RGB makes big changes
        cvtColor(Frame, FrameHSV, COLOR_BGR2HSV);

        Mat FrameFiltered;   //To filter out te colors we don't want
        Vec3b LowerBound(37, 65, 65);
        Vec3b UpperBound(87, 255, 255);

        inRange(FrameHSV, LowerBound, UpperBound, FrameFiltered);

        //Choose a point only when filtered frame is true
        Moments m = moments(FrameFiltered, true);
        Point p(m.m10/m.m00, m.m01/m.m00);    // Finds the centre point around pendulum

        circle(Frame, Point(p), 20, Scalar(0,0,255), 5);       //Draw circle in the middle of pendulum
        line(Frame, Point(p), Point(p), Scalar(0,0,255), 15);  //Draw line in the middle of pendulum


        //Calculate the angle of the pendulum in reference to the pivot
        double angle1 = atan2(p.x - Pivot.x, p.y - Pivot.y);  //Find the inverse tangent of both points
        double angle2 = angle1 * 180 / PI;   //Convert from radians to degrees
        cout << "The Angle is " << angle2 << endl;


        // Write angle data to excel file. New data on new lines
        DataFile << angle2 << endl;


        //imshow("Video", FrameFiltered);


        //==============================================================================================================================

        //display the frame
        imshow("Video", Frame);
        waitKey(10);
    }

    DataFile.close(); //close output file
}

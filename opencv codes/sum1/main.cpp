#include <QCoreApplication>
#include "/usr/local/include/opencv2/opencv.hpp"
#include "/usr/local/include/opencv2/highgui/highgui.hpp"
#include "/usr/local/include/opencv/cv.h"
//#include "/usr/local/include/opencv2/imgcodecs.hpp"
#include<iostream>
#include<QMouseEvent>
#include "/usr/local/include/opencv2/opencv.hpp"

using namespace std;
using namespace cv;
int x_clk1,y_clk1,x_clk2,y_clk2,flag_clk=0;


//Sumakar::Copied this function from :http://opencv-srf.blogspot.in/2011/11/mouse-events.html
void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
     if  ( event == EVENT_LBUTTONDOWN )
     {
          cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;

        if(flag_clk==0)
        {
            x_clk1=x;
            y_clk1=y;
            flag_clk++;
        }

        else if(flag_clk==1)
        {
            x_clk2=x;
            y_clk2=y;
            flag_clk++;
        }

        else
        {
            flag_clk=0;
         }



     }
     else if  ( event == EVENT_RBUTTONDOWN )
     {
        //  cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
     }
     else if  ( event == EVENT_MBUTTONDOWN )
     {
      //    cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
     }
     else if ( event == EVENT_MOUSEMOVE )
     {
    //          cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;

     }
}
int main()
{
    VideoCapture cap(0);

    if(!cap.isOpened())
    {
        //return -1;
    }
    //cap.set(CV_CAP_PROP_POS_MSEC,300);
     //visit opencv-srf website for frame rate
   namedWindow("MyVideo",CV_WINDOW_AUTOSIZE);

   while(1)
   {
       Mat frame;
       bool bSuccess=cap.read(frame);


       if(!bSuccess)
       {break;}

       if (flag_clk==2)
       {
       Mat D (frame, Rect(x_clk1,y_clk1 , (x_clk2-x_clk1),(y_clk2-y_clk1)) );
       imshow("MyVideo",D);
       }
    else
       {
           imshow("MyVideo",frame);
       }
        setMouseCallback("MyVideo", CallBackFunc, NULL);

        if(waitKey(30)=='q')
       {
           break;
       }

   }
}

#include <QCoreApplication>
#include "/usr/local/include/opencv2/opencv.hpp"
#include "/usr/local/include/opencv2/highgui/highgui.hpp"
#include "/usr/local/include/opencv/cv.h"
//#include "/usr/local/include/opencv2/imgcodecs.hpp"
#include<iostream>
#include<QMouseEvent>
#include "/usr/local/include/opencv2/opencv.hpp"

#include <ctime>
#include <string>
using namespace std;
using namespace cv;
int x_clk1,y_clk1,x_clk2,y_clk2,flag_clk=0;
string path_to_save ="/home/sumakar/saved_videos/" ;

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
void time_stamp()
{
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer,sizeof(buffer),"%d_%m_%Y_%I_%M_%S.jpg",timeinfo);
    string sec_path_save(buffer);
    path_to_save=path_to_save+sec_path_save;

}

int main()
{   int i=0;
    VideoCapture cap(0);
    time_stamp();
    if(!cap.isOpened())
            {         cout<<"camera or video not found /n";    }

    int frame_width=   cap.get(CV_CAP_PROP_FRAME_WIDTH);
    int frame_height=   cap.get(CV_CAP_PROP_FRAME_HEIGHT);

   // VideoWriter video(path_to_save,CV_FOURCC('M','J','P','G'),30, Size(frame_width,frame_height),true);
    cap.set(CV_CAP_PROP_POS_MSEC,300);     //visit opencv-srf website for frame rate
    namedWindow("MyVideo",CV_WINDOW_AUTOSIZE);

    while(1)
    {
       Mat frame;
       bool bSuccess=cap.read(frame);
                   if(!bSuccess)
                   {break;}

       imshow("MyVideo",frame);

      // setMouseCallback("MyVideo", CallBackFunc, NULL);

       char c = (char)waitKey(33);
       if( c == 'q' )
       {
           imwrite(path_to_save,frame);

       }
       if(c==27)break;


   }
}

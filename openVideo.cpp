#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int* video2image(string videoname)
{
  int* inf=new int[4];
  VideoCapture capture(videoname);
  if (!capture.isOpened())
    {
      cout<<"failede open video"<<endl;
      return 0;
    }
  string image_name;
  Mat frame;
  int frame_number = capture.get(CV_CAP_PROP_FRAME_COUNT);
  int frame_fps = capture.get(CV_CAP_PROP_FPS);
  int frame_width = capture.get(CV_CAP_PROP_FRAME_WIDTH);
  int frame_height = capture.get(CV_CAP_PROP_FRAME_HEIGHT);
  inf[0]=frame_number;
  inf[1]=frame_fps;
  inf[2]=frame_width;
  inf[3]=frame_height;
  int count=1;
  for(count=1;count<=frame_number;count++)
    {
      capture>>frame;
      image_name="./photos/"+to_string(count)+".jpg";
      imwrite(image_name,frame);
    }
  return inf;
}

int image2video(int* inf,string name)
{
  VideoWriter writer;
  int isColor=1;
  int count=inf[0];
  int frame_fps=inf[1];
  int frame_width=inf[2];
  int frame_height=inf[3];
  string photo_name;
  Mat image;
  string videoname=name;
  writer = VideoWriter(videoname,CV_FOURCC('M','P','E','G'),frame_fps,Size(frame_width,frame_height),isColor);
  while(count>0)
  {
    photo_name="./photos/"+to_string(count)+".jpg";
    image=imread(photo_name);
    if(!image.data)
      {
        cout<<"couldn't load image"<<endl;
      }
    if(!image.empty())
      {
        imshow("image to video",image);
        waitKey(10);
      }
    writer.write(image);
    --count;
  }
  return 1;
}

int video_from_camera(string name)
{
  VideoCapture capture(1);
  if(!capture.isOpened())
    {
      cout<<"open camera failed"<<endl;
      return 0;
    }
  VideoWriter writer;
  int isColor=1;
  int frame_fps=30;
  int frame_width=capture.get(CV_CAP_PROP_FRAME_WIDTH);
  int frame_height=capture.get(CV_CAP_PROP_FRAME_HEIGHT);
  Mat image;
  string videoname=name;
  writer = VideoWriter(videoname,CV_FOURCC('M','P','E','G'),frame_fps,Size(frame_width,frame_height),isColor);
  while(true)
  {
    capture>>image;
    writer.write(image);
    imshow("camera show",image);
    if(waitKey(5)==27)
      break;
  }
  return 0;
}


int main()
{

  int* inf=new int[4];
  inf = video2image("youyisi.mpeg");
  image2video(inf,"water.mpeg");
  return 0;
}

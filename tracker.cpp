#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/dnn.hpp>
#include <iostream>
#include <cstring>

using namespace std;
using namespace cv;

int main( int argc, char** argv ){
  // show help
  /*if(argc<2){
    cout<<
      " Usage: tracker <video_name>\n"
      " examples:\n"
      " example_tracking_kcf Bolt/img/%04d.jpg\n"
      " example_tracking_kcf faceocc2.webm\n"
      << endl;
    return 0;
  }*/
 
printf("starting tracker...\n");
  // 1. Load the network (Using an ONNX model as an example)
    //cv::dnn::Net net_head = cv::dnn::readNet("..\\data\\nanotrack_head_sim.onnx");
    
//printf("readNet complete...\n");
    //cv::dnn::Net net_backbone = cv::dnn::readNet("..\\data\\nanotrack_backbone_sim.onnx");
    
//printf("readNet complete...\n");
    // Optional: Configure target backend (e.g., CUDA/GPU or default CPU)
    /*net_head.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
    net_head.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
  
    net_backbone.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
    net_backbone.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
*/

// 1. Configure TrackerNano parameters
    cv::TrackerNano::Params params;
    params.backbone = "..\\data\\nanotrack_backbone_sim.onnx";
    params.neckhead = "..\\data\\nanotrack_head_sim.onnx";
    params.backend = cv::dnn::DNN_BACKEND_OPENCV;
    params.target = cv::dnn::DNN_TARGET_CPU;

// 2. Instantiate TrackerNano
    cv::Ptr<cv::TrackerNano> tracker = cv::TrackerNano::create(params);

    // 3. Open Video Stream
    cv::VideoCapture cap("sample.mp4");
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open video file." << std::endl;
        return -1;
    }

    cv::Mat frame;
    cap >> frame;

    // 4. ROI Selection
    std::string winName = "TRACK WIN";

    // 2. Create a resizable window (Crucial step)
    cv::namedWindow(winName, cv::WINDOW_NORMAL);

    // 3. Set the custom window dimensions (Width, Height)
    cv::resizeWindow(winName, 960, 540);
    cv::Rect bbox = cv::selectROI(winName, frame, false);

  //quit if ROI was not selected
  if(bbox.width==0 || bbox.height==0)
  {
	  printf("ROI width height 0...\n");
	  return 0;
  }

  // initialize the tracker
  tracker->init(frame,bbox);

  // perform the tracking process
  printf("Start the tracking process, press ESC to quit.\n");
  for ( ;; )
  {
    // get frame from the video
    cap >> frame;

    // stop the program if no more images
    if(frame.rows==0 || frame.cols==0)
      break;

    // update the tracking result
    tracker->update(frame,bbox);

    // draw the tracked object
    rectangle( frame, bbox, Scalar( 255, 0, 0 ), 2, 1 );

    // show image with the tracked object
    imshow(winName,frame);

    //quit on ESC button
    if(waitKey(1)==27)break;
  }
/* sample while
 while (cap.read(frame)) {
        // 6. Update target prediction tracking
        bool success = tracker->update(frame, bbox);

        if (success) {
            cv::rectangle(frame, bbox, cv::Scalar(0, 255, 0), 2, 1);
            cv::putText(frame, "Tracking", cv::Point(50, 50), cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar(0, 255, 0), 2);
        } else {
            cv::putText(frame, "LOST Status", cv::Point(50, 50), cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar(0, 0, 255), 2);
        }

        cv::imshow("NanoTrack Demo", frame);
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }
 * */
  return 0;
}

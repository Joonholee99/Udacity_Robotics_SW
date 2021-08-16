#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define Global Variable
ros::ServiceClient client;

void drive_robot(float lin_x, float ang_z){
    ROS_INFO_STREAM("Move to ball position");

    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;

    if(!client.call(srv)){
        ROS_ERROR("Failed to call service safe_move");
    }
}

void process_image_callback(const sensor_msgs::Image img){
    int white_pixel = 255;
    int white_idx = 3; // 0:Left , 1:Forward, 2:Right
    bool detected = false;

    for (int i = 0; i<img.height * img.step-2;i+=3){
        int step_idx = i%img.step;
        
        if (step_idx < (int)(img.step/3)){
            white_idx = 0;
            
        }
        else if(step_idx >= (int)(img.step/3) && step_idx < 2*((int)(img.step/3))){
            white_idx = 1;
        }
        else if(step_idx >= 2*((int)(img.step/3))){
            white_idx = 2;
        }

        if (img.data[i] == white_pixel && img.data[i+1] == white_pixel && img.data[i+2] == white_pixel){
            detected = true;
            break;
        }
    }
    printf("White is Detected at : %d \n",white_idx);
    if (detected)
    {
        if (white_idx == 0 && detected == true){
        drive_robot(0.0, 0.5);
        }
        else if(white_idx == 1 && detected == true){
            drive_robot(1.0, 0.0);
        }
        else if(white_idx == 2 && detected == true){
            drive_robot(0.0, -0.5);
        }
    }
    else{drive_robot(0.0, 0.0);}

}

int main(int argc, char** argv){
    // init the ros node
    ros::init(argc,argv, "process_image");
    ros::NodeHandle n;

    // Define Client service 
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw",10, process_image_callback);

    ros::spin();

    return 0;

}
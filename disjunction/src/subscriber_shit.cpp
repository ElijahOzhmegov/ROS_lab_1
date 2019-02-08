#include "ros/ros.h"
#include "std_msgs/Bool.h"
#include "stdio.h"

std_msgs::Bool disjuncted_msg;
int remembered_msg;

int flag = true;            // if flag is true, a new message will be remembered
int do_publishing = false;  // if flag is up, then message will be sent to bool_out

void recieve(const std_msgs::Bool msg)
{
    std::cout << "Number was got: " << msg;
    
    if (flag == false)
    {
        {
            std_msgs::Bool disjuncted_msg;
            int bubble = msg.data;
            disjuncted_msg.data = remembered_msg | bubble;      

            std::cout << "disjuncted_msg: " << disjuncted_msg << std::endl;
            
            do_publishing = true;
        }

        flag = true;
    }else{
        remembered_msg = msg.data;
        flag = false;
    }
    
    return; 
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "subscriber");
    
    ros::NodeHandle n;
  
    ros::Subscriber sub = n.subscribe("bool_in", 1000, recieve);
    ros::Publisher  pub = n.advertise<std_msgs::Bool>("bool_out", 1000);

    ros::Rate loop_rate(100); 
    
    while (ros::ok())
    {
        if (do_publishing) pub.publish(disjuncted_msg);
        
        ros::spinOnce();
  
        loop_rate.sleep();
        
        do_publishing = false;
    }
    
    ros::spin();

    return 0;
}

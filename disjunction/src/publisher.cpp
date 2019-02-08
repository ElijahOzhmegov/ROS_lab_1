#include "ros/ros.h"
#include "std_msgs/Bool.h"
#include "stdio.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "publisher");
    
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<std_msgs::Bool>("bool_in", 1000);

    ros::Rate loop_rate(1);

    int bubble = 0;
    std::cout << "Enter a number: ";
    while (std::cin >> bubble)
    {
        std_msgs::Bool msg;
        msg.data = bubble;

    
        pub.publish(msg);
        
        std::cout << "Enter a number: ";
        
        loop_rate.sleep();
    }
    ros::spinOnce();

    return 0;
}

#include "ros/ros.h"
#include "std_msgs/Bool.h"
#include "stdio.h"


class SubscribeAndPublish
{
public:
    SubscribeAndPublish()
    {
        pub_ = n_.advertise<std_msgs::Bool>("bool_out", 1);

        sub_ = n_.subscribe("bool_in", 1, &SubscribeAndPublish::callback, this);
        
        doSent = false;
    }

    void callback(const std_msgs::Bool& input)
    {
        std::cout << "Number was got: " << input;
        
        if (doSent)
        {
            std_msgs::Bool output;

            output.data = prevMsg.data | input.data;
            std::cout << "Disjuncted " << output << std::endl;

            pub_.publish(output);
            
            doSent = false;
            
        }else{
            prevMsg.data = input.data;
            
            doSent = true;
        }
    }

private:
    ros::NodeHandle n_; 
    ros::Publisher  pub_;
    ros::Subscriber sub_;

    bool doSent;
    std_msgs::Bool prevMsg;
};


int main(int argc, char **argv)
{
    ros::init(argc, argv, "subscriber");
    
    SubscribeAndPublish Mr_nipple;
    
    ros::spin();

    return 0;
}

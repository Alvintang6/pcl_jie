
#include <ros/ros.h>
#include <pcl/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl/io/pcd_io.h>

using namespace std;
class cloudHandler
{
public:
	cloudHandler()
	: frame(0)
	{
		pcl_sub = nh.subscribe("kinect2/sd/points", 10, &cloudHandler::cloudCB, this);
		
	}



void cloudCB(const sensor_msgs::PointCloud2 &input)
{
    
    oss.str("");
    oss << "./" << std::setfill('0') << std::setw(4) << frame;
    const std::string baseName = oss.str();
    const std::string cloudName = baseName + "_cloud.pcd";

    pcl::PointCloud<pcl::PointXYZ> cloud;
    pcl::fromROSMsg(input, cloud);
    pcl::io::savePCDFileASCII (cloudName, cloud);
    ++frame;
}

protected:
	ros::NodeHandle nh;
	std::ostringstream oss;
	ros::Subscriber pcl_sub;
	size_t frame;

};

main (int argc, char **argv)
{
    ros::init (argc, argv, "pcl_write");

    cloudHandler runing;
    

    ros::spin();

    return 0;
}
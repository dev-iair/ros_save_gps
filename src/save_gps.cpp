#include <ros/ros.h>
#include <sensor_msgs/NavSatFix.h>
#include <fstream>
#include <string>

using namespace std;


class SaveGPS
{
  protected:
    ros::NodeHandle nh_;

  private:
    int count = 0;
    std::string file_dir_;
    std::string latitude_;
    std::string longitude_;
    std::string altitude_;

  public:
    string topic_;
    ros::Subscriber sub_;

    ////////////////////////////////////////////////////////////////////////////////
    // Callback
  void save_gps(const sensor_msgs::NavSatFix::ConstPtr& msg)
  {
    std::stringstream file;
    file << file_dir_ << count << ".json";

    latitude_ = std::to_string(msg->latitude);
    longitude_ = std::to_string(msg->longitude);
    altitude_ = std::to_string(msg->altitude);

    ROS_INFO ("GPS DATA SAVE TO %s", file.str().c_str());

    std::stringstream json;
    json << "{'latitude':" << latitude_ << ",'longitude':" << longitude_ << ", 'altitude':" << altitude_ << "}";

    std::ofstream write_json;
    write_json.open(file.str().c_str());
    write_json.write(json.str().c_str(),json.str().size());
    write_json.close();

    count++;
  }

 SaveGPS ()  {
    ros::NodeHandle priv_nh("~");
    priv_nh.getParam("file_dir", file_dir_);
    topic_ = "input";
    sub_ = nh_.subscribe(topic_, 1, &SaveGPS::save_gps, this);

    }
};

int main (int argc, char** argv)
{
  ros::init(argc, argv, "save_gps");
  SaveGPS b;
  ros::spin();
  return 0;
}
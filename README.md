##Pioneer 3at slam

First install Kinect on ROS kinetic[https://www.reddit.com/r/ROS/comments/6qejy0/openni_kinect_installation_on_kinetic_indigo/]

sudo apt-get install git build-essential python libusb-1.0-0-dev freeglut3-dev openjdk-8-jdk

sudo apt-get install doxygen graphviz mono-complete

cd ~/
mkdir kinect

cd ~/kinect
git clone https://github.com/OpenNI/OpenNI.git
cd OpenNI
git checkout Unstable-1.5.4.0
cd Platform/Linux/CreateRedist
chmod +x RedistMaker
./RedistMaker
cd ../Redist/OpenNI-Bin-Dev-Linux-[xxx]  (where [xxx] is your architecture and this particular OpenNI release. In my case, this is x64)
sudo ./install.sh

cd ~/kinect
git clone https://github.com/avin2/SensorKinect
cd SensorKinect
cd Platform/Linux/CreateRedist
chmod +x RedistMaker
./RedistMaker
cd ../Redist/Sensor-Bin-Linux-[xxx]  (where [xxx] is your architecture and this particular OpenNI release. In my case this was x64-v5.1.2.1)

chmod +x install.sh
sudo ./install.sh
sudo ./install.sh -u

sudo apt-get install ros-kinetic-openni*

cd ~/kinect 
NITE-Bin-Dev-Linux-x64-v1.5.2.23
sudo ./install.sh

cd ~/catkin_ws/src
git clone https://github.com/ros-drivers/openni_tracker.git

cd ~/catkin_ws
catkin_make
catkin_make install

Install freenect, rtabmap and use it:

roslaunch freenect_launch freenect.launch depth_registration:=true
roslaunch rtabmap_ros rgbd_mapping.launch rtabmap_args:="--delete_db_on_start" rviz:=true rtabmapviz:=false
rviz

Use laserscan
roslaunch to_laserscan.launch

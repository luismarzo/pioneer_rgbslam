# Pioneer 3at slam

First install Kinect on ROS kinetic[https://www.reddit.com/r/ROS/comments/6qejy0/openni_kinect_installation_on_kinetic_indigo/]

`sudo apt-get install git build-essential python libusb-1.0-0-dev freeglut3-dev openjdk-8-jdk`

`sudo apt-get install doxygen graphviz mono-complete`

`cd ~/`
`mkdir kinect`

`cd ~/kinect`
`git clone https://github.com/OpenNI/OpenNI.git`
`cd OpenNI`
`git checkout Unstable-1.5.4.0`
`cd Platform/Linux/CreateRedist`
`chmod +x RedistMaker`
`./RedistMaker`
`cd ../Redist/OpenNI-Bin-Dev-Linux-[xxx]`  
(where [xxx] is your architecture and this particular OpenNI release. In my case, this is x64)
`sudo ./install.sh`

`cd ~/kinect`
`git clone https://github.com/avin2/SensorKinect`
`cd SensorKinect`
`cd Platform/Linux/CreateRedist`
`chmod +x RedistMaker`
`./RedistMaker`
`cd ../Redist/Sensor-Bin-Linux-[xxx]`
(where [xxx] is your architecture and this particular OpenNI release. In my case this was x64-v5.1.2.1)

`chmod +x install.sh`
`sudo ./install.sh`
`sudo ./install.sh -u`

`sudo apt-get install ros-kinetic-openni*`

`cd ~/kinect `
`NITE-Bin-Dev-Linux-x64-v1.5.2.23`
`sudo ./install.sh`

`cd ~/catkin_ws/src`
`git clone https://github.com/ros-drivers/openni_tracker.git`

`cd ~/catkin_ws`
`catkin_make`
`catkin_make install`

Change the ermisions in the port to use ARIA

`cd /dev`
`sudo chmod 777 ttyUSB0`


Install freenect, rtabmap and use it:
 `sudo apt-get install ros-kinetic-freenect-camera`
`roslaunch freenect_launch freenect.launch depth_registration:=true`
`roslaunch rtabmap_ros rgbd_mapping.launch rtabmap_args:="--delete_db_on_start" rviz:=true rtabmapviz:=false`
`rviz`

Use laserscan
`sudo apt-get install ros-kinetic-pointcloud-to-laserscan`
`roslaunch slam to_laserscan_scan.launch`


For odometry use Rosaria
`roslaunch rosaria_client rosaria_client_launcher.launch` (or something like that)


2D map
`rosrun gmapping slam_gmapping scan:= (topic)`
`rosrun map_server map_saver -f <map_name>`
http://wiki.ros.org/slam_gmapping/Tutorials/MappingFromLoggedData#record

Camera calibration
http://wiki.ros.org/camera_calibration
http://wiki.ros.org/camera_calibration/Tutorials/MonocularCalibration

Navigation
http://wiki.ros.org/navigation/Tutorials/RobotSetup

Others
https://github.com/danimtb/pioneer3at_ETSIDI
http://wiki.ros.org/navigation/Tutorials/Using%20rviz%20with%20the%20Navigation%20Stack
https://github.com/rosbook/effective_robotics_programming_with_ros

## Raspberry pi

Add memory swap for building packages
https://digitizor.com/create-swap-file-ubuntu-linux/

Enable wifi Ubuntu Mate in raspberry pi 3b+
	Step 1: Open terminal
	Step 2: type this code "sudo nano /etc/NetworkManager/NetworkManager.conf"

	You will be directed to edit what's in the NetworkManager.conf
	Step 3: Change the "false" to "true" and save it and close the nano
	Step 4: type this code "sudo service network-manager restart
	
Install Aria
https://web.archive.org/web/20180205212122/http://robots.mobilerobots.com/wiki/Aria
In this page, download ARIA 2.9.4 - Ubuntu 16.04 (xenial) or later, amd 64-bit architecture
`dpkg -i --force-all libaria_2.9.4+ubuntu16_amd64.deb`
`cd /usr/local/Aria`
`make clean`
`make`

Later, if you have problems doing catkin_make in your package and appear "Error: Aria.h not found", try using this
`catkin_make --force-cmake`

if you have problems with "make", install this 
  ` sudo apt-get install build-essential software-properties-common -y`
 `  sudo add-apt-repository ppa:ubuntu-toolchain-r/test -y `
   `sudo apt-get update`
   `sudo apt-get install gcc-snapshot -y `
   


Install freenect camera and all the stuff
 `sudo apt-get install ros-kinetic-freenect-camera`
 `sudo apt-get install ros-kinetic-freenect-launch`
 `sudo apt-get install ros-kinetic-rtabmap-ros`
 `sudo apt-get install ros-kinetic-move-base`
 
Give permision to Rosaria.cfg in the packages
`sudo chmod a+x /home/luis/ws_rosaria/src/rosaria/cfg/RosAria.cfg` 

if still having problems with the compilation, install gcc+6
`sudo add-apt-repository ppa:ubuntu-toolchain-r/test`
`sudo apt update`
`sudo apt install gcc-6`
 

Export ROSMASTER (write in .basrc inside the raspberry)
`export ROS_MASTER_URI=http://Luis:11311`

Connect via ssh (you have to enable ssh and not be connected to eduroam)
	`ssh luisraspy@luispi.local`
	`ssh luis@luis-desktop.local`

You always have to give permisions to ttyUSB0
	`cd /dev`
	`sudo chmod 777 ttyUSB0`


## In order to use it:
`roslaunch p3at_slam pioneer3at-rosaria.launch`
`roslaunch p3at_slam global_navigation_p3at.launch`

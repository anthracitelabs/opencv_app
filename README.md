# opencv_app
a sample opencv application to demonstrate object tracking 

# What is Object Tracking?
<p>Object Tracking means predicting object location at some future point in time. So object tracking in a video is basically estimating the location of an object in subsequent frames. This can be done by developing both a <i>motion model</i> and an <i>appearance model</i>.
</p>

<p>The motion model will estimate the position and velocity of a particular object in pixel coordinates and then use that information to predict its location in future video frames. Then the appearance model, which encodes what the object looks like, will search the region around the predicted location from the motion model to fine-tune the location of the object.</p>

<p>In this demonstration we will use OpenCV API tracker class. So as a concrete example suppose we're interested in tracking a specific object like the race car identified here in the first frame of a video clip. In order to initiate the tracking algorithm we need to specify the initial location of the object and to do this we define a bounding box shown here in blue which consists of two sets of pixel coordinates which define the upper left and lower right corners of the bounding box. Once the tracking algorithm is initialized with this information the goal is to then track the object in subsequent video frames by producing a bounding box in each new video frame</p> 


Note that after OpenCV 4.5.0 custom algorithms were moved to the contrib [repo](https://github.com/opencv/opencv_contrib). The policy is when an algorithm is mature enough it is moved to the main repo.


In this sample Tracker Nano is used. This tracker requires model data to run. This data can be found [here](https://github.com/HonglinChu/SiamTrackers.git).


[Tracker intro](https://docs.opencv.org/5.0/tutorials_contrib/tracking/tutorial_introduction_to_tracker.html)

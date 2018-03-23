# VisionUtils package

This approach is based on the Monocular Visual Odometry code provided in: https://github.com/avisingh599/mono-vo using the given approach as a feature detection and extraction template. It has been modifying used SURF feature extraction and Laplacian filter to track the blur changes over time, on an attempt to find collisions.

Requirements:
    OpenCV 3.X
    Qt5 for standalone

Install:
    cd <folder_path>
    mkdir build
    cd build
    cmake ..
    make
    sudo make install

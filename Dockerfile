FROM ubuntu:latest
# Install yarp prerequisites
RUN apt update && apt install -y cmake g++ wget unzip \
    build-essential git cmake cmake-curses-gui swig \
    libeigen3-dev \
    libace-dev \
    libedit-dev \
    libsqlite3-dev \
    libtinyxml-dev \
    qtbase5-dev qtdeclarative5-dev qtmultimedia5-dev \
    qml-module-qtquick2 qml-module-qtquick-window2 \
    qml-module-qtmultimedia qml-module-qtquick-dialogs \
    qml-module-qtquick-controls qml-module-qt-labs-folderlistmodel \
    qml-module-qt-labs-settings \
    libqcustomplot-dev \
    libgraphviz-dev \
    libjpeg-dev \
    libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev \
    gstreamer1.0-plugins-base \
    gstreamer1.0-plugins-good \
    gstreamer1.0-plugins-bad \
    gstreamer1.0-libav \
    python3.10-dev \
    pip

# Install ycm
RUN cd / && git clone https://github.com/robotology/ycm.git && mkdir robotology && mv ycm/ robotology/ \
    && cd robotology/ycm && mkdir build \
    && cd build && cmake .. && make && make install

# Install yarp
RUN cd /robotology && git clone https://github.com/robotology/yarp.git \
	&& cd yarp && mkdir build && cd build \ 
    && cmake -D ENABLE_yarpcar_mjpeg=ON -D ENABLE_yarpmod_ffmpeg_grabber=ON \
        -D YARP_COMPILE_BINDINGS=ON -D CREATE_PYTHON=ON .. \
	&& make -j8 && make install

# Install openai

RUN pip install openai

RUN apt install -y vim

COPY . /yarpGPT

ENV PYTHONPATH="/robotology/yarp/build/lib/python3:/yarpGPT"


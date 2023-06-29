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

# Install python openai

RUN pip install openai

# Install openai c++ dependencies

RUN apt update && apt install -y curl zip unzip tar

RUN git clone https://github.com/Microsoft/vcpkg.git && \
    cd vcpkg && ./bootstrap-vcpkg.sh -disableMetrics && \
    ./vcpkg integrate install && ./vcpkg install curl[tool] && \
    ./vcpkg install nlohmann-json && \
    echo "ciao"

# Install openai c++ community library
RUN git clone https://github.com/D7EAD/liboai.git && \
    cd liboai/liboai && \
    cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=/vcpkg/scripts/buildsystems/vcpkg.cmake \
    -DCMAKE_POSITION_INDEPENDENT_CODE=true && \
    cd build && make -j8 && make install

# Install vim, I need vim, you do you, comment the following line if you dont need it
RUN apt install -y vim qml-module-qtquick-controls2

# Install yarpGPT
COPY . /yarpGPT

RUN cd /yarpGPT && cmake -B build -S . \
    && cd build && make install -j8 && ldconfig

ENV PYTHONPATH="/robotology/yarp/build/lib/python3:/yarpGPT/src/python"


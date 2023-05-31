#!/bin/bash

if [[ -z $1 ]]
then
  IMG=fbrand-new/yarpgpt:devel
else
  IMG=$1
fi

docker run -it --rm --privileged --gpus=all --network host --pid host\
  -v /etc/localtime:/etc/localtime -v /tmp/.X11-unix:/tmp/.X11-unix \
  -v ${XAUTHORITY}:/root/.Xauthority -e DISPLAY=$DISPLAY \
  -e QT_X11_NO_MITSHM=1 -v /etc/hosts:/etc/hosts \
  $IMG bash
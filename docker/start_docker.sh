#!/bin/bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

cd $SCRIPT_DIR

if [[ -z $1 ]]
then
  IMG=fbrand-new/yarpgpt:devel
else
  IMG=$1
fi

if [[ -z $2 ]]
then
  CMD=bash
else
  CMD=$2
fi

docker run -it --rm --privileged --gpus=all --network host --pid host --name yarpgpt \
  -v /etc/localtime:/etc/localtime -v /tmp/.X11-unix:/tmp/.X11-unix \
  -v ${XAUTHORITY}:/root/.Xauthority -e DISPLAY=$DISPLAY \
  -e QT_X11_NO_MITSHM=1 -v /etc/hosts:/etc/hosts -v ${HOME}/.config/yarp:/root/.config/yarp \
  --env-file ../.env $IMG $CMD

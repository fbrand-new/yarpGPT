#!/bin/bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

cd $SCRIPT_DIR/..

./docker/build_docker.sh

cd $SCRIPT_DIR

docker compose -f docker-compose-gui.yml up 


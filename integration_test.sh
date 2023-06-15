#!/bin/bash

up=true
down=false

while [ $# -gt 0 ] ; do
    case $1 in 
        --up)   up=true ;;
        --down) up=false ;;
    esac 
    shift
done

SCRIPT_DIR=$( cd -- "$( dirname -- "$BASH_SOURCE[0]}" )" &> /dev/null && pwd )

cd $SCRIPT_DIR

if [ "$up" = true ] ; then
    docker compose -f docker/docker-compose-test.yml up
else
    docker compose -f docker/docker-compose-test.yml down
fi
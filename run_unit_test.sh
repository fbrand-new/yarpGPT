#!/bin/bash

SCRIPT_DIR=$( cd -- "$( dirname -- "$BASH_SOURCE[0]}" )" &> /dev/null && pwd )

cd $SCRIPT_DIR/tests

python3 -m unittest discover -p unit*.py
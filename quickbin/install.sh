#!/bin/bash 

# get current directory
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

# modify bashrc
cat >> ~/.bashrc << EOF

# Quickbin
source ${SCRIPT_DIR}/path_setup.sh
source ${SCRIPT_DIR}/command_setup.sh

EOF

# source 
source ~/.bashrc

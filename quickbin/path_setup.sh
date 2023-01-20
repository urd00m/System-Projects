#!/bin/bash

# get current script directory 
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

# setup path
export PATH=$PATH:${SCRIPT_DIR}/bin
export QBIN_DIR=${SCRIPT_DIR}/bin
export PROJECT_DIR=${SCRIPT_DIR}/..

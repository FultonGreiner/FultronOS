#!/bin/bash -e

# git clone --recurse-submodules git@github.com:renode/renode.git

/Users/fultongreiner/renode/renode-test tests/test-basic.robot --variable PWD_PATH:"${PWD}"

# robot tests/test-basic.robot

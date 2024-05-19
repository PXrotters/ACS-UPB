#!/bin/bash

sudo apt-get update
sudo apt-get install -y clang clang-tidy python3
sudo python3 -m pip install -U pip
sudo python3 -m pip install cpplint

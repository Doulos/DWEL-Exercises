#!/bin/bash
ran=$RANDOM
echo "Creating 50M file of randomness called 50M${ran}.dat"
dd if=/dev/urandom of=50M${ran}.dat bs=1M count=50 

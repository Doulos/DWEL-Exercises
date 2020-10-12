#!/bin/bash
while :
do
	date | logger -i -t logdaemon
	sleep 1m
done

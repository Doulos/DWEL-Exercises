#!/bin/bash
set -e
PIDFILE=/var/run/startstopdaemon.pid
DAEMON=/home/root/logdaemon.sh

case "$1" in
    start)
        echo "Starting daemon: $DAEMON"
        start-stop-daemon --start --make-pidfile --pidfile $PIDFILE --exec $DAEMON & 
        ;;
    stop)
        echo "Stopping daemon: $DAEMON"
        start-stop-daemon --stop --pidfile $PIDFILE
        rm -rf $PIDFILE
        ;;
    restart)
        echo "Restarting daemon: $DAEMON"
		start-stop-daemon --stop --pidfile $PIDFILE
        rm -rf $PIDFILE
		start-stop-daemon --start --make-pidfile --pidfile $PIDFILE --exec $DAEMON &
		;;
    *)
        echo "Usage: "$1" {start|stop|restart}"
	exit 1
esac

exit 0


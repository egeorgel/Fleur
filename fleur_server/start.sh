#!/bin/sh
WEBSOCKIFY="/var/www/fleur.how/fleur_server/websockify"

exec socat tcp-listen:2000,reuseaddr,fork,crlf exec:'fleur --no-rlwrap' &
exec socat tcp-listen:2001,reuseaddr,fork,crlf,range=127.0.0.1/32 exec:'fleur -s --no-rlwrap' &
exec $WEBSOCKIFY/run 2002 localhost:2001 &

wait


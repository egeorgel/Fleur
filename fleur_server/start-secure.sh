#!/bin/sh
WEBSOCKIFY="/var/www/fleur.how/fleur_server/websockify"

exec socat openssl-listen:2100,reuseaddr,fork,crlf,cert=/etc/letsencrypt/live/www.fleur.how/privkeyfullchain.pem,verify=0 exec:'fleur --no-rlwrap' &
socat tcp-listen:2101,reuseaddr,fork,crlf,range=127.0.0.1/32 exec:'fleur -s --no-rlwrap' &
$WEBSOCKIFY/run 2102 localhost:2101 --cert=/etc/letsencrypt/live/www.fleur.how/fullchain.pem --key=/etc/letsencrypt/live/www.fleur.how/privkey.pem --ssl-only &

wait

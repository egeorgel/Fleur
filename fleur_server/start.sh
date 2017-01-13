#!/bin/sh
WEBSOCKIFY="/var/www/fleur.how/fleur_server/websockify"
FLEUR_TELNET="exec socat tcp-listen:2000,reuseaddr,fork,crlf exec:'fleur --no-rlwrap'"
FLEUR_SILENT_TELNET="socat tcp-listen:2001,reuseaddr,fork,crlf,range=127.0.0.1/32 exec:'fleur -s --no-rlwrap'"
FLEUR_WEBSOCKET="$WEBSOCKIFY/run 2002 localhost:2001"
parallel ::: "$FLEUR_TELNET" "$FLEUR_SILENT_TELNET" "$FLEUR_WEBSOCKET"

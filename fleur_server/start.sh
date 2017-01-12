#!/bin/sh
WEBSOCKIFY="/var/www/fleur.how/fleur_server/websockify"
FLEUR_TELNET="exec socat tcp-listen:2000,reuseaddr,fork,crlf exec:fleur"
FLEUR_SILENT_TELNET="exec socat tcp-listen:2001,reuseaddr,fork,crlf exec:'fleur -s'"
FLEUR_WEBSOCKET="$WEBSOCKIFY/run 2002 localhost:2001"
parallel ::: "$FLEUR_TELNET" "$FLEUR_SILENT_TELNET" "$FLEUR_WEBSOCKET"

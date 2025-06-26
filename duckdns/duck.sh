#!/bin/sh

echo "Starting DuckDNS updater"
while true; do
  curl -k "https://www.duckdns.org/update?domains=${DOMAIN}&token=${TOKEN}&ip="
  echo "$(date): updated" >> /var/log/duckdns.log
  sleep 300
done

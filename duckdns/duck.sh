#!/bin/sh

echo "Starting DuckDNS updater"
while true; do
  RESPONSE=$(curl -ks "https://www.duckdns.org/update?domains=${DOMAIN}&token=${TOKEN}&ip=")
  echo "$(date): update response = $RESPONSE" >> /var/log/duckdns.log
  sleep 300
done

#!/usr/bin/env bash

echo -n "Ingresa la interfaz de red que deseas modificar:"
read interface
echo -n "Ingresa la MAC Address que deseas que trabaje en esa:"
read mac

sudo ip link set dev ${interface} down
sudo ip link set dev ${interface} address ${mac}
sudo ip link set dev ${interface} up
sudo ip link show ${interface}


#!/usr/bin/env bash
echo "Ingresa el nombre de la interfaz de red"
read interface
echo "Ingresa la ip que deseas utilizar para la interfaz"
read ip
echo "Ingresa el prefijo que utilizas para la interfaz ${interface}"
read prefix
echo "Ingresa la ip del gateway"
read gate
ip route flush dev ${interface}
ip addr add ${ip}/${prefix} dev ${interface}
ip route add default via ${gate}
echo "Listo uwu"

#!/usr/bin/env bash
echo -n "Ingresa el nombre de la interfaz de red: "
read interface
echo -n "Ingresa la ip que deseas utilizar para la interfaz: "
read ip
echo -n "Ingresa el prefijo que utilizas para la interfaz ${interface}: "
read prefix
echo -n "Ingresa la ip del gateway: "
read gate
ip route flush dev ${interface}
ip addr add ${ip}/${prefix} dev ${interface}
ip route add default via ${gate}
echo "Listo uwu"

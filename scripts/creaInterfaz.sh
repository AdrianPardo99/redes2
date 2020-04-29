#!/usr/bin/env bash

echo "Creacion de la interfaz virtual tap0"
sudo tunctl -t tap0 -u $(whoami)
echo "Habilitación de la interfaz tap0"
sudo ip l s dev tap0 up
echo "Por favor ingresa la IP que se le va a asignar la interfaz tap0"
read ipAddr
sudo ip address add ${ipAddr} dev tap0

while true; do
  echo "Deseas ingresar algun enrutamiento: 1 -> Si / 2 -> No"
  read var
  if [ ${var} == "2" ];then
    break
  else
    echo "Ingresa la red a la que deseas enrutar junto a su mascara de subred"
    read network
    sudo ip route add ${network} via ${ipAddr} dev tap0
  fi
done
echo "Se creo la interfaz de red tap0, con la siguiente tabla de enrutamiento:"
route -n | grep tap0

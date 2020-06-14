#!/usr/bin/env bash

echo -n "Ingresa el nombre de la interfaz virtual que deseas crear: "
read virtualInt
echo "Creacion de la interfaz virtual ${virtualInt}: "
sudo tunctl -t ${virtualInt} -u $(whoami)
echo -n "Habilitación de la interfaz ${virtualInt}: "
sudo ip l s dev ${virtualInt} up
echo -n "Por favor ingresa la IP que se le va a asignar la interfaz ${virtualInt}: "
read ipAddr
echo -n "Por favor ingresa el prefijo de la mascara a la cual deseas que tenga ${virtualInt}: "
read prefijo
sudo ip address add ${ipAddr}/${prefijo} dev ${virtualInt}

while true; do
  echo -n "Deseas ingresar algun enrutamiento: 1 -> Si / 2 -> No: "
  read var
  if [ ${var} == "2" ];then
    break
  else
    echo -n "Ingresa la red a la que deseas enrutar junto a su mascara de subred: "
    read network
    sudo ip route add ${network} via ${ipAddr} dev ${virtualInt}
  fi
done
echo "Se creo la interfaz de red tap0, con la siguiente tabla de enrutamiento:"
route -n | grep tap0

#!/usr/bin/env bash

echo -n "Ingresa el nombre de la interfaz virtual que deseas eliminar: "
read virtualInt
echo "Se eliminara la tabla de enrutamiento para ${virtualInt}: "
sudo ip route flush dev ${virtualInt}
echo "A continuación se eliminara la interfaz de red ${virtualInt}: "
sudo ip l d ${virtualInt}
echo "Tarea finalizada"

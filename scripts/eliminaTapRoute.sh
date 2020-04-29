#!/usr/bin/env bash

echo "Se eliminara la tabla de enrutamiento para tap0"
sudo ip route flush dev tap0
echo "A continuación se eliminara la interfaz de red tap0"
sudo ip l d tap0
echo "Tarea finalizada"

#!/usr/bin/env bash
echo -n "Escribe el path del servidor TFTP: "
read path
echo $path
while true; do
  echo ""
  echo "Deseas ingresar un router al cual se le hara su backup: 1 -> Si / 2 -> No"
  read var
  if [ ${var} == "2" ];then
    break
  elif [ ${var} == "1" ];then
    router="Router"
    echo -n "Ingresa la ip del router: "
    read ip
    echo -n "Ingresa el puerto del router: "
    read port
    echo -n "Ingresa el numero de router: "
    read num
    mkdir ${path}${router}"-"${num}
    sudo chown nobody ${path}${router}"-"${num}
    sudo chmod 777 ${path}${router}"-"${num}
    ./script.sh $ip $port $num
    sleep 1
    sudo mv "${path}router-${num}-confg" "${path}${router}-${num}/router-${num}-confg"
  else
    echo "Ingresa una opción valida"
  fi
done

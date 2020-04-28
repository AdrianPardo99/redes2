# Información respecto al proyecto de ejemploEnClase.gns3

Inicialmente se cuenta con 1 router 3745 con algunos puertos de los cuales contienen un enrutamiento con la siguiente configuración en el terminal del router

Inicialmente vemos puertos utilizados y la configuración de los puertos

\# sh ip int br

\# conf t

\#(config) ip route 192.168.1.0 255.255.255.0 <Interface -> fastEthernet0/0>

\#(config) ip route 192.168.2.0 255.255.255.0 <Interface -> fastEthernet0/1>

\#(config) exit

\# show ip route

\# show run



Una vez ya teniendo esto ya solo es necesario mandar un ping y ver si las VPCS tienen la configuración de IP guardada
En la configuración de VPCS se tiene

\# ip <address>/<mask-bits> <gateway>

\# save

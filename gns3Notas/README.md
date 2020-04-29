# Resumen comandos y notas.

GNS3 es un software muy importante pues permite emular entornos y topologías de red en las cuales se puede desde comprender algunos principios de virtualización de servicios, hasta la creación de entornos cuya carga de trabajo a nivel de equipos puede realizarce de forma distribuida.

## Instalación ##

__En Distribuciones basadas en Debian__

$ sudo add-apt-repository ppa:gns3/ppa --yes

$ sudo apt update                                

$ sudo apt install gns3-gui gns3-server python3-pip python3-pyqt5 python3-pyqt5.qtsvg python3-pyqt5.qtwebsockets qemu qemu-kvm qemu-utils libvirt-clients libvirt-daemon-system virtinst wireshark xtightvncviewer apt-transport-https ca-certificates curl gnupg2 software-properties-common -y

$ sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys F88F6D313016330404F710FC9A2FD067A2E3EF7B

$ sudo apt-get update

$ sudo apt install dynamips ubridge

__En Distribuciones basadas en RedHat__

$ sudo dnf -y install git gcc cmake flex bison elfutils-libelf-devel libuuid-devel libpcap-devel python3-tornado python3-netifaces python3-devel python-pip python3-setuptools python3-PyQt4 python3-zmq wireshark --skip-broken

$ sudo dnf -y install gns3-server gns3-gui wireshark wireshark-qt qemu-kvm qemu-system-x86

$ sudo dnf -y copr enable athmane/gns3-extra

$ sudo dnf -y install vpcs dynamips


## Algunos hits de VPCS ##


En las VPCS contienen algunos comandos familiarizados a los comandos existentes en Linux

\\\> ? ; Este sirve para pedir ayuda en los comandos familiarizados con la VPCS

\\\> ip \<address\>/\<mask-bits\> \<gateway\> ; Sirve como \<parametros\> los cuales describen lo siguiente "address" es la dirección IP que se le asignara a la VPCS "mask-bits" es la mascara de subred que se le asigna para la creación de redes a nivel local, recordemos que esta mascara va 0 a 32 bits (dependiendo el número de host de la red), "gateway" es la puerta de enlace de datos que generalmente procede de la dirección que pertenece al router, en algunas ocasiones es la primer dirección y en algunas es la ultima dirección, dependiendo como sea la comodidad


## En Routers IOS ##

__Para configuración de las interfaces de red conectadas vamos a hacer uso de las siguientes líneas de código__

\\\# conf t

\\\#(config) int or interface \<Interface\#/\#\>

\\\#(conf-interface) ip address \<address\> \<netmask\>

\\\#(conf-interface) no shu

\\\#(conf-interface) exit

\\\#(config) exit

\\\# wr

__Para enrutamiento estático__

\\\# conf t

\\\#(config) ip route \<network\> \<netmask\> \<gateway\>

\\\#(config) exit

\\\# wr

___Forma 2:___

\\\#(config) ip route \<network\> \<netmask\> \<interface\>

\\\#(config) exit

\\\# wr

___Para enrutamiento con RIP_v2___

\\\# conf t

\\\#(config) router rip

\\\#(config-rou) version 2

\\\#(config-rou) network \<network\>

\\\#(config-rou) exit

\\\#(config) exit

\\\# wr


## Conexión vía emulación con entorno local (terminal virtual externa) ##

Para esta se añade un paquete con "tunctl" el cual nos permite crear interfaces virtuales el cual solo es instalarlo de acuerdo a su distribución

__Paso 1__

Crearemos la interfaz de red virtual

$ sudo tunctl -t tap0 -u $(whoami)

__Paso 2__

Encenderemos la interfaz de red virtual

$ sudo ip l s dev tap0 up

__Paso 3__

Añadiremos una ip para que podamos trabajar

$ sudo ip address add \<IP\> dev tap0

__Paso 4__

Añadiremos el enrutamiento a las distintas redes que pertenece esta maquina

$ sudo ip route add \<network\>/\<netmask\> via \<IP\> dev tap0

__Paso 5__

Añadir la nube de la interfaz de red "tap0" a GNS3 para trabajar con ella desde el exterior, de igual forma probar el ping desde la VPCS o desde la terminal de Linux hacia alguna VPCS

Para ver la tabla de enrutamiento:

$ route -n

Para eliminar la interfaz tap0 así como su tabla de enrutamiento:

$ sudo ip route flush dev tap0

$ sudo ip l d tap0

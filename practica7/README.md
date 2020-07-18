# Servidor DNS #

## Instalación Fedora ##

```bash
\# dnf -y install bind bind-utils
```

### Configuración del servicio ###

__Esto creara varios archivos y el servicio named por lo cual nosotros debemos configurar el archivo hasta las ultimas lineas__

___Ubicado en /etc/named.conf___

```
zone <nombre-de-la-zona-directa-o-inversa> {

  type <tipo-de-dns (master / slave)>;

  file <"el path donde va estar guardado el archivo de zona directa o inversa si solo esta el nombre de archivo el path es /var/named/ ">;

  /* Otras opciones en caso de ser el servidor poner lo siguiente */

  allow-transfer { <IP-a-la-del-servidor-secundario>};

};
```

__Tambien configurar el query de "listen-on port 53" y añadir un any; entre lo que tenga en las llaves asi como en "listen-on-v6" y "allow-query"__

### Configuración de las zonas a acceder del DNS ###
___Ir a los archivos que estaran ubicados en /var/named y crear los archivos con los que se asignaron al nombre del file de la zona directa o inversa___

```
$TTL 86400

@  IN  SOA <nombre-dominio>.  root.<nombre-dominio>. (

  2011071001  ;Serial

  3600        ;Refresh

  1800        ;Retry

  604800      ;Expire

  86400       ;Minimum TTL

)

; Nameserver zone

   IN  NS <servidor-o-nombre><nombre-domino>.

___ZONA DIRECTA___

; Se añaden cuantos zonas de servicio existan

<servidor-o-nombre><nombre-domino>.  IN A <IP-Nombre-de-servidor>

; En zona directa se añaden IP

<nombre-host> IN  A <IP-completa>

___ZONA INVERSA___

; En zona inversa se añaden PTR en el caso del nombre del servidor

<IP-completa-u-octetos-de-la-subred>  IN  PTR <servidor-o-nombre><nombre-domino>.

; Al igual que con las ip se añade lo siguiente

<IP-completa-u-octetos-de-la-subred>  IN  PTR <nombre-host>
```

###Check de la configuración y las zonas###

__Una vez concluido esto y guardado los archivos__

```bash
\# named-checkconf
```

Para verificar que la salida es correcta este comando no retorna nada

```bash
\# named-checkzone <nombre-de-la-zona-directa-o-inversa> /var/named/<archivo-de-zona-directa-o-inversa>
```

Este comando debe retornar un OK de la zona a verificar

###Configuración de firewall y habilitación de bind para DNS###

```bash
\# systemctl enable --now named

\# firewall-cmd --add-service=dns --permanent

\# firewall-cmd --reload
```

Una vez que se realizo esto podemos añadir nuestros servidores DNS al archivo /etc/resolv.conf

```bash
nameserver <IP-del-servidor>
```

para verificar podemos usar el comando

```bash
\# dig <nombre o host del dominio>
```

O

```bash
\# nslookup <nombre o host del dominio>
```

__Nota: cabe resaltar que esto es cuando ya se preconfiguro GNS3 con sus nombres de DNS y se habilito el ip dns server para que este logre redireccionar sus pings, dig's o nslookups al servidor correcto__

___En todo caso en el router ya una vez configurado todo lo que implica enrutamiento y asignación de IP's a sus interfaces se realiza:___

```bash
Router\# conf t

Router\#(config) ip name-server <IP-del-servidor-DNS>

Router\#(config) ip dns server

Router\#(config) ip domain-lookup

Router\#(config) exit

Router\# wr
```

## Instalación Debian ##

```bash
\# apt install bind9
```

### Configuración del servicio ###

__Esto creara varios archivos y el servicio bind9 por lo cual nosotros debemos configurar el archivo hasta las ultimas lineas__

___Ubicado en /etc/bind/named.conf.options___

Se puede comentar todo el archivo y poner lo siguente

```
options {

  directory "/var/cache/bind"

  recursion yes;

  allow-recursion { yes; };

  listen-on { any; };

  allow-transfer { none; };

};
```

___Ubicando ahora el archivo /etc/bind/named.conf.local___

Podemos añadir las zonas directas e inversas del secundario en el caso de como se realizo la practica

```
zone <nombre-de-la-zona-directa-o-inversa> {

  type slave;

  file <"nombre del archivo el path es /var/cache/ ">;

  /* Otras opciones en caso de ser el servidor poner lo siguiente /var/cache/bind/*/

  masters { <IP-del-servidor-primario>};

};
```

__Se verifica de igual forma que en Fedora y se habilita el servicio sin necesidad de ver su firewall__

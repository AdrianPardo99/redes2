### Servidor TFTP en Linux ###

## Instalación en Fedora ##

\$ sudo dnf install tftp-server tftp -y

__El servicio de TFTP en este sistema estan alojados en /usr/lib/systemd/system/ tftp.service and tftp.socket__

_Lo siguiente es_

\$ sudo cp /usr/lib/systemd/system/tftp.service /usr/lib/systemd/system/tftp-server.service

\$ sudo cp /usr/lib/systemd/system/tftp.socket usr/lib/systemd/system/tftp-server.socket

_En el archivo de tftp-server.service se modifica la linea ubicada en [Unit]_

<Requires> por

Requires=tftp-server.socket

_En [Service] se añaden banderas que permitan trabajar al servidor en el servicio estara prestablecido lo siguiente_

ExecStart=/usr/sbin/in.tftpd -s /var/lib/tftpboot

Cambiar por

ExecStart=/usr/sbin/in.tftpd -c -s -p /var/lib/tftpboot

# Las banderas explican #

  -c permite crear nuevos archivos

  -p Usado para no revisar permisos adicionales a los que ya le fueron asignados

  -s opcion recomendada para la seguridad, asi como compatibilidad con ROM de arranque que no se pueden incluir facilmente al incluir el nombre de directorio de su solicitud

_En la siguiente sección [Install] se añaden y se modifican lo siguiente:_

se añade

WantedBy=muti-user.target

_Y en_

Also=tftp.socket
se cambia por

Also=tftp-server.socket

__Seguido de esto guardamos el archivo y seguimos con lo siguiente__

\# systemctl daemon-reload

\# systemctl enable --now tftp-server

__Ahora cambiamos los permisos del directorio TFTP__

\# chmod 777 /var/lib/tftpboot

__Ahora para que el firewall permita el trafico de TFTP se realiza lo siguiente:__

\# firewall-cmd --add-service=tftp --perm

\# firewall-cmd --reload

# Ya con esto esta configura el servidor TFTP para trabajar con GNS3 #

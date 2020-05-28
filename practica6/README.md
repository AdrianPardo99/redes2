### Servidor TFTP en Linux ###

## Instalación en Fedora ##

\$ sudo dnf install tftp-server tftp -y

__El servicio de TFTP en este sistema estan alojados en /usr/lib/systemd/system/ tftp.service and tftp.socket__

___Lo siguiente es___

\$ sudo cp /usr/lib/systemd/system/tftp.service /usr/lib/systemd/system/tftp-server.service

\$ sudo cp /usr/lib/systemd/system/tftp.socket usr/lib/systemd/system/tftp-server.socket

___En el archivo de tftp-server.service se modifica la linea ubicada en [Unit]___

<Requires> por

Requires=tftp-server.socket

___En [Service] se añaden banderas que permitan trabajar al servidor en el servicio estara prestablecido lo siguiente___

ExecStart=/usr/sbin/in.tftpd -s /var/lib/tftpboot

Cambiar por

ExecStart=/usr/sbin/in.tftpd -c -s -p /var/lib/tftpboot

# Las banderas explican #

  -c permite crear nuevos archivos

  -p Usado para no revisar permisos adicionales a los que ya le fueron asignados

  -s opcion recomendada para la seguridad, asi como compatibilidad con ROM de arranque que no se pueden incluir facilmente al incluir el nombre de directorio de su solicitud

___En la siguiente sección [Install] se añaden y se modifican lo siguiente:___

se añade

WantedBy=muti-user.target

___Y en___

Also=tftp.socket
se cambia por

Also=tftp-server.socket

___Seguido de esto guardamos el archivo y seguimos con lo siguiente___

\# systemctl daemon-reload

\# systemctl enable --now tftp-server

___Ahora cambiamos los permisos del directorio TFTP___

\# chmod 777 /var/lib/tftpboot

___Ahora para que el firewall permita el trafico de TFTP se realiza lo siguiente:___

\# firewall-cmd --add-service=tftp --perm

\# firewall-cmd --reload

## Ya con esto esta configura el servidor TFTP para trabajar con GNS3 ##

### Servidor TFTP en Linux ###

Instalación en Fedora

\$ sudo dnf install tftp-server tftp -y

El servicio de TFTP en este sistema estan alojados en /usr/lib/systemd/system/ tftp.service and tftp.socket

Lo siguiente es

\$ sudo cp /usr/lib/systemd/system/tftp.service /usr/lib/systemd/system/tftp-server.service

\$ sudo cp /usr/lib/systemd/system/tftp.socket usr/lib/systemd/system/tftp-server.socket

En el archivo de tftp-server.service se modifica la linea ubicada en [Unit]

<Requires> por

Requires=tftp-server.socket

En [Service] se añaden banderas que permitan trabajar al servidor en el servicio estara prestablecido lo siguiente

ExecStart=/usr/sbin/in.tftpd -s /var/lib/tftpboot

Cambiar por

ExecStart=/usr/sbin/in.tftpd -c -s -p /var/lib/tftpboot

Las banderas explican
  -c permite crear nuevos archivos
  -p Usado para no revisar permisos adicionales a los que ya le fueron asignados
  -s opcion recomendada para la seguridad, asi como compatibilidad con ROM de arranque que no se pueden incluir facilmente al incluir el nombre de directorio de su solicitud

En la siguiente sección [Install] se añaden y se modifican lo siguiente:

se añade

WantedBy=muti-user.target

Y en

Also=tftp.socket
se cambia por

Also=tftp-server.socket

Seguido de esto guardamos el archivo y seguimos con lo siguiente

\# systemctl daemon-reload

\# systemctl enable --now tftp-server

Ahora cambiamos los permisos del directorio TFTP

\# chmod 777 /var/lib/tftpboot

Ahora para que el firewall permita el trafico de TFTP se realiza lo siguiente:

\# firewall-cmd --add-service=tftp --perm

\# firewall-cmd --reload

Ya con esto esta configura el servidor TFTP para trabajar con GNS3

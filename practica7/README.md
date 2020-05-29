# Servidor DNS #

## Instalación Fedora ##

\# dnf -y install bind bind-utils

__Esto creara varios archivos y el servicio named por lo cual nosotros debemos configurar el archivo hasta las ultimas lineas__

___Ubicado en /etc/named.conf___

zone \<nombre-de-la-zona-directa-o-inversa\> \{

  type \<tipo-de-dns \(master / slave\)\>\;

  file \<"el path donde va estar guardado el archivo de zona directa o inversa si solo esta el nombre de archivo el path es /var/named/ "\>;

  \/\* Otras opciones en caso de ser el servidor poner lo siguiente \*\/

  allow-transfer \{ \<IP-a-la-del-servidor-secundario\>\};

\}\;

___Ir a los archivos que estaran ubicados en /var/named y crear los archivos con los que se asignaron al nombre del file de la zona directa o inversa___



## Instalación Debian ##

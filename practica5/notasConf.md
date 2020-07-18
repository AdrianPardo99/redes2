# Para que esta madre jale chido y como le comence a mover

__En la terminal normal del router__

```bash
> debug ip rip

> conf t

> (config) int f<\#>/<\#>

> (config-int) ip rip v2-broadcast

> (config-int) exit

\#\# Repetir con ambas interfaces punto de int f<\#>/<\#>

> wr

> conf t

> (config) int f<\#>/<\#> \#\# De la interfaz donde pertene el servidor

> (config-int) ip helper-address <255.255.255.255> o <Direccion de broadcast en caso de que tu programa lo obtenga>

> (config-int) int f<\#>/<\#> \#\# De la interfaz donde pertene el cliente

> (config-int) ip broadcast-address <255.255.255.255> o <Direccion de broadcast en caso de que tu programa lo obtenga>

> (config-int) exit

> (config) ip forward-protocol udp

> (config) ip forward-protocol udp <port>

```

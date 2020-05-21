#!/usr/bin/expect
set ip [lindex $argv 0]
set port [lindex $argv 1]
set numRouter [lindex $argv 2]
set varRoute Router-
set var1 [concat $varRoute$numRouter]

set timeout 5
spawn telnet $ip $port
expect "'^]'."
send "\r"
expect $var1
send "\rcopy running-config tftp\r"
expect "?"
send "192.168.1.10\r"
expect "?"
send "\r"
sleep 1

#!/usr/bin/env bash
i=0
while [[ true ]]; do
  clear
  i=$(cat *.txt | wc -l)
  echo "Numero de caracteres en archivos: $i"
  echo -n "Palabras en 1.txt  "
  cat 1.txt | grep "consumiendo 1" | wc -l
  echo -n "Palabras en 2.txt  "
  cat 2.txt | grep "consumiendo 2" | wc -l
  echo -n "Palabras en 3.txt  "
  cat 3.txt | grep "consumiendo 3" | wc -l
  echo -n "Palabras en 4.txt  "
  cat 4.txt | grep "consumiendo 4" | wc -l
  echo -n "Palabras en 5.txt  "
  cat 5.txt | grep "consumiendo 5" | wc -l
  echo -n "Palabras en a.txt  "
  cat a.txt | grep "consumiendo a" | wc -l
  echo -n "Palabras en b.txt  "
  cat b.txt | grep "consumiendo b" | wc -l
  echo -n "Palabras en c.txt  "
  cat c.txt | grep "consumiendo c" | wc -l
  echo -n "Palabras en d.txt  "
  cat d.txt | grep "consumiendo d" | wc -l
  echo -n "Palabras en e.txt  "
  cat e.txt | grep "consumiendo e" | wc -l
  echo ""
  sleep 2
done

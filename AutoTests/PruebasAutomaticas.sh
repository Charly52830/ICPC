#!/bin/bash

echo "Introduce el numero de pruebas a correr"
read numPruebas

count=1
while [ "$count" -le $numPruebas ]
do
	./cases > Entrada.in
	cat Entrada.in | ./4 > Salida1.out
	cat Entrada.in | ./2 > Salida2.out
	if ! [ -z "$(diff Salida1.out Salida2.out)" ]
	then
		break
	fi
	echo $count
	count=$((count + 1))
done

if [ "$count" -le $numPruebas ]
then
	echo "Se encontro una prueba incorrecta"
else
	echo "$numPruebas pruebas dieron la misma respuesta"
fi


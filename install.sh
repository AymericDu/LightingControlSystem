#!/bin/bash

cd
if [ ! -d "cross-compiler" ];then
  mkdir cross-compiler
fi
cd cross-compiler
rm -rf smews rflpc gcc-arm-none-eabi-*

## GNU ARM Embedded Toolchain
echo "Téléchargement de GNU ARM Embedded Toolchain..."
wget https://launchpad.net/gcc-arm-embedded/5.0/5-2016-q3-update/+download/gcc-arm-none-eabi-5_4-2016q3-20160926-linux.tar.bz2
echo "Décompression de GNU ARM Embedded Toolchain..."
tar xjf ~/cross-compiler/gcc-arm-none-eabi-5_4-2016q3-20160926-linux.tar.bz2
echo "Ajout du chemin des exécutables de GNU ARM Embedded Toolchain à la variable PATH"
export PATH=$PATH:~/cross-compiler/gcc-arm-none-eabi-5_4-2016q3/bin

## Librairie RFLPC
echo "Téléchargement de RFLPC..."
git clone https://github.com/hauspie/rflpc
echo "Compilation de RFLPC..."
cd rflpc/; make; cd ..

## Smews
echo "Téléchargement de Smews..."
git clone https://github.com/2xs/smews.git
echo "Pré-compilation de Smews..."
cd smews; ./targets/mbed_ethernet/summon-rflpc

## Préparation d'une interface
if [ -z $1 ]
then
  echo "Aucune interface configurée"
else
  echo "Configuration de l'interface $1 à l'adresse 192.168.0.5/24"
  ## ip addr add 192.168.0.5/24 dev $1
  ## ip link set $1 up
  sudo ifconfig $1 192.168.0.5 netmask 255.255.255.0 up
fi

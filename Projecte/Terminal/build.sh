#!/bin/bash

if [ "$#" -eq 1 ]; then
  if [ "$1" == "clean" ]; then
    make clean
    exit 0
  fi
fi


make program.exe

if [ "$#" -lt 1 ]; then
  echo "USAGE: build.sh [contenidor | cataleg | terminal | ubicacio | all]"
  exit 0
fi

for ((i=1;i<=$#;i++));
do
  echo '=============' ${!i}' =================='
  if [ ${!i} == "contenidor" ]; then
    ./program.exe < jp_public/jp_public_contenidor.in > output_contenidor.out
    python3 check_result.py output_contenidor.out
  elif [ ${!i} == "cataleg" ]; then
    ./program.exe < jp_public/jp_public_cataleg.in > output_cataleg.out
    python3 check_result.py output_cataleg.out
  elif [ ${!i} == "terminal" ]; then
    ./program.exe < jp_public/jp_public_terminal.in > output_terminal.out
    python3 check_result.py output_terminal.out
  elif [ ${!i} == "ubicacio" ]; then
    ./program.exe < jp_public/jp_public_ubicacio.in > output_ubicacio.out
    python3 check_result.py output_ubicacio.out
  elif [ ${!i} == "all" ]; then
    rm output_all.res
    ./program.exe < jp_public/jp_public.in > output_all.res
    diff output_all.res jp_public/jp_public.res
  elif [ ${!i} == "clean" ]; then
    make clean
  else
    echo ${!i} "no es un parametre valid."
    echo "Els parametres acceptats son [contenidor | cataleg | terminal | ubicacio | all]"
    echo
  fi
done;






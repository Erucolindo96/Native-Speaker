#!/usr/bin/env bash



function recognition()
{
  local model1=$1
  local modelUbm=$2
  local sample_dir=$3
  local threshold=$4

  echo $model1
  echo $modelUbm
  echo $sample_dir
  echo $threshold

  for file in $sample_dir/*
  do
    echo $file

    ./main -r models/ $model1 $modelUbm $threshold $file 
    echo "----------------------------------------------" 
    echo "----------------------------------------------" 	
	
  done
}



prog=$1	

models=("ferus-bez-ciszy" "janFigat-bez-ciszy" "kasprzak-bez-ciszy" "maksymFigat-bez-ciszy") 

model_dirs=("probki/ferus/rozpoznawanie" "probki/janFigat/rozpoznawanie" "probki/kasprzak/rozpoznawanie" "probki/maksymFigat/rozpoznawanie")

ubms=("ubm-bez-ciszy-bez-rozpoznawania" "ubm-bez-ciszy-bez-uczacych-rozpoznawanych")

models_zgodne=(0 0 0 0)
models_niezgodne=(0 0 0 0)

ferus=0
jan=1
kasprzak=2
maksym=3
models_cnt=4


for ubm in ${ubms[0]} ${ubms[1]} 
do

  echo "UBM równy $ubm  "
  for i in {0..3}
  do
    echo "Próbki zgodne"
    recognition ${models[i]} $ubm ${model_dirs[i]} $prog
    echo "Próbki niezgodne"
	recognition ${models[i]} $ubm ${model_dirs[(i+1)%$models_cnt]} $prog
	echo "#############################################################"
	echo "#############################################################"

 
  done
  echo "*****************************************************"
  echo "*****************************************************"
done








#!/usr/bin/env bash



function recognition()
{
  local model1=$1
  local modelUbm=$2
  local sample_dir=$3
  local threshold=$4

#  echo $model1
#  echo $modelUbm
#  echo $sample_dir
#  echo $threshold

  local succes_sum=0

  for file in $sample_dir/*
  do
    echo $file

    ./main -r models/ $model1 $modelUbm $threshold $file
    succes_sum=$(($succes_sum+$?))
    echo "----------------------------------------------" 
    echo "----------------------------------------------" 	
	
  done
  echo "pozytywne weryfikacje: $succes_sum"   
  return $succes_sum     
}


function test_models()
{

local prog=$1	
local ubm=$2

local models=("ferus-bez-ciszy" "janFigat-bez-ciszy" "kasprzak-bez-ciszy" "maksymFigat-bez-ciszy") 

local model_dirs=("probki/ferus/rozpoznawanie" "probki/janFigat/rozpoznawanie" "probki/kasprzak/rozpoznawanie" "probki/maksymFigat/rozpoznawanie")

#ubms=("ubm-bez-ciszy-bez-rozpoznawania" "ubm-bez-ciszy-bez-uczacych-rozpoznawanych")

local sample_cnt=20

local models_zgodne=(0 0 0 0)
local models_niezgodne=($sample_cnt $sample_cnt $sample_cnt $sample_cnt)

#local ferus=0
#local jan=1
#local kasprzak=2
#local maksym=3
local models_cnt=4

for i in {0..3}
  do
    echo "Próbki zgodne"
    recognition ${models[i]} $ubm ${model_dirs[i]} $prog
    models_zgodne[$i]=$(($?))
	echo "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"    
	echo "Próbki niezgodne"

	for j in {1..3} #robimy weryfikacje dla wszystkich folderów próbek poza próbkami naszego modelu(test próbek niezgodnych)
	do
	  recognition ${models[i]} $ubm ${model_dirs[(i+j)%$models_cnt]} $prog
	  models_niezgodne[$i]=$((${models_niezgodne[$i]}+$?))
	  echo "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
	done    

	echo "#############################################################" 
done

echo "*****************************************************"


echo "Prób rozpoznawania wynosił: $prog" >> test-model-result.txt
echo "Używany model UBM: $ubm" >> test-model-result.txt
echo "Weryfikacji dla próbek zgodnych jest $sample_cnt" >> test-model-result.txt
echo "Zaś dla niezgodnych jest $(($sample_cnt*3))" >> test-model-result.txt

for i in {0..3}
  do
    echo "Model ${models[$i]} uzyskał ${models_zgodne[$i]} pozytywnych weryfikacji dla próbek zgodnych" >> test-model-result.txt
    echo "oraz ${models_niezgodne[$i]} pozytywnych weryfikacji dla próbek niezgodnych" >> test-model-result.txt
    echo "próbki niezgodne należą do modelu ${models[(i+1)%$models_cnt]}" >> test-model-result.txt
done

}

#base_thr=0.1
ubm=$1

for thr in 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1
do

echo "Próg == $thr"
test_models $thr $ubm 

done








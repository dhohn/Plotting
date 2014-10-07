#!/bin/bash


PCHANNEL=$1

if [ $# -eq 0 ]
then echo "Please enter the file name."
exit
fi

#merge_lhe.exe ${PCHANNEL}_0.lhe ${PCHANNEL}_1.lhe
merge_lhe.exe 1${PCHANNEL}.lhe 2${PCHANNEL}.lhe
#mv -f out.lhe tmp.lhe && rm ${PCHANNEL}_{0,1}.lhe
mv -f out.lhe tmp.lhe && rm {1,2}${PCHANNEL}.lhe


for i in 3 4 5 6 7 8 9 10
do
  ii=i+1
  FILE1=tmp.lhe
  #FILE2=${PCHANNEL}_$i.lhe
  FILE2=$i${PCHANNEL}.lhe
#$((i+1))
  merge_lhe.exe $FILE1 $FILE2
  #echo $FILE2
  mv -f out.lhe tmp.lhe && rm ${FILE2}
done

mv -f tmp.lhe ${PCHANNEL}.lhe
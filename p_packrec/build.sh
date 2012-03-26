#!/usr/bin
 echo 1. build:  gcc -o packrec  -ggdb3  packrec.cpp Rect.cpp -lstdc++
time  gcc -o packrec  -ggdb3  packrec.cpp  Rect.cpp  -lstdc++ -lm
 #./packrec ./packrec.in  | tee ./packrec.out
 
  echo 2. genenrate input file
time  ./packrec -g -n 10 | awk ' BEGIN {FS=":"} /RECT_CORXY/ { print $2 }' | tee  packrec.in
  echo 3. running and output:
  ./packrec -n 10 | tee output.trc
  echo 4. get results by awk:
  cat output.trc | awk ' BEGIN {FS=":"} /PACK_RECT_RESULT/ { print $2 }' | tee packrec.out
  cat output.trc | awk ' BEGIN {FS=":"} /PACK_RECT_XY/ { print $2 }' | uniq | sort -g | tee -a  packrec.out
  echo 5. result checking:
  echo
  echo
  echo ____________packrec_in___________________
  cat packrec.in 
  echo _________________________________________
  echo _____________packrec_out_________________
  cat packrec.out
  echo _________________________________________
echo `date` Good nigth and enjoy programming. 

#!/usr/bin/env bash

set -e

LIST_NOT_ALLOWED="taobao hello"

for keyword in $LIST_NOT_ALLOWED
do
  echo "\nstart finding keyword "$keyword"..."
  found=`grep $keyword -R --exclude-dir "node_modules" --color --exclude="*.sh" ./`
  found_lines=0
  for l in $found
  do
    found_lines=$(($found_lines+1))
  done
  if [ $found_lines \> 0 ];
  then
    echo "and found $found_lines match, THIS IS NOT ALLOWED!!!\n"
    exit 1
  else
    echo "and found nothing, well done!"
  fi
done

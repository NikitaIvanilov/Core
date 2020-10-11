#!/bin/bash

# This script was created to work with ponymix.
# Source code: github.com/falconindy/ponymix

# Check null argument
if [[ $# == 0 ]]; then

  echo "Usage: $(echo $0 | cut -f2 -d "/") [operation] <step>"
  exit 1

fi

# Check operation argument
if [[ $1 == '!' ]]; then

  ponymix --sink toggle
  exit 1

elif [[ $1 != '+' && $1 != '-' ]]; then

  echo "Bad operation!"
  exit 1

fi

# Setup variables
volume=$(ponymix --sink get-volume)
operation=$1
step=5

# Check custom step
if [[ $# == 2 ]]; then

  temp=$(echo $2 | tr -cd "[0-9]")

  if [[ $temp != "" ]]; then

    step=$temp

  fi

  unset temp

fi

# Count result
result=$(expr "$volume" "$operation" "$step")

# Set new volume
ponymix --sink set-volume $result
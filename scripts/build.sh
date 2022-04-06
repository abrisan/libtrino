#!/bin/bash

BASE_DIR=$1

if [ ! -d "$BASE_DIR/build" ]
then
  mkdir $BASE_DIR/build
fi

cd $BASE_DIR/build || exit 1
cmake ..
make || exit 1

echo "Waiting for trino"

until curl trino:8080/v1/info/state
do
  echo "Still waiting..."
  sleep 2
done

echo "Trino is up. Running tests"

tests/libtrino_tests

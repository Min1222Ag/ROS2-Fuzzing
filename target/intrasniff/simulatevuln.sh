#!/bin/sh

ros2 run secretserver secretserver

ros2 run secretserver dbinteract <<< "1 10 2 0 1 10 3 0 8 2 0 5"

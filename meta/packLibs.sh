#!/bin/bash

#################################################
function packLib()
{
    echo -e "\nCopy dependencies for ${1}"
    deps=$(ldd $1 | awk 'BEGIN{ORS=" "}$1 ~/^\//{print $1}$3~/^\//{print $3}' | sed 's/,$/\n/')

    #Check if the paths are vaild
    [[ ! -e $1 ]] && echo "Not a vaild input $1" && exit 1
    [[ -d $2 ]] || echo -e "No such directory $2" && mkdir -pv "$2"

    #Copy the deps
    for dep in $deps
    do
        cp -v "$dep" "$2"
    done
}

#################################################
if [ -z $1 ]; then
    echo "usage: $0 <prefix>"
    exit 1
fi

packLib $1/usr/lib/libguh.so $1/usr/lib/
packLib $1/usr/bin/guhd $1/usr/lib/

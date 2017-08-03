#! /bin/sh

home_app=~/app

home_utah=${home_app}/utah

./configure --prefix=${home_utah}

if test -d ${home_utah}; then
    rm -rf ${home_utah}
fi

make install

make distclean

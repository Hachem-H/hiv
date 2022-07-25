#!/usr/bin/env sh

cc=gcc
cc_flags=-Iinclude

bin_dir=bin
src_dir=testing


mkdir -p bin

for file in `ls -1 $src_dir`
do
    outfile=$bin_dir/$(echo $file | rev | cut -c3- | rev)
    srcfile=$src_dir/$file

    $cc -o $outfile $srcfile $cc_flags
    echo "[CC] $srcfile -> $outfile"
done

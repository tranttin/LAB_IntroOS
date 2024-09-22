#!/bin/bash

#reading data from the user
read -p 'Enter file name : ' FileName

if [ -e $FileName ]
then
    echo File Exist
else
    echo File doesnot exist
fi

if [ -s $FileName ]
then
    echo The given file is not empty.
else
    echo The given file is empty.
fi

if [ -r $FileName ]
then
    echo The given file has read access.
else
    echo The given file does not has read access.
fi

if [ -w $FileName ]
then
    echo The given file has write access.
else
    echo The given file does not has write access.
fi

if [ -x $FileName ]
then
    echo The given file has execute access.
else
    echo The given file does not has execute access.
fi

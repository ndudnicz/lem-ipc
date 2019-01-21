#! /bin/sh
ipcrm -M $1
ipcrm -Q $1
ipcrm -S $1

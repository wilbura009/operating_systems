#!/usr/bin/env bash
# The following is used with assign3
#
# Print a help Msg
if [[ $# -lt 1 ]]; then
    echo "USAGE: $0 <file>"
    exit 0
fi
targetHash=c95b27848ae8d4354d87678d075001f7
myHash=($(md5sum $1))
echo ${targetHash[0]}; echo ${myHash[0]}
diff -s <(echo ${targetHash[0]}) <(echo ${myHash[0]})

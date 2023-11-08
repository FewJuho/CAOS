#!/User/bin/env

function find_header() {
    grep -E "\#include <" | sed -En 's/.*#include <(.*)>/\1/p'
}
IFS=":"
while read name
do
    result="---"
    for mpath in $MANPATH
    do
        path="$mpath/man3/$str.3"
        if [-f "$path"]
        then
            result=`cat $path | find_header`
            break
        fi
        if [-f "$path"]
                then
                    result=`gunzip -cd "$path.gz" | find_header`
                    break
        fi
    done
    echo $result
done

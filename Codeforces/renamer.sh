for moo in `ls`; do
    if [ -d $moo ]; then
        cd $moo
        for hundreds in `ls`; do
            cd $hundreds
            echo $hundreds
            for tens in `ls`; do
                for problem in `ls`; do
                    if [ "${problem:4:1}" = "_" ]; then
                        mv $problem ${problem:0:4}${problem:5:1}".cpp"
                    fi
                    if [ "${problem:3:1}" = "_" ]; then
                        mv $problem ${problem:0:3}${problem:4:1}".cpp"
                    fi
                    if [ "${problem:2:1}" = "_" ]; then
                        mv $problem ${problem:0:2}${problem:3:1}".cpp"
                    fi
                done
            done
            cd ..
        done
        cd ..
    fi
    # while IFS= read -r line; do
    # if [ "${line:4:1}" = "_" ]; then
    #     # Remove the 5th character
    #     modified="${line:0:4}${line:5}"
    # else
    #     # Leave line unchanged
    #     modified="$line"
    # fi
    # echo "$modified"
    # done
done
for moo in `ls`; do
    if [ -d $moo ]; then
        cd $moo
        for hundreds in `ls`; do
            cd $hundreds
            echo $hundreds
            for tens in `ls`; do
                if [ -d $tens ]; then
                    cd $tens
                    for contest in `ls`; do
                        if [ -d $contest ]; then
                            cd $contest
                            echo $contest
                            for problem in `ls`; do
                                if [ "${problem:1:1}" = "_" ]; then
                                    mv $problem $contest${problem:0:1}".cpp"
                                fi
                                if [ "${problem:4:1}" = "_" ]; then
                                    mv $problem $contest${problem:5:1}".cpp"
                                fi
                            done
                            cd ..
                        fi
                    done
                    cd ..
                fi
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
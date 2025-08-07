g++-15 -std=c++23 generator.cpp -o generator
g++-15 -std=c++23 correct.cpp -o correct
g++-15 -std=c++23 incorrect.cpp -o incorrect

for i in `seq 1 1000`; do
    ./generator

    echo "===== Test Case $i ====="

    ./incorrect
    incorrect_exit=$?
    ./correct
    correct_exit=$?

    if [ $correct_exit == 0 ] && [ $incorrect_exit == 0 ] && 
       diff -q "incorrect.out" "correct.out" > /dev/null; then
        continue
    else
        echo "Fuck"
        break
    fi

done;
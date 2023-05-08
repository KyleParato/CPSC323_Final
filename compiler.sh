# Kyle Parato - compiler.sh
# Shell Script to run project
# Uses ubunto linux and g++, to run file,
# make sure cmp323.out(compiled main.cpp, compiler.hpp, compiler.cpp)
# and finalp.cpp is in the same directory as this shell script
./cmp323.out
echo -n "Run file? (y/n): "
read response
if [ $response = "y" ]; then
    echo""
    g++ -c finalp.cpp -o finalp.o
    g++ -o finalp.out finalp.o
    ./finalp.out
    echo ""

    echo -n "Clear File? (y/n): "
    read response
    if [ $response = "y" ]; then
        truncate -s 0 finalp.cpp
    fi
fi
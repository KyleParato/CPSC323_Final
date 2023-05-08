# Kyle Parato - 323FinalBuild.sh
# Shell script to compile project and run
# Uses ubunto linux and g++, to run file,
# make sure main.cpp, compiler.hpp, compiler.cpp and 
# finalp.cpp is in the same directory as this shell script
echo "Removing .o and .out files"
rm *.o
rm *.out
echo ""

g++ -c compiler.cpp -o compiler.o
g++ -c main.cpp -o main.o
g++ -o cmp323.out main.o compiler.o
./cmp323.out

echo -n "Compile file? (y/n): "
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
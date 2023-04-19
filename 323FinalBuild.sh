echo "Removing .o and .out files"
rm *.o
rm *.out
echo ""

g++ -c compiler.cpp -o compiler.o
g++ -c main.cpp -o main.o

g++ -o cmp323.out main.o compiler.o
./cmp323.out

g++ -c finalp.cpp -o finalp.o
g++ -o finalp.out finalp.o
./finalp.out


echo -n "Clear File (y/n): "
read response
if [ $response = "y" ]; then
    truncate -s 0 finalp.cpp
fi
#include "Huffman.cpp"

int main(int argc, char const *argv[])
{
    try
    {
        Huffman h;
        h.compressTofile("hello.png","file2.txt");
        h.decompressToFile("file2.txt","hello2.png");
    }
    catch(const std::logic_error& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}
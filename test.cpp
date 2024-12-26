#include "Huffman.cpp"

int main(int argc, char const *argv[])
{
    try
    {
        Huffman h;
        h.compressTofile("file.txt","file2.txt");
        h.decompressToFile("file2.txt","file3.txt");
    }
    catch(const std::logic_error& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}
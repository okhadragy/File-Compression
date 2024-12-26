#include <iostream>
#include "linkedlist.h"
#include <windows.h>
#include <fstream>
#include "Huffman.cpp"

using namespace std;

void encode(string files[], int &size)
{
    Huffman h;
    ofstream mega("mega.txt", ios::out);
    if (!mega.is_open())
        throw runtime_error("Error opening files!");
    for (int i = 0; i < size; i++)
    { // concatenate all files
        ifstream temp(files[i]);
        if (!temp.is_open())
            throw runtime_error("Error opening files!");
        mega << temp.rdbuf();
        temp.close();
    }
    mega.close();
    h.compressTofile("mega.txt", "encodedmega.txt");
}

void decode(string encoded, string files[], int size)
{
    Huffman h;
    h.decompressToFile(encoded, "decodedmega.txt");
    ifstream decfile("decodedmega.txt", ios::binary);
    if (!decfile.is_open())
        throw runtime_error("Error opening files!");
    int counter = 0;
    int fin = 0;
    for (int i = 0; i < size; i++)
    {
        counter++;
        ofstream currfile(files[i]);
        if (!currfile.is_open())
            throw runtime_error("Error opening files!");
        char c;
        while (decfile.get(c))
        {
            if (c != EOF)
                currfile << c;
            else
            {
                if (size == counter)
                    fin = 1;
                break;
            }
        }
        currfile.close();
        if (fin)
            break;
    }
    decfile.close();
}

void iterateDirectory(string path, string files[], int &numOfFiles)
{
    string searchpath = path + "\\*";
    WIN32_FIND_DATAA filedata;
    HANDLE hfind = FindFirstFileA(searchpath.c_str(), &filedata);
    do
    {
        if (string(filedata.cFileName) == "." || string(filedata.cFileName) == "..")
            continue;
        if (filedata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            iterateDirectory(path + "\\" + filedata.cFileName, files, numOfFiles);
        else
            files[numOfFiles++] = path + "\\" + filedata.cFileName;
    } while (FindNextFileA(hfind, &filedata));
    FindClose(hfind);
}

int main()
{
    string path;
    cin >> path;
    int numOfFiles = 0;
    string files[100];
    DWORD attributes = GetFileAttributesA(path.c_str());
    if (attributes == INVALID_FILE_ATTRIBUTES)
        throw std::logic_error("Path doesn't exist!");
    else if (attributes & FILE_ATTRIBUTE_DIRECTORY)
    {
        iterateDirectory(path, files, numOfFiles);
    }
    else
    {
        files[0] = path;
        numOfFiles++;
    }
    encode(files, numOfFiles);
    decode("encodedmega.txt", files, numOfFiles);
}

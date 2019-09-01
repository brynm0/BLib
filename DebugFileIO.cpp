/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Bryn Murrell $
   ======================================================================== */

#include <iostream>
#include <fstream>
#include <vector>
flocal void*
readEntireFileBinary(char* path)
{
    void* result;
    FILE* file = fopen(path, "rb");
    if (file)
    {
        fseek(file, 0, SEEK_END);
        size_t fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);
        result = (char*)malloc(fileSize);
        fread(result, fileSize, 1, file);
        fclose(file);
    }
    return result;
}

flocal char*
readEntireFileText(char* path)
{
    char* result = 0;
    FILE* file = fopen(path, "rb");
    if (file)
    {
        fseek(file, 0, SEEK_END);
        size_t fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);
        result = (char*)malloc(fileSize + 1);
        fread(result, fileSize, 1, file);
        result[fileSize] = 0;
        fclose(file);
    }
    return result;
}

//DEBUG
flocal void concatenateStrings(i64 sourceACount, char* sourceA,
                               i64 sourceBCount, char* sourceB,
                               char* dest)
{
    
    for (i64 index = 0; index < sourceACount; ++index)
    {
        *dest++ = *sourceA++;
    }
    for (i64 index = 0; index < sourceBCount; ++index)
    {
        *dest++ = *sourceB++;
    }
    *dest++ = 0;
}

flocal int
stringLen(char* string)
{
    int ctr = 0;
    for (char* scan = string; *scan; ++scan)
    {
        ++ctr;
    }
    return ctr;
}

flocal std::vector<char> readFile(const std::string& filename)
{
	std::ifstream file(filename, std::ios::ate | std::ios::binary);
	if (!file.is_open())
	{
		printf("Failed to open file %s\n", filename.c_str());
		// TODO(bryn): Logging
	}
    
	int fileSize = file.tellg();
    file.seekg(0);

	std::vector<char> buffer(fileSize);
	file.read(buffer.data(), fileSize);


	file.close();
	return buffer;
}

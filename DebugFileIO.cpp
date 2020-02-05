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
read_entire_file_binary(char* path, u64* num_bytes)
{
    void* result;
    FILE* file = fopen(path, "rb");
    if (file)
    {
        fseek(file, 0, SEEK_END);
        size_t file_size = ftell(file);
        if (num_bytes) {*num_bytes = file_size;}
        fseek(file, 0, SEEK_SET);
        result = (char*)malloc(file_size);
        fread(result, file_size, 1, file);
        fclose(file);
    }
    return result;
}

flocal void*
read_entire_file_binary(FILE* f, u64* num_bytes)
{
    void* result;
    if (f)
    {
        fseek(f, 0, SEEK_END);
        size_t file_size = ftell(f);
        if (num_bytes) {*num_bytes = file_size;}
        fseek(f, 0, SEEK_SET);
        result = (char*)malloc(file_size);
        fread(result, file_size, 1, f);
    }
    return result;
}

flocal char*
read_entire_file_text(char* path, u64* ret)
{
    char* result = 0;
    FILE* file = fopen(path, "rb");
    u64 fs;
    if (file)
    {
        fseek(file, 0, SEEK_END);
        fs = ftell(file);
        fseek(file, 0, SEEK_SET);
        result = (char*)malloc(fs + 1);
        fread(result, fs, 1, file);
        result[fs] = 0;
        fclose(file);
    }
    if (ret) { *ret = fs; }
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
#if 0 
flocal std::vector<char> read_file(const std::string& filename)
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
#endif

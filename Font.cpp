/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Bryn Murrell $
   ======================================================================== */

#include "Font.h"
#include <sstream>
#include <iterator>

flocal u32
numFromToken(std::string inStr)
{
    u32 pos = inStr.find("=");
    std::string tok1 = inStr.substr(pos+1);
    return atoi((char*)tok1.c_str());
}

flocal void
arrayFromToken(std::string inStr, u32 count, u32* ret)
{
    u32 pos = inStr.find("=");
    std::string tok1 = inStr.substr(pos);
    for (u32 i = 0; i < count; i++)
    {
        ret[i] = tok1[1 + 2 * i] - '0';
    }
}

flocal char
charFromToken(std::string inStr, char out)
{

    u32 pos = inStr.find("=");
    std::string tok1 = inStr.substr(pos);
    char* tokC = (char*)tok1.c_str();
    return tokC[2];
    
}

flocal void
stringFromToken(std::string inStr, char* out)
{
    
    u32 pos = inStr.find("=");
    std::string tok1 = inStr.substr(pos + 2);
    
    out = strncpy(out, (char*)tok1.c_str(), tok1.length() - 1);
}

//TODO(bryn): -BUG- Since the file may not write EOF, final line may not be null terminated,
//Thus junk will be written to the final kerning.
//TODO(bryn): -BUG- Strings contained within the file cannot contain spaces.
flocal Font
loadFontFile(char* filename)
{
    Font out = {};
    std::vector<char> v = readFile(filename);
    std::string file = v.data();
    std::istringstream iss(file);
    std::string line;
    while(std::getline(iss, line))
    {
            
        std::istringstream lIterator(line);
        std::vector<std::string> results(std::istream_iterator<std::string>{lIterator},
                                         std::istream_iterator<std::string>());
        if (results[0] == "info")
        {
            if (results.size() != 12)
            {
                u32 i = 0;
                while(true)
                {
                    if (results[i].substr(0, 4) != "size")
                    {
                        ++i;
                    }
                    else
                    {
                        break;
                    }
                }
                
                for (i; i < results.size(); i++)
                {   
                    u32 pos = results[i].find("=");
                    std::string s = results[i].substr(0, pos);
                    if (s=="size")
                    {
                        out.size = numFromToken(results[i]);
                        
                    }
                    else if (s=="bold")
                    {
                        out.bold = numFromToken(results[i]);
                        
                    }
                    else if (s=="italic")
                    {
                        out.italic = numFromToken(results[i]);
                        
                    }
                    else if (s=="charset")
                    {
                        out.charset = 0;
                        
                    }
                    else if (s=="unicode")
                    {
                        out.unicode = numFromToken(results[i]);
                        
                    }
                    else if (s=="stretchH")
                    {
                            out.stretchHeight = numFromToken(results[i]);
                            
                    }
                    else if (s=="smooth")
                    {
                        out.smooth = numFromToken(results[i]);
                        
                    }
                    else if (s == "aa")
                    {
                        out.ssLevel = numFromToken(results[i]);
                        
                    }
                    else if (s == "padding")
                    {
                        arrayFromToken(results[i], 4, out.padding);
                        
                    }
                    else if (s == "spacing")
                    {
                        arrayFromToken(results[i], 2, out.spacing);   
                    }
                }
            }
            else
            {
                
                for (u32 i = 0; i < results.size(); i++)
                {
                    
                    switch(i)
                    {
                        case 2 :
                            out.size = numFromToken(results[i]);
                        case 3 :
                            out.bold = numFromToken(results[i]);
                            break;
                        case 4 :
                            out.italic = numFromToken(results[i]);
                            break;
                        case 5 :
                            out.charset = 0;
                            break;
                        case 6 :
                            out.unicode = numFromToken(results[i]);
                            break;
                        case 7 :
                            out.stretchHeight = numFromToken(results[i]);
                            break;
                        case 8 :
                            out.smooth = numFromToken(results[i]);
                            break;
                        case 9 :
                            out.ssLevel = numFromToken(results[i]);
                            break;
                        case 10 :
                            arrayFromToken(results[i], 4, out.padding);
                            break;
                        case 11 :
                            arrayFromToken(results[i], 2, out.spacing);
                            break;
                    }
                }
            }
        }
        else if (results[0] == "common")
        {
            for (int i = 1; i < results.size(); i++)
            {
                switch(i)
                {
                    case 1 :
                        out.lineHeight = numFromToken(results[i]);
                        break;
                    case 2 :
                        out.base = numFromToken(results[i]);
                        break;
                    case 3 :
                        out.scaleW = numFromToken(results[i]);
                        break;
                    case 4 :
                        out.scaleH = numFromToken(results[i]);
                        break;
                    case 6 :
                        out.packed = numFromToken(results[i]);
                        break;
                }
            }
        }
        else if (results[0] == "page")
        {

            for (int i = 1; i < results.size(); i++)
            {
                switch(i)
                {
                    case 1 :
                        out.page.id = numFromToken(results[i]);
                        break;
                    case 2 :
                        stringFromToken(results[i], out.page.path);
                        break;
                }
            }
            
        }
        else if (results[0] == "char")
        {
            if (results.size() != 2)
            {
                Character c = {};
                for (int i = 0; i < results.size(); i++)
                {
                    switch(i)
                    {
                        case 1 :
                            c.id = numFromToken(results[i]);
                            break;
                        case 2 :
                            c.x = numFromToken(results[i]);
                            break;
                        case 3 :
                            c.y = numFromToken(results[i]);
                            break;
                        case 4 :
                            c.width = numFromToken(results[i]);
                            break;
                        case 5 :
                            c.height = numFromToken(results[i]);
                            break;
                        case 6 :
                            c.xOffset = numFromToken(results[i]);
                            break;
                        case 7 :
                            c.yOffset = numFromToken(results[i]);
                            break;
                        case 8 :
                            c.xAdvance = numFromToken(results[i]);
                            break;
                        case 9:
                            c.page = numFromToken(results[i]);
                            break;
                        case 10 :
                            c.channel = numFromToken(results[i]);
                            break;
                        case 11 :
                            if (results.size() != i+1)
                            {
                                std::string s = results[i] + results[i+1];
                                stringFromToken(s, &c.letter);
                            }
                            else
                            {
                                stringFromToken(results[i], &c.letter);
                            }
                            
                            break;
                    }
                }
                out.ids.insert({c.letter, c.id});
                out.characters.insert({c.id, c});
            }
        }
        else if (results[0] == "kerning")
        {
            Kerning k = {};
            for (int i = 0; i < results.size(); i++)
            {
                switch(i)
                {
                    case 1:
                        k.idFirst = numFromToken(results[i]);
                        break; 
                    case 2:
                        k.idSecond = numFromToken(results[i]);
                        break; 
                    case 3:
                        i32 num = numFromToken(results[i]);
                        k.amount = num;
                        break; 
                }
            }
            out.characters.at(k.idFirst).kernings.insert({k.idSecond,k});
        }
    }

    return out;
}

flocal TypeFace getTypeFace(char name[])
{
    char path[] = "W:\\Fonts\\";
    char buf[256];
    concatenateStrings(stringLen(path), path,
                       stringLen(name), name,
                       buf);
    char fntPath[256];
    char fnt[] = ".fnt";
    concatenateStrings(stringLen(buf), buf,
                       stringLen(fnt), fnt,
                       fntPath);
    TypeFace t = {};
    t.font = loadFontFile(fntPath);

    char infoPath[256];
    char info[] = ".info";
    concatenateStrings(stringLen(buf), buf,
                       stringLen(info), info,
                       infoPath);
    
    FILE* f = fopen(infoPath, "r");
    char bfr[512];
    fgets(bfr, 512, f);
    t.info = {};
    t.info.characterCount = atoi(bfr);
    for (int i = 0; i < t.info.characterCount; i++)
    {
        fgets(&bfr[0], 512, f);
        char delim[] = " ";
        u32 a = atoi(strtok(bfr, delim));
        u32 b = atoi(strtok(NULL, delim));
        t.info.charVertexMap.insert({a, b});
    }
#if 0 
    char obj[] = ".obj";
    concatenateStrings(stringLen(buf), buf,
                       stringLen(obj), obj,
                       t.objPath);
    char png[] = ".png";
    concatenateStrings(stringLen(buf), buf,
                       stringLen(png), png,
                       t.pngPath);
#endif
    return t;
}

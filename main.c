#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <byteswap.h>

struct IffHeader {
    char identifier[4];
    int fileSize;
    char fileType[4];
};

struct SegmentHeader {
    char segmentType[4];
    int segmentByteCount;
};

int swapEndian(int number)
{
   int byte0, byte1, byte2, byte3;
   byte0 = (number & 0x000000FF) >> 0;
   byte1 = (number & 0x0000FF00) >> 8;
   byte2 = (number & 0x00FF0000) >> 16;
   byte3 = (number & 0xFF000000) >> 24;
   return ((byte0<<24) | (byte1 << 16) | (byte2 << 8) | (byte3 << 0));
}

int main() {
    // printf() displays the string inside quotation
    // /Users/briankotos/Downloads/IMG_4899.jpg
    FILE *stream;
    stream = fopen("/Users/briankotos/Projects/mine/cbin/JimTopia.sc2", "rb");

    struct IffHeader city;

    

    fread(&city, sizeof(struct IffHeader), 1, stream);
    // fread(&nameSegmentHeader, sizeof(struct SegmentHeader), 1, stream);

    printf("CITY: %s %d %s \n", city.identifier, city.fileSize, city.fileType);

    printf("\n\n");
    for (int i = 0; i < 2; i++) {
        struct SegmentHeader nameSegmentHeader;
        fread(&nameSegmentHeader, sizeof(struct SegmentHeader), 1, stream);

        // gets red as a little endian int, but it's actually big endian
        nameSegmentHeader.segmentByteCount = swapEndian(nameSegmentHeader.segmentByteCount);


        printf("Read segment '%s' containing %d bytes\n", nameSegmentHeader.segmentType, nameSegmentHeader.segmentByteCount);

        if (strcmp(nameSegmentHeader.segmentType, "CNAM ") == 0) {
            char cityName[nameSegmentHeader.segmentByteCount];
            fread(&cityName, sizeof(cityName), 1, stream);
            printf("City name: '%s'\n", cityName);
        } else if (strcmp(nameSegmentHeader.segmentType, "MISC") == 0) {
            printf("MISC\n");
        }
        // printf("%#010x\n\n", nameSegmentHeader.segmentType);

        // nameSegmentHeader = (struct SegmentHeader){ 0 };
        memset(&nameSegmentHeader, 0, sizeof(nameSegmentHeader));

        printf("\n\n");
    }
    // printf("NAME: %s %d \n\n", nameSegmentHeader.segmentType, nameSegmentHeader.segmentByteCount);


    // printf("%#010x\n\n", nameSegmentHeader.segmentByteCount);

    //int32_t buffer;
    // unsigned long int buffer;
    // int count = fread(&buffer, sizeof(long), sizeof(long), stream);
    fclose(stream);

    printf("Hello, World!\n");
    // printf("yo '%zu' dude", buffer);
    return 0;
}

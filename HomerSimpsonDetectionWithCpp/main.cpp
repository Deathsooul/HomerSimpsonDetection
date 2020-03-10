#include <stdio.h>
#include <stdlib.h>

unsigned char* ReadBMP(char* filename)
{
    int i;
    int cont=0;
    FILE* f = fopen(filename, "rb");

    if(f == NULL)
        throw "Argument Exception";

    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

    int width = *(int*)&info[18];
    int height = *(int*)&info[22];

    printf("Name: %s\n", filename);
//    printf("Width: %d\n", width);
//    printf("Height: %d\n", height);

    int row_padded = (width*3 + 3) & (~3);
    unsigned char* data = new unsigned char[row_padded];
    unsigned char tmp;

    for(int i = 0; i < height; i++)
    {
        fread(data, sizeof(unsigned char), row_padded, f);
        for(int j = 0; j < width*3; j += 3)
        {
            // Convert (B, G, R) to (R, G, B)
            tmp = data[j];
            data[j] = data[j+2];
            data[j+2] = tmp;
            if( ((int)data[j] < 200 && (int)data[j] > 180 ) && ((int)data[j+1] < 178 && (int)data[j+1] > 158) && ((int)data[j+2] < 121 && (int)data[j+2] > 101))
            {
                cont++;
            }
            //printf("R: %d - G: %d - B: %d\n", (int)data[j], (int)data[j+1], (int)data[j+2]);
        }
    }
    if(cont > 1){
        printf("Imagem COM Homer!\n");
    } else {
        printf("Imagem SEM Homer!\n");
    }

    fclose(f);
    return data;
}


int main(int argc, char *argv[]) {

    int i=0;
    char str[500];
    for(i=1;i<=58;i++) {
//		printf("%d\n", i);
        sprintf(str, "/home/wallace/Documentos/Faculdade/2020/InteligenciaArtificial/Aula1/HomerSimpsonDetection/HomerSimpsonDetectionWithCpp/imagens/%d.bmp", i);
        ReadBMP(str);
    }

    return 0;
}
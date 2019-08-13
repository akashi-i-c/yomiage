//2018/7/16時点で、リニアPCMのみ対応する予定

#include <stdio.h>
#include <stdlib.h>

int main(){
    int i=0;
    unsigned long before_size = 0;
    unsigned char *input;
    unsigned char *tmp;
    unsigned long output_size=0;
    unsigned char *output_data;
    int path_size = 1;
    unsigned char *filename;

    filename = (unsigned char *)malloc(sizeof(unsigned char)*1);
    if(filename == NULL){
        printf("error\n");
        exit(1);
    }else{
    }
    /*パス指定*/
    printf("Please input data-path.\n");
    printf("-> ");
    for(int flug = 0;flug != 1;path_size++){
            if(path_size < 1){
                tmp = (unsigned char *)realloc(filename,sizeof(unsigned char)*path_size);
                if(tmp == NULL){
                    printf("error 10\n");
                    free(filename);
                    exit(1);
                }else{
                }
                filename = tmp;
            }else{
            }
            filename[path_size - 1] = getchar();
            if(filename[path_size - 1] == '\n'){
                filename[path_size - 1] = '\0';
                flug = 1;
                break;
            }else{
            }

    }
    printf("data-path : %s\n",filename);
    /*ファイル名入力*/
    input = (unsigned char *)malloc(sizeof(unsigned char)*2);
    if(input == NULL){
        printf("error1\n");
        exit(1);
    }else{
    }
    printf("ready\n");
    for(int flug = 0;flug != 1;i++){
        if(i>=1){
            tmp = (unsigned char *)realloc(input,sizeof(unsigned char)*(i+2));
            if(tmp == NULL){
                printf("error2\n");
                free(filename);
                exit(1);
            }else{
            }
            input = tmp;
        }else{
        }
        input[i] = getchar();

        if(input[i] == '\n'){
            input[i] = '\0';
            flug = 1;
        }else{
        }
    }
    printf("%s\n",input);
    printf("%d\n",i-1);
        /*ファイル読み込み・データチャンクコピー*/
    int mozisu = i-1;
    unsigned char output[4];
    unsigned char channels[2];
    unsigned char sample_rate[4];
    unsigned char bps[4];
    unsigned char data_set[2];
    unsigned char data_bit[2];
    unsigned int data_size = 0;
    unsigned char buff;

    for(i = 0;i < mozisu;i = i+2){
        output[0] = input[i];
        output[1] = input[i+1];
        if(input[i+3] == 0xa1 || input[i+3] == 0xa5 || input[i+3] == 0xe1 || input[i+3] == 0xe3 || input[i+3] == 0xe5){
            output[2] = input[i+2];
            output[3] = input[i+3];
            i += 2;
            filename[path_size - 1] = '\\';
            filename[path_size] = output[0];
            filename[path_size + 1] = output[1];
            filename[path_size + 2] = output[2];
            filename[path_size + 3] = output[3];
            filename[path_size + 4] = '.';
            filename[path_size + 5] = 'w';
            filename[path_size + 6] = 'a';
            filename[path_size + 7] = 'v';
            filename[path_size + 8] = '\0';
        }else{
            filename[path_size - 1] = '\\';
            filename[path_size] = output[0];
            filename[path_size + 1] = output[1];
            filename[path_size + 2] = '.';
            filename[path_size + 3] = 'w';
            filename[path_size + 4] = 'a';
            filename[path_size + 5] = 'v';
            filename[path_size + 6] = '\0';
        }
        FILE *size_s;
        printf("%s:",filename);
        size_s = fopen(filename,"rb");
        if(size_s == NULL){
            printf("\nfile loading error\n");
            free(input);
            free(filename);
            exit(1);
        }else{
        }
        fseek(size_s,40,SEEK_SET);
        fread(&data_size,sizeof(unsigned int),1,size_s);
        printf("%d byte\n",data_size);
        output_size += data_size;
    }

    output_data = (unsigned char *)malloc(sizeof(unsigned char)*output_size + 44);
    if(output_data == NULL){
        printf("error3\n");
        free(input);
        free(filename);
        exit(1);
    }else{
    }
    printf("prepared size:%d\n",output_size + 44);

    int first_flag = 0;
    unsigned long copy = 44;
    for(i = 0;i < mozisu;i = i+2){
        output[0] = input[i];
        output[1] = input[i+1];
        if(input[i+3] == 0xa1 || input[i+3] == 0xa5 || input[i+3] == 0xe1 || input[i+3] == 0xe3 || input[i+3] == 0xe5){
            output[2] = input[i+2];
            output[3] = input[i+3];
            i += 2;
            filename[path_size - 1] = '\\';
            filename[path_size] = output[0];
            filename[path_size + 1] = output[1];
            filename[path_size + 2] = output[2];
            filename[path_size + 3] = output[3];
            filename[path_size + 4] = '.';
            filename[path_size + 5] = 'w';
            filename[path_size + 6] = 'a';
            filename[path_size + 7] = 'v';
            filename[path_size + 8] = '\0';
        }else{
            filename[path_size - 1] = '\\';
            filename[path_size] = output[0];
            filename[path_size + 1] = output[1];
            filename[path_size + 2] = '.';
            filename[path_size + 3] = 'w';
            filename[path_size + 4] = 'a';
            filename[path_size + 5] = 'v';
            filename[path_size + 6] = '\0';
        }
        FILE *Rwav;
        printf("%s\n",filename);
        Rwav = fopen(filename,"rb");
        if(Rwav == NULL){
            printf("file loading error\n");
            free(input);
            free(filename);
            exit(1);
        }else{
        }
        printf("__file loading successful__\n");
        if(first_flag == 0){
            fseek(Rwav,22,SEEK_CUR);
            fread(channels,sizeof(unsigned char),2,Rwav);
            printf("channel:%d%d\n",channels[0],channels[1]);
            fread(sample_rate,sizeof(unsigned char),4,Rwav);
            printf("sampling rate:%d%d%d%d\n",sample_rate[0],sample_rate[1],sample_rate[2],sample_rate[3]);
            fread(bps,sizeof(unsigned char),4,Rwav);
            printf("BPS:%d%d%d%d\n",bps[0],bps[1],bps[2],bps[3]);
            fread(data_set,sizeof(unsigned char),2,Rwav);
            printf("data align:%d%d\n",data_set[0],data_set[1]);
            fread(data_bit,sizeof(unsigned char),2,Rwav);
            printf("bit depth:%d%d\n",data_bit[0],data_bit[1]);
            printf("-------------------------------------------------\n");
            first_flag = 1;
        }else{
        }

        fseek(Rwav,40,SEEK_SET);
        int test = 1;
        test = fread(&data_size,sizeof(unsigned int),1,Rwav);
        if(test == 0){
            printf("error4.1\n");
            free(input);
            free(filename);
            free(output_data);
            fclose(Rwav);
            exit(1);
        }

        for(int Ccount = 0;Ccount < data_size;Ccount++){
            fread(&buff,sizeof(unsigned char),1,Rwav);
            output_data[copy] = buff;
            copy++;
        }
        fclose(Rwav);
        printf("%d character\n",i);
    }
    /*ファイル名作成*/
    unsigned char *wavname;
    wavname = (unsigned char *)malloc(sizeof(unsigned char)*(mozisu + 5));
    if(wavname == NULL){
        printf("error5\n");
        free(input);
        free(filename);
        free(output_data);
        exit(1);
    }else{
    }
    for(i = 0;i <= mozisu;i++){
        wavname[i] = input[i];
    }
    wavname[mozisu] = '.';
    wavname[mozisu + 1] = 'w';
    wavname[mozisu + 2] = 'a';
    wavname[mozisu + 3] = 'v';
    wavname[mozisu + 4] = '\0';
    printf("%s\n",wavname);
    unsigned char *W_address;
    unsigned char W_path[] = {'C',':','\\','U','s','e','r','s','\\','s','s','s','k','a','i','\\','M','u','s','i','c','\\','d','a','t','a','\\','O','U','T','P','U','T','\\'};
    W_address = (unsigned char *)malloc(sizeof(unsigned char)*(mozisu + 39));
    if(W_address == NULL){
        printf("error6\n");
        free(input);
        free(filename);
        free(output_data);
        exit(1);
    }else{
    }
    for(i = 0;i < 34;i++){
        W_address[i] = W_path[i];
    }
    for(i = 0;i < mozisu + 5;i++){
        W_address[i+34] = wavname[i];
    }
    printf("%s\n",W_address);
    /*ヘッダ作成*/
    unsigned char header[44];
    header[0] = 'R';
    header[1] = 'I';
    header[2] = 'F';
    header[3] = 'F';
    output_size += 44;
    header[4] = output_size << 24 & 0xff;
    header[5] = output_size << 16 & 0xff;
    header[6] = output_size << 8 & 0xff;
    header[7] = output_size << 0 & 0xff;
    header[8] = 'W';
    header[9] = 'A';
    header[10] = 'V';
    header[11] = 'E';
    header[12] = 'f';
    header[13] = 'm';
    header[14] = 't';
    header[15] = ' ';
    header[16] = 16;
    header[17] = 0;
    header[18] = 0;
    header[19] = 0;
    header[20] = 1;
    header[21] = 0;
    header[22] = channels[0];
    header[23] = channels[1];
    header[24] = sample_rate[0];
    header[25] = sample_rate[1];
    header[26] = sample_rate[2];
    header[27] = sample_rate[3];
    header[28] = bps[0];
    header[29] = bps[1];
    header[30] = bps[2];
    header[31] = bps[3];
    header[32] = data_set[0];
    header[33] = data_set[1];
    header[34] = data_bit[0];
    header[35] = data_bit[1];
    header[36] = 'd';
    header[37] = 'a';
    header[38] = 't';
    header[39] = 'a';
    unsigned int  out_data_size = output_size - 44;
    header[40] = out_data_size << 24 & 0xff;
    header[41] = out_data_size << 16 & 0xff;
    header[42] = out_data_size << 8 & 0xff;
    header[43] = out_data_size << 0 & 0xff;

    /*ファイル書き出し*/
    FILE *Wwav;
    Wwav = fopen(W_address,"wb");
    if(Wwav == NULL){
        printf("file making error\n");
        free(input);
        free(filename);
        free(output_data);
        free(wavname);
        free(W_address);
        fclose(Wwav);
        exit(1);
    }else{
    }
    printf("__file making successful__\n");
    fwrite(header,sizeof(header),1,Wwav);
    fwrite(output_data,sizeof(unsigned char),output_size,Wwav);
    fclose(Wwav);
    printf("output data size:%d\n",output_size);
    printf("finish\n");
    free(input);
    free(filename);
    free(output_data);
    free(wavname);
    free(W_address);
    return 0;
}
#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  
  
#define IMG_SIZE                (16*1024)  
#define HEADER_SIZE             16  
#define BLKSIZE                 512  
  
int main (int argc, char *argv[])  
{  
    FILE            *fp;  
    unsigned        char *Buf;  
    int             BufLen;  
    int             nbytes, fileLen;  
    unsigned int    checksum, count;  
    int             i;  
  
    if (argc != 3)  
    {  
        printf("Usage: %s <source file> <destination file>\n", argv[0]);  
        return -1;  
    }  
  
    /* 分配16K的buffer */  
    BufLen = IMG_SIZE;  
    Buf = malloc(BufLen);  
    if (!Buf)  
    {  
        perror("Alloc buffer failed!");  
        return -1;  
    }  
    memset(Buf, 0x00, BufLen);  
  
    /* 读源bin到buffer */  
    fp = fopen(argv[1], "rb");  
    if( fp == NULL)  
    {  
        perror("source file open error");  
        free(Buf);  
        return -1;  
    }  
    /* 获取源bin长度 */  
    fseek(fp, 0L, SEEK_END);  
    fileLen = ftell(fp);  
    fseek(fp, 0L, SEEK_SET);  
  
    /* 源bin长度不得超过16K-16byte */  
    fileLen = (fileLen < (IMG_SIZE - HEADER_SIZE)) ? fileLen : (IMG_SIZE - HEADER_SIZE);  
  
    /* 读源bin到buffer[16] */  
    nbytes = fread(Buf + HEADER_SIZE, 1, fileLen, fp);  
    if (nbytes != fileLen)  
    {  
        perror("source file read error\n");  
        free(Buf);  
        fclose(fp);  
        return -1;  
    }  
    fclose(fp);  
      
    /* 计算校验和 */  
    for(i = 0, checksum = 0; i < fileLen; i++)  
        checksum += Buf[HEADER_SIZE + i];  
  
    /* 计算BL1的大小: 
    ** BL1的大小包括BL1的头信息 
    ** 另外iROM从SD卡拷贝是按块拷贝的，因此这里需要调整大小为512字节的整数倍 
    */  
    fileLen += HEADER_SIZE;  
    count = fileLen / BLKSIZE * BLKSIZE;  
    if (count < fileLen)  
        count += BLKSIZE;  
    memcpy(Buf, &count, 4);     // 保存BL1的大小到Buf[0-3]  
  
    // 将校验和保存在buffer[8~15]  
    memcpy(Buf + 8, &checksum, 4);  
  
    fp = fopen(argv[2], "wb");  
    if (fp == NULL)  
    {  
        perror("destination file open error");  
        free(Buf);  
        return -1;  
    }  
    // 将count + HEADER_SIZE字节的buffer拷贝到目的bin中  
    nbytes  = fwrite(Buf, 1, IMG_SIZE, fp);  
    if (nbytes != IMG_SIZE)  
    {  
        perror("destination file write error");  
        free(Buf);  
        fclose(fp);  
        return -1;  
    }  
  
    free(Buf);  
    fclose(fp);  
  
    return 0;  
}  

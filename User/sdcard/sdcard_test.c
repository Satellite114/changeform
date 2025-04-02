#include "sdcard_test.h"

FRESULT  MyFile_Res; // 文件操作结果
//	函数：FatFs_Check
//	功能：进行FatFs文件系统的挂载
//
void FatFs_Check(void) // 判断FatFs是否挂载成功，若没有创建FatFs则格式化SD卡
{
	BYTE work[_MAX_SS];

	FATFS_LinkDriver(&SD_Driver, SDPath);	  // 初始化驱动
	MyFile_Res = f_mount(&SDFatFS, (const TCHAR*) SDPath, 1); //	挂载SD卡

	if (MyFile_Res == FR_OK) // 判断是否挂载成功
			{
		//f_setlabel("UFO");
		printf("\r successed to mount SD\r\n");
	} else {
		printf("SD卡还未创建文件系统，即将格式化\r\n");

		MyFile_Res = f_mkfs("0:", FM_FAT32, 0, work, sizeof work); // 格式化SD卡，FAT32，簇默认大小16K

		if (MyFile_Res == FR_OK) // 判断是否格式化成功
			printf("SD卡格式化成功！\r\n");
		else
			printf("格式化失败，请检查或更换SD卡！\r\n");
	}
}
//	函数：FatFs_GetVolume
//	功能：计算设备的容量，包括总容量和剩余容量
//
void FatFs_GetVolume(void) // 计算设备容量
{
	FATFS *fs;							 // 定义结构体指针
	uint32_t SD_CardCapacity = 0;		 // SD卡的总容量
	uint32_t SD_FreeCapacity = 0;		 // SD卡空闲容量
	DWORD fre_clust, fre_sect, tot_sect; // 空闲簇，空闲扇区数，总扇区数

	f_getfree((const TCHAR*) SDPath, &fre_clust, &fs); // 获取SD卡剩余的簇

	tot_sect = (fs->n_fatent - 2) * fs->csize; // 总扇区数量 = 总的簇 * 每个簇包含的扇区数
	fre_sect = fre_clust * fs->csize;		   // 计算剩余的可用扇区数

	SD_CardCapacity = tot_sect / 2048; // SD卡总容量 = 总扇区数 * 512( 每扇区的字节数 ) / 1048576(换算成MB)
	SD_FreeCapacity = fre_sect / 2048; // 计算剩余的容量，单位为M
	printf("-------------------获取设备容量信息-----------------\r\n");
	printf("SD容量：%ldMB\r\n", SD_CardCapacity);
	printf("SD剩余：%ldMB\r\n", SD_FreeCapacity);
}

//	函数：FatFs_FileTest
//	功能：进行文件写入和读取测试
//
uint8_t FatFs_FileTest(void) // 文件创建和写入测试
{
	uint8_t i = 0;
	uint16_t BufferSize = 0;
	FIL MyFile;												   // 文件对象
	UINT MyFile_Num;										   //	数据长度
	BYTE MyFile_WriteBuffer[] = "STM32H7B0 SD卡 文件系统测试"; // 要写入的数据
	BYTE MyFile_ReadBuffer[1024];							   // 要读出的数据

	printf("-------------FatFs 文件创建和写入测试---------------\r\n");

	MyFile_Res = f_open(&MyFile, "0:test/Test.txt",
	FA_CREATE_ALWAYS | FA_WRITE); // 打开文件，若不存在则创建该文件
	if (MyFile_Res == FR_OK) {
		printf("文件打开/创建成功，准备写入数据...\r\n");

		MyFile_Res = f_write(&MyFile, MyFile_WriteBuffer,
				sizeof(MyFile_WriteBuffer), &MyFile_Num); // 向文件写入数据
		if (MyFile_Res == FR_OK) {
			printf("写入成功，写入内容为：\r\n");
			printf("%s\r\n", MyFile_WriteBuffer);
		} else {
			printf("文件写入失败，请检查SD卡或重新格式化!\r\n");
			f_close(&MyFile); // 关闭文件
			return ERROR;
		}
		f_close(&MyFile); // 关闭文件
	} else {
		printf("无法打开/创建文件，请检查SD卡或重新格式化!\r\n");
		f_close(&MyFile); // 关闭文件
		return ERROR;
	}

	printf("-------------FatFs 文件读取测试---------------\r\n");

	BufferSize = sizeof(MyFile_WriteBuffer) / sizeof(BYTE); // 计算写入的数据长度
	MyFile_Res = f_open(&MyFile, "0:test/Test.txt",
	FA_OPEN_EXISTING | FA_READ);						  // 打开文件，若不存在则创建该文件
	MyFile_Res = f_read(&MyFile, MyFile_ReadBuffer, BufferSize, &MyFile_Num); // 读取文件
	if (MyFile_Res == FR_OK) {
		printf("文件读取成功，正在校验数据...\r\n");

		for (i = 0; i < BufferSize; i++) {
			if (MyFile_WriteBuffer[i] != MyFile_ReadBuffer[i]) // 校验数据
					{
				printf("校验失败，请检查SD卡或重新格式化!\r\n");
				f_close(&MyFile); // 关闭文件
				return ERROR;
			}
		}
		printf("校验成功，读出的数据为：\r\n");
		printf("%s\r\n", MyFile_ReadBuffer);
	} else {
		printf("无法读取文件，请检查SD卡或重新格式化!\r\n");
		f_close(&MyFile); // 关闭文件
		return ERROR;
	}

	f_close(&MyFile); // 关闭文件
	return SUCCESS;
}

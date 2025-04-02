#include "screenshot.h"
#include "ff.h"
#include "lvgl.h"
#include "gui_guider.h"
ALIGN_32BYTES(uint8_t snapshot_buf[800000])
__attribute__((section(".SDRAM")));
char cwd[256]; // 用于保存当前路径
FRESULT fr;
extern uint16_t sd_count;

static lv_img_dsc_t snapshot_dsc; // 需保持全局有效
static lv_img_dsc_t load_img_dsc;
uint8_t take_snapshot_with_buffer(lv_obj_t *obj, const char *filename)
{
    // 计算所需的缓冲区大小
    uint32_t buf_size = lv_snapshot_buf_size_needed(obj, LV_IMG_CF_TRUE_COLOR_ALPHA);

    if (buf_size > sizeof(snapshot_buf))
    {
        LV_LOG_USER("error : %s size: %d", buf_size, sizeof(snapshot_buf));
        return SNAPSHOT_FAILED;
    }

    // 生成快照
    if (lv_snapshot_take_to_buf(obj, LV_IMG_CF_TRUE_COLOR_ALPHA, &snapshot_dsc, snapshot_buf, buf_size) != LV_RES_OK)
    {
        LV_LOG_USER("fail to take snapshot");
        return SNAPSHOT_FAILED;
    }

    // 将快照数据存储到 SD 卡
    return save_snapshot_to_sd(filename, snapshot_buf, buf_size);
}

uint8_t save_snapshot_to_sd(const char *filename, uint8_t *buf, uint32_t size)
{
    FIL file; // 文件对象
    UINT bytes_written;
    FRESULT res;

    // 1. 打开/创建文件
    res = f_open(&file, filename, FA_CREATE_ALWAYS | FA_WRITE);

    if (res != FR_OK)
    {
        LV_LOG_USER("SD failed: %d", res);
        return SNAPSHOT_FAILED;
    }
    if (buf == NULL || size == 0)
    {
        LV_LOG_USER("error");
        return SNAPSHOT_FAILED;
    }

    // 2. 写入数据
    res = f_write(&file, buf, size, &bytes_written);
    if (res != FR_OK || bytes_written != size)
    {
        LV_LOG_USER("SD failed: %d", res);
        f_close(&file);
        return SNAPSHOT_FAILED;
    }

    // 3. 关闭文件
    f_close(&file);
    LV_LOG_USER("successed %d to %s", bytes_written, filename);
    return SNAPSHOT_SUCCESS;
}

uint8_t load_image_from_sd(const char *filename)
{
    FIL file;
    UINT bytes_read;
    FRESULT res;

    // 打开文件
    res = f_open(&file, filename, FA_READ);
    if (res != FR_OK)
    {
        LV_LOG_USER("SD failed: %d", res);
        return 0;
    }

    // 读取文件
    res = f_read(&file, snapshot_buf, sizeof(snapshot_buf), &bytes_read);
    if (res != FR_OK || bytes_read == 0)
    {
        LV_LOG_USER("SD failed: %d", res);
        f_close(&file);
        return 0;
    }

    // 关闭文件
    f_close(&file);
    LV_LOG_USER("successed read %d ", bytes_read);
    return 1;
}
uint8_t refersh_lvgl_image(lv_obj_t *img)
{
    load_img_dsc.header.always_zero = 0;
    load_img_dsc.header.w = 600; // 图片宽度（根据图片实际尺寸调整）
    load_img_dsc.header.h = 420; // 图片高度（根据图片实际尺寸调整）
    load_img_dsc.header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA;
    load_img_dsc.data_size = sizeof(snapshot_buf); // 图片数据大小
    load_img_dsc.data = snapshot_buf;              // 指向图片数据
    lv_img_set_src(img, &load_img_dsc);
    LV_LOG_USER("successed to create image descriptor!\r\n");
    return 1;
}
uint8_t GetFileCount(const char *path)
{
    FATFS fs;
    FILINFO fno;
    DIR dir;
    FRESULT res;
    uint16_t file_count = 0;
    // fr = f_getcwd(cwd, sizeof(cwd));
    // if (fr != FR_OK)
    // {
    //     // 错误处理
    //     LV_LOG_USER("\33Error getting current directory.\n");
    //     return -1;
    // }

    // // 打印当前路径
    // LV_LOG_USER("Current directory: %s\n", cwd);
    // 初始化文件计数
    // 打开目录
    res = f_opendir(&dir, path);
    if (res != FR_OK)
    {
        LV_LOG_USER("Failed to open directory: %s, Error: %d\n", path, res);
        f_closedir(&dir);  // 补充关闭操作
        return -1; // 失败
    }

    // 遍历目录
    while (1)
    {
        res = f_readdir(&dir, &fno); // 读取目录项
        if (res != FR_OK || fno.fname[0] == 0)

            break; // 读取出错或到达目录末尾

        if (!(fno.fattrib & AM_DIR))
        { // 排除子目录
            file_count++;
            LV_LOG_USER("file number: %d,name:%s\r\n", file_count, fno.fname);
        }
    }

    // 关闭目录
    f_closedir(&dir);
    // fr = f_getcwd(cwd, sizeof(cwd));
    // if (fr != FR_OK)
    // {
    //     // 错误处理
    //     LV_LOG_USER("\33Error getting current directory.\n");
    //     return -1;
    // }

    // // 打印当前路径
    // LV_LOG_USER("Current directory: %s\n", cwd);
    // sd_count=file_count;
    // LV_LOG_USER("sd_count: %d\n", sd_count);
    return file_count-1; // 成功
}
uint8_t OpenFileByIndex(const char *path, uint16_t index)
{

    // fr = f_getcwd(cwd, sizeof(cwd));
    // if (fr != FR_OK)
    // {
    //     // 错误处理
    //     LV_LOG_USER("\33Error getting current directory.\n");
    //     return -1;
    // }



    FATFS fs;
    FILINFO fno;
    FRESULT res;
    uint16_t current_index = 0;
    // 2. 打开目录
    DIR dir;
    res = f_opendir(&dir, path);
    if (res != FR_OK)
    {
        LV_LOG_USER("filed to open dir: %d", res);
        f_closedir(&dir);  // 补充关闭操作
        return 0;
    }
    FIL file;
    // 3. 遍历目录找到第 index 个文件
    while (1)
    {
        res = f_readdir(&dir, &fno);
        if (res != FR_OK || fno.fname[0] == 0)
        {
            LV_LOG_USER("could not read dir. res:%d",res);
            f_closedir(&dir);
            return 0;
        }

        // 排除子目录，仅统计文件
        if (!(fno.fattrib & AM_DIR))
        {
            if (current_index == index)
            {
                // 4. 打开目标文件
                char filepath[128];
                snprintf(filepath, sizeof(filepath), "%s/%s", path, fno.fname);
                lv_label_set_text_fmt(guider_ui.wave_model_label_27, "IMAGE:%s,  %d/%d", fno.fname,index,sd_count);
                LV_LOG_USER("openning: %s\r\n", filepath);
                res = f_open(&file, filepath, FA_READ);
                if (res == FR_OK)
                {
                    LV_LOG_USER("successed to open number %d file: %s\r\n", index, fno.fname);
                    UINT bytes_read;
                    res = f_read(&file, snapshot_buf, sizeof(snapshot_buf), &bytes_read);
                    if (res != FR_OK || bytes_read == 0)
                    {
                        LV_LOG_USER("SD failed: %d", res);
                        f_close(&file);
                        return 0;// 读取失败
                    }
                    f_close(&file);

                    f_closedir(&dir);
                    return 1;
                }
                else
                {
                    LV_LOG_USER("fileed to open number %d file,%d", index,res);
                    f_closedir(&dir);
                    return 0;
                }
            }
            current_index++;
        }
    }

    // 5. 关闭目录
    f_closedir(&dir);

    // fr = f_getcwd(cwd, sizeof(cwd));
    // if (fr != FR_OK)
    // {
    //     // 错误处理
    //     LV_LOG_USER("\033Error getting current directory.\n");
    //     return -1;
    // }

    return 0;
}

uint8_t DeleteFileByIndex(const char *path, uint16_t index)
{
    FATFS fs;
    FILINFO fno;
    FRESULT res;
    DIR dir;
    uint16_t current_index = 0;

    // 打开目录
    res = f_opendir(&dir, path);
    if (res != FR_OK)
    {
        LV_LOG_USER("Failed to open directory: %s, Error: %d\n", path, res);
        return 0;
    }

    // 查找指定索引对应的文件
    while (1)
    {
        res = f_readdir(&dir, &fno);
        if (res != FR_OK || fno.fname[0] == 0)
        {
            LV_LOG_USER("Could not read directory. Res: %d", res);
            f_closedir(&dir);
            return 0;
        }

        // 排除子目录，仅删除文件
        if (!(fno.fattrib & AM_DIR))
        {
            if (current_index == index)
            {
                // 拼接文件路径
                char filepath[128];
                snprintf(filepath, sizeof(filepath), "%s/%s", path, fno.fname);

                // 执行删除操作
                res = f_unlink(filepath);
                if (res == FR_OK)
                {
                    LV_LOG_USER("Successfully deleted file: %s", filepath);
                    f_closedir(&dir);
                    return 1;
                }
                else
                {
                    LV_LOG_USER("Failed to delete file: %s, Error: %d", filepath, res);
                    f_closedir(&dir);
                    return 0;
                }
            }
            current_index++;
        }
    }

    // 关闭目录
    f_closedir(&dir);
    return 0;
}



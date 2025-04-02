#ifndef __SCREENSHOT_H__
#define __SCREENSHOT_H__
#include "lvgl.h"
#include "sdram.h"
#include "lv_snapshot.h"
#include "ff.h"
#define SNAPSHOT_SUCCESS  1  // 成功
#define SNAPSHOT_FAILED   0  // 失败




uint8_t take_snapshot_with_buffer(lv_obj_t *obj, const char *filename);
uint8_t save_snapshot_to_sd(const char *filename, uint8_t *buf, uint32_t size);
uint8_t refersh_lvgl_image(lv_obj_t * obj);
uint8_t load_image_from_sd(const char *filename);
uint8_t GetFileCount(const char *path);
uint8_t OpenFileByIndex(const char *path, uint16_t index);
uint8_t DeleteFileByIndex(const char *path, uint16_t index);

#endif
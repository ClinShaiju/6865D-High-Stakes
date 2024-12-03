#include "main.h"

typedef  FILE* pc_file_t;

static void* fs_open(lv_fs_drv_t * drv, const char * path, lv_fs_mode_t mode)
{
    errno = 0;
    const char * flags = "";
    if(mode == LV_FS_MODE_WR) flags = "wb";
    else if(mode == LV_FS_MODE_RD) flags = "rb";
    else if(mode == (LV_FS_MODE_WR | LV_FS_MODE_RD)) flags = "a+";

    void* f = fopen(path, flags);

    return f;
}

static lv_fs_res_t fs_close(lv_fs_drv_t * drv, void * file_p)
{
    pc_file_t * fp = (pc_file_t *)file_p;
    fclose(*fp);
    return LV_FS_RES_OK;
}

static lv_fs_res_t fs_read(lv_fs_drv_t * drv, void * file_p, void * buf, uint32_t btr, uint32_t * br)
{
    pc_file_t * fp =  (pc_file_t *)file_p;
    *br = fread(buf, 1, btr, *fp);
    return LV_FS_RES_OK;
}

static lv_fs_res_t fs_seek(lv_fs_drv_t * drv, void * file_p, uint32_t pos, lv_fs_whence_t whence)
{
    pc_file_t * fp = (pc_file_t *)file_p;
    fseek(*fp, pos, SEEK_SET);
    
    return LV_FS_RES_OK;
}

static lv_fs_res_t fs_tell(lv_fs_drv_t * drv, void * file_p, uint32_t * pos_p)
{
    pc_file_t * fp =  (pc_file_t *)file_p;
    *pos_p = ftell(*fp);
    return LV_FS_RES_OK;
}

void test2() {
    static lv_fs_drv_t drv;                   /*Needs to be static or global*/
    lv_fs_drv_init(&drv);                     /*Basic initialization*/

    drv.letter = 'S';                         /*An uppercase letter to identify the drive */
    drv.cache_size = 0;           /*Cache size for reading in bytes. 0 to not cache.*/

    drv.ready_cb = NULL;               /*Callback to tell if the drive is ready to use */
    drv.open_cb = fs_open;                 /*Callback to open a file */
    drv.close_cb = fs_close;               /*Callback to close a file */
    drv.read_cb = fs_read;                 /*Callback to read a file */
    drv.write_cb = NULL;               /*Callback to write a file */
    drv.seek_cb = fs_seek;                 /*Callback to seek in a file (Move cursor) */
    drv.tell_cb = fs_tell;                 /*Callback to tell the cursor position  */

    drv.dir_open_cb = NULL;         /*Callback to open directory to read its content */
    drv.dir_read_cb = NULL;         /*Callback to read a directory's content */
    drv.dir_close_cb = NULL;       /*Callback to close a directory */

    drv.user_data = NULL;             /*Any custom data if required*/

    lv_fs_drv_register(&drv);                 /*Finally register the drive*/
}




void test() {

}


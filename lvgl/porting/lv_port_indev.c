/**
 * @file lv_port_indev_templ.c
 *
 */

/*Copy this file as "lv_port_indev.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_indev.h"
#include "../../lvgl.h"
#include "gui_guider.h"

/*********************
 *      DEFINES
 *********************/
uint8_t Direction = 0;
int32_t enc1 = 0, enc1_old = 0;

/**********************
 *      TYPEDEFS
 **********************/
extern lv_ui guider_ui;
/**********************
 *  STATIC PROTOTYPES
 **********************/
static void encoder_init(void);
static void encoder_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data);
static void encoder_handler(void);

static void button_init(void);
static void button_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data);
static int8_t button_get_pressed_id(void);
static bool button_is_pressed(uint8_t id);

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_indev_t *indev_encoder;
lv_indev_t *indev_button;

static int32_t encoder_diff;
static lv_indev_state_t encoder_state;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_port_indev_init(void)
{
    static lv_indev_drv_t indev_drv;

    encoder_init();

    /*Register a encoder input device*/
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_ENCODER;
    indev_drv.read_cb = encoder_read;
    indev_encoder = lv_indev_drv_register(&indev_drv);

    lv_group_t *g = lv_group_create();
    lv_group_set_default(g); // 设置组(group)为默认模式,后面的部件创建时会自动加入组(group)
    g->wrap = 1;
    g->editing = 0;
    g->frozen = 0;
    lv_indev_set_group(indev_encoder, g);

    // lv_group_focus_next(g);
    // lv_indev_drv_init(&indev_drv);
    // indev_drv.type = LV_INDEV_TYPE_BUTTON;
    // indev_drv.read_cb = button_read;
    // indev_button = lv_indev_drv_register(&indev_drv);

    // /*Assign buttons to points on the screen*/
    // static const lv_point_t btn_points[1] = {
    //         {20, 420},   /*Button 0 -> x:10; y:10*/
    // };
    // lv_indev_set_button_points(indev_button, btn_points);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*------------------
 * Encoder
 * -----------------*/

/*Initialize your keypad*/
static void encoder_init(void)
{
    /*Your code comes here*/

    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
}

/*Will be called by the library to read the encoder*/
static void encoder_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{

    if (EC_K == 0)                         // 编码器的按键
        encoder_state = LV_INDEV_STATE_PR; // 按下

    else
        encoder_state = LV_INDEV_STATE_REL; // 松开
    uint8_t temp = __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim3);
    enc1_old = (uint32_t)(__HAL_TIM_GET_COUNTER(&htim3));
    if (enc1 != enc1_old)
    {
        lv_group_t *gr = lv_group_get_default();
        if (temp == 0)
        {
            lv_group_focus_prev(gr);
            encoder_diff--;
            encoder_state = LV_KEY_LEFT;
        }
        else if (temp == 1)
        {

            lv_group_focus_next(gr);
            encoder_diff++;
            encoder_state = LV_KEY_RIGHT;
        }
        Direction = temp;
        enc1 = enc1_old;
    }

    data->enc_diff = encoder_diff;
    data->state = encoder_state;
    encoder_diff = 0;
}

/*Call this function in an interrupt to process encoder events (turn, press)*/
static void encoder_handler(void)
{
    /*Your code comes here*/

    encoder_diff += 0;
    encoder_state = LV_INDEV_STATE_REL;
}

static void button_init(void)
{
    /*Your code comes here*/
}

static void button_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{

    static uint8_t last_btn = 0;

    /*Get the pressed button's ID*/
    int8_t btn_act = button_get_pressed_id();

    if (btn_act >= 0)
    {
        data->state = LV_INDEV_STATE_PR;
        last_btn = btn_act;
    }
    else
    {
        data->state = LV_INDEV_STATE_REL;
    }

    /*Save the last pressed button's ID*/
    data->btn_id = last_btn;
}

static int8_t button_get_pressed_id(void)
{
    uint8_t i;

    /*Check to buttons see which is being pressed (assume there are 2 buttons)*/
    for (i = 0; i < 2; i++)
    {
        /*Return the pressed button's ID*/
        if (button_is_pressed(i))
        {
            return i;
        }
    }

    /*No button pressed*/
    return -1;
}

static bool button_is_pressed(uint8_t id)
{

    /*Your code comes here*/
    // if(EC_K == 0)
    // {
    //     return true;
    // }

    return false;
}

#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif

#include QMK_KEYBOARD_H

#define _COLEMAK 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16
#define KC_ KC_TRN
#define KC_LOWR LOWER
#define KC_RASE RAISE
#define KC_RST RESET
#define KC____  KC_TRNS

enum custom_keycodes {
  COLEMAK = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAK] = LAYOUT(
     GRV , 1  , 2  , 3  , 4  , 5  ,                6 ,  7  , 8  , 9  , 0  ,BSPC,
     TAB , Q  , W  , F  , P  , B  ,                J  , L  , U  , Y  ,SCLN, DEL,
     ESC , A  , R  , S  , T  , G  ,                M  , N  , E  , I  , O  ,QUOT,
     LSFT, Z  , X  , C  , D  , V  ,HOME,     LALT, K  , H  ,COMM, DOT,SLSH,RSFT,
                   ___, LGUI,LOWR, ENT,        SPC,RASE,LCTL,___
  ),
 
  [_LOWER] = LAYOUT(
     TILD,EXLM, AT ,HASH, DLR,PERC,               MRWD,MPLY,MFFD,LPRN,MINS, EQL,
     ___ ,___ ,___ ,___ ,___ ,___ ,               ___ ,___ , UP ,LBRC,RBRC,BSLS,
     ___ ,___ ,___ ,___ ,___ ,___ ,               ___ ,LEFT,DOWN,RGHT,___ ,PGDN,
     ___ ,___ ,___ ,___ ,___ ,___ ,___ ,     ___ ,___ ,___ ,___ ,___ ,___ ,___ ,
                    ___, ___ ,___ ,___ ,      ___ ,___ ,___ ,___
  ),

  [_RAISE] = LAYOUT(
     ___ ,BRID,BRIU,___ ,___ ,___ ,               ___ ,___ ,___ ,VOLD,VOLU,MUTE,
     ___ ,___ ,___ ,WH_U,___ ,___ ,               ___ ,___ ,MS_U,___ ,___ ,___ ,
     ___ ,___ ,WH_L,WH_D,WH_R,___ ,               ___ ,MS_L,MS_D,MS_R,___ ,___ ,
     ___ ,___ ,___ ,___ ,___ ,___ ,MS_BTN2,  ___ ,___ ,___ ,___ ,___ ,___ ,___ ,
                    ___, ___ ,___ ,MS_BTN1,   ___ ,___ ,___ ,___
  ),
 
  [_ADJUST] = LAYOUT(
     ___ ,___ ,___ ,___ ,___ ,___ ,               ___ ,___ ,___ ,___ ,___ ,___ ,
     ___ ,___ ,___ ,___ ,___ ,___ ,               ___ ,___ ,___ ,___ ,___ ,___ ,
     ___ ,___ ,___ ,___ ,___ ,___ ,               ___ ,___ ,___ ,___ ,___ ,___ ,
     ___ ,___ ,___ ,___ ,___ ,___ ,___ ,     ___ ,___ ,___ ,___ ,___ ,___ ,___ ,
                    ___, ___ ,___ ,___ ,      ___ ,___ ,___ ,___
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false);
  }
}
#endif // OLED_DRIVER_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  return true;
}

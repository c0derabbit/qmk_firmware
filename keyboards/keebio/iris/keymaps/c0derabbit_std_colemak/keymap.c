#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

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
  [_COLEMAK] = LAYOUT_kc(
     GRV , 1  , 2  , 3  , 4  , 5  ,                6 ,  7  , 8  , 9  , 0  ,BSPC,
     TAB , Q  , W  , F  , P  , G  ,                J  , L  , U  , Y  ,SCLN, DEL,
     ESC , A  , R  , S  , T  , D  ,                H  , N  , E  , I  , O  ,QUOT,
     LSFT, Z  , X  , C  , V  , B  ,HOME,     LALT, K  , M  ,COMM, DOT,SLSH,RSFT,
                        LGUI,LOWR, ENT,        SPC,RASE,LCTL
  ),
 
  [_LOWER] = LAYOUT_kc(
     TILD,EXLM, AT ,HASH, DLR,PERC,               MRWD,MPLY,MFFD,LPRN,MINS, EQL,
     ___ ,___ ,___ ,___ ,___ ,___ ,               ___ ,___ , UP ,LBRC,RBRC,BSLS,
     ___ ,___ ,___ ,___ ,___ ,___ ,               ___ ,LEFT,DOWN,RGHT,___ ,PGDN,
     ___ ,___ ,___ ,___ ,___ ,___ ,___ ,     ___ ,___ ,___ ,___ ,___ ,___ ,___ ,
                        ___ ,___ ,___ ,       ___ ,___ ,___ 
  ),

  [_RAISE] = LAYOUT_kc(
     ___ ,BRID,BRIU,___ ,___ ,___ ,               ___ ,___ ,___ ,VOLD,VOLU,MUTE,
     ___ ,___ ,___ ,WH_U,___ ,___ ,               ___ ,___ ,MS_U,___ ,___ ,___ ,
     ___ ,___ ,WH_L,WH_D,WH_R,___ ,               ___ ,MS_L,MS_D,MS_R,___ ,___ ,
     ___ ,___ ,___ ,___ ,___ ,___ ,MS_BTN2,  ___ ,___ ,___ ,___ ,___ ,___ ,___ ,
                        ___ ,___ ,MS_BTN1,    ___ ,___ ,___ 
  ),
 
  [_ADJUST] = LAYOUT_kc(
     ___ ,___ ,___ ,___ ,___ ,___ ,               ___ ,___ ,___ ,___ ,___ ,___ ,
     ___ ,___ ,___ ,___ ,___ ,___ ,               ___ ,___ ,___ ,___ ,___ ,___ ,
     ___ ,___ ,___ ,___ ,___ ,___ ,               ___ ,___ ,___ ,___ ,___ ,___ ,
     ___ ,___ ,___ ,___ ,___ ,___ ,___ ,     ___ ,___ ,___ ,___ ,___ ,___ ,___ ,
                        ___ ,___ ,___ ,       ___ ,___ ,___ 
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}

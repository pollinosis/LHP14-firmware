#include QMK_KEYBOARD_H
#include "joystick.h"
#include "analog.h"

#define SAM 0
#define SCH 1
//#define DRG 2
//#define DRK 3
//#define WAR 4
//#define DNC 5
//#define WHM 6
//#define RDM 7
//#define NIN 8
#define RGB 2




#ifdef OLED_DRIVER_ENABLE

void render_logo(void) {
    oled_set_cursor(0, 0);
    oled_write_P(lhp_logo, false);
}

enum custom_keycodes {
  SR_CS = SAFE_RANGE,
  RR_RD,
  RGBRST
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SR_CS:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT("0") "-");
      }
      break;
    case RR_RD:
      if (record->event.pressed) {
		register_code(KC_LCTL);
        SEND_STRING(SS_LALT("2"));
        unregister_code(KC_LCTL);
        SEND_STRING("5");
      }
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
        }
      #endif
      break;
  }
  return true;
}


void render_layer(void) {
	
	oled_set_cursor(START_COL, START_ROW);
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case SAM:
            oled_write_P(PSTR("SAMURAI\n"), false);
            rgblight_sethsv(0, 255, 180);
            break;
        case SCH:
            oled_write_P(PSTR("SCHOLAR\n"), false);
            rgblight_sethsv(20, 255, 210);
            break;
/*        case DRG:
            oled_write_P(PSTR("DRAGOON\n"), false);
            rgblight_sethsv(170, 255, 180);
            break;
        case DRK:
            oled_write_P(PSTR("DARK KNIGHT\n"), false);
            rgblight_sethsv(0, 255, 90);
            break;
        case WAR:
            oled_write_P(PSTR("WARRIOR\n"), false);
            rgblight_sethsv(85, 255, 90);
            break;            
        case DNC:
            oled_write_P(PSTR("DANCER\n"), false);
            rgblight_sethsv(213, 255, 180);
            break;            
        case WHM:
            oled_write_P(PSTR("WHITE MAGE\n"), false);
            rgblight_sethsv(11, 176, 180);
            break;
        case RDM:
            oled_write_P(PSTR("RED MAGE\n"), false);
            rgblight_sethsv(0, 255, 220);
            break;            
        case NIN:
            oled_write_P(PSTR("NINJA\n"), false);
            rgblight_sethsv(191, 255, 150);
            break;
 */
        case RGB:
            oled_write_P(PSTR("RGB LED TEST\n"), false);
            //rgblight_sethsv(128, 255, 180);
            break;     
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }
}

void oled_task_user(void) {
    render_logo();
    render_layer();
}

void suspend_power_down_user(void) {
    oled_off();
}

#endif



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* SAM
   * ,----------------------------------.   
   * |∫›act1|  W   |ƒ©Ÿ∞N lè∆îj  |  D   |   
   * |------+------+------+------+------|   
   * |  A   |Space |¿πﬁë÷ |¿πﬁãﬂ |ëMâe  |   
   * |------+------+------+------+------|   
   * |ótâB  |à”ãCè’|±—⁄›  |ñæãæ  |ñÚ1   |   
   * |------+------+------+------+------|   
   * |SCH   |∫›act2|  S   |ñÈìV  |ñŸëz  |   
   * `----------------------------------'   
   *
   */
  [SAM] = LAYOUT( \
    KC_Z,       KC_W,         LALT(KC_1), LALT(KC_4), KC_D,       \
    KC_A,       KC_SPC,       KC_F,       KC_T,       LALT(KC_9), \
    LALT(KC_5), LALT(KC_2),   KC_AMPR,    KC_ASTR,    LALT(KC_0), \
    TO(SCH),    LCA(KC_MINS), KC_S,       LALT(KC_7), LALT(KC_3),    JS_BUTTON7 \
  ),

/* [SAM] = LAYOUT( \
    KC_Q,     KC_W,     KC_E,       KC_R,     KC_T,      \
    KC_A,     KC_S,     KC_D,       KC_F,     KC_G,      \
    KC_1,     KC_Z,     KC_X,       KC_C,     KC_V,      \
    TO(SCH),  KC_3,     KC_5,       KC_6,     KC_7,      \
  ),*/




  /* SCH
   * ,----------------------------------.   
   * | ﬂ∏ƒ2 |   W  |îÈçÙ  |      |ã~èo  |   
   * |------+------+------+------+------|   
   * |      |Space |¿πﬁë÷ |¿πﬁãﬂ |Ÿ∞ºØƒﬁ|   
   * |------+------+------+------+------|   
   * |∫›act1|¥∞√Ã€∞|åòé¿ñÇ|òAä¬åv|ì]âª  |   
   * |------+------+------+------+------|   
   * |RGB   |      |   S  |âûã}  |æ◊+∫›ø|   
   * `----------------------------------'   
   */
  [SCH] = LAYOUT( \
    LCA(KC_5), KC_W,       KC_ASTR,    XXXXXXX,    LALT(KC_3),  \
    XXXXXXX,   KC_SPC,     KC_F,       KC_T,       LALT(KC_4),  \
    KC_Z,      LALT(KC_6), LALT(KC_5), LALT(KC_1), LCA(KC_7) ,  \
    TO(RGB),   XXXXXXX,    KC_S,       KC_7,       SR_CS,         JS_BUTTON7 \
  ),

  /* DRG
   * ,------------------------------------------------.   
   * |∫›act1|¿πﬁST |  W   |ƒ©Ÿ∞N |Ω ﬂ≤›D|¿πﬁMT |ÿ¿∆∞  |   
   * |------+------+------+------+------+------+------|   
   * |   A  |      |Space |¿πﬁë÷ |¿πﬁãﬂ |ºﬁ¨›Ãﬂ|  D   |   
   * |------+------+------+------+------+------+------|   
   * |      |∫›act1|ëìó≥åå|±—⁄›  |D¿ﬁ≤Ãﬁ| ñÚ1  | DRK  |   
   * |------+------+------+------+------+------+------|   
   * |ó≥í‹îˆ|      |      |   S  |≤Ÿ∞ºÃﬁ|ÿ¿∆∞  |  LB  |   
   * `------------------------------------------------'   

  [DRG] = LAYOUT( \
    KC_Z,     KC_F3,     KC_W,       LALT(KC_1), KC_EQUAL,  KC_F1,      LALT(KC_6), \
    KC_A,     XXXXXXX,   KC_SPC,     KC_F,       KC_T,      KC_MINUS,   KC_D,       \
    XXXXXXX,  KC_Z,      LALT(KC_9), KC_ASTR,    KC_0,      LCA(KC_0),  TO(DRK),    \
    RR_RD,    XXXXXXX,   XXXXXXX,    KC_S,       LALT(KC_7),                        \
                                                            LALT(KC_6),             \
                                                                        KC_F12      \
  ),

   DRK
   * ,------------------------------------------------.   
   * | º¨∞∏ |      |      |ÿÃﬂ◊≤ |±ÀﬁªŸ |      |ÿÀﬁ√ﬁ |   
   * |------+------+------+------+------+------+------|   
   * |∫›act1|      |Space |¿πﬁë÷ |¿πﬁãﬂ |Ãﬁ◊√ﬁÿ|      |   
   * |------+------+------+------+------+------+------|   
   * |      |      |Ãﬁ◊≈≤ |±—⁄›  |Ãﬁ◊≥™ |      | WAR  |   
   * |------+------+------+------+------+------+------|   
   * |      |      |      |      |Ω¿›Ω  |      |  LB  |   
   * `------------------------------------------------'   

  [DRK] = LAYOUT( \
    LCA(KC_EQL), XXXXXXX, XXXXXXX,      KC_LPRN,    LALT(KC_1), XXXXXXX,    LCA(KC_3),  \
    KC_Z,        XXXXXXX, KC_SPC,       KC_F,       KC_T,       LALT(KC_2), XXXXXXX,    \
    XXXXXXX,     XXXXXXX, LALT(KC_EQL), LALT(KC_6), LALT(KC_3), XXXXXXX,    TO(WAR),    \
    XXXXXXX,     XXXXXXX, XXXXXXX,      XXXXXXX,    LALT(KC_4),                         \
                                                                XXXXXXX,                \
                                                                            KC_F12      \
  ),

   WAR
   * ,------------------------------------------------.   
   * | º¨∞∏ |      |º™≤∏µÃ|ÿÃﬂ◊≤ |      |      | ŒŸ—  |   
   * |------+------+------+------+------+------+------|   
   * |      |      |Space |¿πﬁë÷ |¿πﬁãﬂ |Ã™Ÿ∏ÿ |      |   
   * |------+------+------+------+------+------+------|   
   * |      |      |≥´∞∏◊≤|±—⁄›  |å¥èâäJ|      | DNC  |   
   * |------+------+------+------+------+------+------|   
   * |      |      |      |      |Ω¿›Ω  |      |  LB  |   
   * `------------------------------------------------'   

  [WAR] = LAYOUT( \
    LCA(KC_EQL), XXXXXXX, KC_PLUS,      KC_LPRN,    XXXXXXX,    XXXXXXX,    LCA(KC_3),  \
    XXXXXXX,     XXXXXXX, KC_SPC,       KC_F,       KC_T,       LALT(KC_3), XXXXXXX,    \
    XXXXXXX,     XXXXXXX, LALT(KC_UNDS),LALT(KC_9), LALT(KC_5), XXXXXXX,    TO(DNC),    \
    XXXXXXX,     XXXXXXX, XXXXXXX,      XXXXXXX,    LALT(KC_1),                         \
                                                                XXXXXXX,                \
                                                                            KC_F12      \
  ),

   DNC
   * ,------------------------------------------------.   
   * |      |      |      |±›± ﬁ›|      |¿πﬁMT |      |   
   * |------+------+------+------+------+------+------|   
   * |      |      |Space |¿πﬁë÷ |¿πﬁãﬂ |Ã◊ÿØº≠|      |   
   * |------+------+------+------+------+------+------|   
   * |      |∫›act1|éÁª› ﬁ|±—⁄›  |çU¿›∫ﬁ|      | WHM  |   
   * |------+------+------+------+------+------+------|   
   * |      |      |      |      |ñ¸‹Ÿ¬ |≤›Ãﬂ€À|  LB  |   
   * `------------------------------------------------'   

  [DNC] = LAYOUT( \
    XXXXXXX,  XXXXXXX,   XXXXXXX,   KC_EQUAL,   XXXXXXX,   KC_F1,   XXXXXXX, \
    XXXXXXX,  XXXXXXX,   KC_SPC,    KC_F,       KC_T,      KC_8,    XXXXXXX, \
    XXXXXXX,  KC_Z,      KC_LPRN,   LALT(KC_5), KC_AMPR,   XXXXXXX, TO(WHM), \
    XXXXXXX,  XXXXXXX,   XXXXXXX,   XXXXXXX,    KC_ASTR,                     \
                                                           KC_MINUS,         \
                                                                    KC_F12   \
  ),

   WHM
   * ,------------------------------------------------.   
   * |∫›act1|      |   W  |Õﬁ∆ø›T|√› ﬂ  |¿πﬁMT |ã~èo  |   
   * |------+------+------+------+------+------+------|   
   * |      |      |Space |¿πﬁë÷ |¿πﬁãﬂ |Ÿ∞ºØƒﬁ|      |   
   * |------+------+------+------+------+------+------|   
   * |      |      |º›¥±∞ |åòé¿ñÇ|ê_ë¨ñÇ|      | RDM  |   
   * |------+------+------+------+------+------+------|   
   * |      |      |      |      |≤›ƒﬁ©Ÿ|∫›act1|  LB  |   
   * `------------------------------------------------'   

  [WHM] = LAYOUT( \
    KC_Z,      XXXXXXX,   KC_W,       LALT(KC_EQUAL),LALT(KC_5),    KC_F1,      LALT(KC_4),    \
    XXXXXXX,   XXXXXXX,   KC_SPC,     KC_F,          KC_T,          LALT(KC_8), XXXXXXX,       \
    XXXXXXX,   XXXXXXX,   LALT(KC_0), LALT(KC_6),    LALT(KC_MINUS),XXXXXXX,    TO(RDM),       \
    XXXXXXX,   XXXXXXX,   XXXXXXX,    XXXXXXX,       LALT(KC_7),                               \
                                                                    KC_Z,                      \
                                                                                KC_F12         \
  ),

   RDM
   * ,------------------------------------------------.   
   * |∫›act1|      |      |±∏æ◊  |      |¿πﬁMT |      |   
   * |------+------+------+------+------+------+------|   
   * |      |      |Space |¿πﬁë÷ |¿πﬁãﬂ |Ÿ∞ºØƒﬁ|      |   
   * |------+------+------+------+------+------+------|   
   * |      |      |œ≈Ã®π |åòé¿ñÇ|¥›ŒﬁŸ |±ƒﬁŸ  | NIN  |   
   * |------+------+------+------+------+------+------|   
   * |      |      |      |      |      |∫›act1|  LB  |   
   * `------------------------------------------------'   

  [RDM] = LAYOUT( \
    KC_Z,      XXXXXXX,   XXXXXXX,    LALT(KC_4), XXXXXXX,    KC_F1,      XXXXXXX,       \
    XXXXXXX,   XXXXXXX,   KC_SPC,     KC_F,       KC_T,       LALT(KC_3), XXXXXXX,       \
    XXXXXXX,   XXXXXXX,   LALT(KC_9), KC_ASTR,    LALT(KC_5), LALT(KC_2), TO(NIN),       \
    XXXXXXX,   XXXXXXX,   XXXXXXX,    XXXXXXX,    XXXXXXX,                               \
                                                              KC_Z,                      \
                                                                          KC_F12         \
  ),

   NIN
   * ,------------------------------------------------.   
   * |      |      |  W   |ƒ©Ÿ∞N |      |¿πﬁMT |      |   
   * |------+------+------+------+------+------+------|   
   * |      |      |Space |¿πﬁë÷ |¿πﬁãﬂ |ìVínêl|      |   
   * |------+------+------+------+------+------+------|   
   * |      |Ç©Ç≠ÇÍ|ÇæÇ‹Çµ|±—⁄›  |äàéE  |      | SAM  |   
   * |------+------+------+------+------+------+------|   
   * |      |      |      |      |ñΩêÖ  |      |  LB  |   
   * `------------------------------------------------'   

  [NIN] = LAYOUT( \
    XXXXXXX,   XXXXXXX,   KC_W,       LALT(KC_3), XXXXXXX,    KC_F1,      XXXXXXX,       \
    XXXXXXX,   XXXXXXX,   KC_SPC,     KC_F,       KC_T,       LALT(KC_2), XXXXXXX,       \
    XXXXXXX,   LALT(KC_0),LALT(KC_7), LALT(KC_4), LALT(KC_1), XXXXXXX,    TO(SAM),       \
    XXXXXXX,   XXXXXXX,   XXXXXXX,    XXXXXXX,    KC_9,                                  \
                                                              XXXXXXX,                   \
                                                                          KC_F12         \
  ),
*/

  /* RGB
   * ,----------------------------------.   
   * |RGBTOG|RGBHUI|RGBHUD|RGBSAI|RGBSAD|   
   * |------+------+------+------+------|   
   * |RGBMOD|RGBRST|RGBVAI|RGBVAD|      |   
   * |------+------+------+------+------|   
   * |      |      |      |      |      |   
   * |------+------+------+------+------|   
   * |SAM   |      |      |      |      |   
   * `----------------------------------'   
   */
  [RGB] = LAYOUT( \
    RGB_TOG,   RGB_HUI,   RGB_HUD,    RGB_SAI,    RGB_SAD, \
    RGB_MOD,   RGBRST,    RGB_VAI,    RGB_VAD,    XXXXXXX, \
    XXXXXXX,   XXXXXXX,   XXXXXXX,    XXXXXXX,    XXXXXXX, \
    TO(SAM),   XXXXXXX,   XXXXXXX,    XXXXXXX,    XXXXXXX,    JS_BUTTON7 \
  ),

};

void joystick_task(){

		joystick_status.axes[0] = -(analogReadPin(D4)/4 - 128);
		joystick_status.axes[1] = analogReadPin(F4)/4 - 128;
        send_joystick_packet(&joystick_status);
}



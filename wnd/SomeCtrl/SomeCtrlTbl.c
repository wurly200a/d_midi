/* 共通インクルードファイル */
#include "common.h"
/* 個別インクルードファイル */

/* 外部関数定義 */
#include "WinMain.h"

/* 外部変数定義 */

/* 内部関数定義 */
#include "SomeCtrl.h"
/* 内部変数定義 */

extern const char *generalMidiProgramChangeStrTbl[128] =
{
    "  0 Acoustic Piano           ", /* 0x00 */
    "  1 Bright Piano             ", /* 0x01 */
    "  2 Electric Grand Piano     ", /* 0x02 */
    "  3 Honky-tonk Piano         ", /* 0x03 */
    "  4 Electric Piano           ", /* 0x04 */
    "  5 Electric Piano 2         ", /* 0x05 */
    "  6 Harpsichord              ", /* 0x06 */
    "  7 Clavi                    ", /* 0x07 */
    "  8 Celesta                  ", /* 0x08 */
    "  9 Glockenspiel             ", /* 0x09 */
    " 10 Musical box              ", /* 0x0A */
    " 11 Vibraphone               ", /* 0x0B */
    " 12 Marimba                  ", /* 0x0C */
    " 13 Xylophone                ", /* 0x0D */
    " 14 Tubular Bell             ", /* 0x0E */
    " 15 Dulcimer                 ", /* 0x0F */
    " 16 Drawbar Organ            ", /* 0x10 */
    " 17 Percussive Organ         ", /* 0x11 */
    " 18 Rock Organ               ", /* 0x12 */
    " 19 Church organ             ", /* 0x13 */
    " 20 Reed organ               ", /* 0x14 */
    " 21 Accordion                ", /* 0x15 */
    " 22 Harmonica                ", /* 0x16 */
    " 23 Tango Accordion          ", /* 0x17 */
    " 24 Acoustic Guitar (nylon)  ", /* 0x18 */
    " 25 Acoustic Guitar (steel)  ", /* 0x19 */
    " 26 Electric Guitar (jazz)   ", /* 0x1A */
    " 27 Electric Guitar (clean)  ", /* 0x1B */
    " 28 Electric Guitar (muted)  ", /* 0x1C */
    " 29 Overdriven Guitar        ", /* 0x1D */
    " 30 Distortion Guitar        ", /* 0x1E */
    " 31 Guitar harmonics         ", /* 0x1F */
    " 32 Acoustic Bass            ", /* 0x20 */
    " 33 Electric Bass (finger)   ", /* 0x21 */
    " 34 Electric Bass (pick)     ", /* 0x22 */
    " 35 Fretless Bass            ", /* 0x23 */
    " 36 Slap Bass 1              ", /* 0x24 */
    " 37 Slap Bass 2              ", /* 0x25 */
    " 38 Synth Bass 1             ", /* 0x26 */
    " 39 Synth Bass 2             ", /* 0x27 */
    " 40 Violin                   ", /* 0x28 */
    " 41 Viola                    ", /* 0x29 */
    " 42 Cello                    ", /* 0x2A */
    " 43 Double bass              ", /* 0x2B */
    " 44 Tremolo Strings          ", /* 0x2C */
    " 45 Pizzicato Strings        ", /* 0x2D */
    " 46 Orchestral Harp          ", /* 0x2E */
    " 47 Timpani                  ", /* 0x2F */
    " 48 String Ensemble 1        ", /* 0x30 */
    " 49 String Ensemble 2        ", /* 0x31 */
    " 50 Synth Strings 1          ", /* 0x32 */
    " 51 Synth Strings 2          ", /* 0x33 */
    " 52 Voice Aahs               ", /* 0x34 */
    " 53 Voice Oohs               ", /* 0x35 */
    " 54 Synth Voice              ", /* 0x36 */
    " 55 Orchestra Hit            ", /* 0x37 */
    " 56 Trumpet                  ", /* 0x38 */
    " 57 Trombone                 ", /* 0x39 */
    " 58 Tuba                     ", /* 0x3A */
    " 59 Muted Trumpet            ", /* 0x3B */
    " 60 French horn              ", /* 0x3C */
    " 61 Brass Section            ", /* 0x3D */
    " 62 Synth Brass 1            ", /* 0x3E */
    " 63 Synth Brass 2            ", /* 0x3F */
    " 64 Soprano Sax              ", /* 0x40 */
    " 65 Alto Sax                 ", /* 0x41 */
    " 66 Tenor Sax                ", /* 0x42 */
    " 67 Baritone Sax             ", /* 0x43 */
    " 68 Oboe                     ", /* 0x44 */
    " 69 English Horn             ", /* 0x45 */
    " 70 Bassoon                  ", /* 0x46 */
    " 71 Clarinet                 ", /* 0x47 */
    " 72 Piccolo                  ", /* 0x48 */
    " 73 Flute                    ", /* 0x49 */
    " 74 Recorder                 ", /* 0x4A */
    " 75 Pan Flute                ", /* 0x4B */
    " 76 Blown Bottle             ", /* 0x4C */
    " 77 Shakuhachi               ", /* 0x4D */
    " 78 Whistle                  ", /* 0x4E */
    " 79 Ocarina                  ", /* 0x4F */
    " 80 Lead 1 (square)          ", /* 0x50 */
    " 81 Lead 2 (sawtooth)        ", /* 0x51 */
    " 82 Lead 3 (calliope)        ", /* 0x52 */
    " 83 Lead 4 (chiff)           ", /* 0x53 */
    " 84 Lead 5 (charang)         ", /* 0x54 */
    " 85 Lead 6 (voice)           ", /* 0x55 */
    " 86 Lead 7 (fifths)          ", /* 0x56 */
    " 87 Lead 8 (bass + lead)     ", /* 0x57 */
    " 88 Pad 1 (Fantasia)         ", /* 0x58 */
    " 89 Pad 2 (warm)             ", /* 0x59 */
    " 90 Pad 3 (polysynth)        ", /* 0x5A */
    " 91 Pad 4 (choir)            ", /* 0x5B */
    " 92 Pad 5 (bowed)            ", /* 0x5C */
    " 93 Pad 6 (metallic)         ", /* 0x5D */
    " 94 Pad 7 (halo)             ", /* 0x5E */
    " 95 Pad 8 (sweep)            ", /* 0x5F */
    " 96 FX 1 (rain)              ", /* 0x60 */
    " 97 FX 2 (soundtrack)        ", /* 0x61 */
    " 98 FX 3 (crystal)           ", /* 0x62 */
    " 99 FX 4 (atmosphere)        ", /* 0x63 */
    "100 FX 5 (brightness)        ", /* 0x64 */
    "101 FX 6 (goblins)           ", /* 0x65 */
    "102 FX 7 (echoes)            ", /* 0x66 */
    "103 FX 8 (sci-fi)            ", /* 0x67 */
    "104 Sitar                    ", /* 0x68 */
    "105 Banjo                    ", /* 0x69 */
    "106 Shamisen                 ", /* 0x6A */
    "107 Koto                     ", /* 0x6B */
    "108 Kalimba                  ", /* 0x6C */
    "109 Bagpipe                  ", /* 0x6D */
    "110 Fiddle                   ", /* 0x6E */
    "111 Shanai                   ", /* 0x6F */
    "112 Tinkle Bell              ", /* 0x70 */
    "113 Agogo                    ", /* 0x71 */
    "114 Steel Drums              ", /* 0x72 */
    "115 Woodblock                ", /* 0x73 */
    "116 Taiko Drum               ", /* 0x74 */
    "117 Melodic Tom              ", /* 0x75 */
    "118 Synth Drum               ", /* 0x76 */
    "119 Reverse Cymbal           ", /* 0x77 */
    "120 Guitar Fret Noise        ", /* 0x78 */
    "121 Breath Noise             ", /* 0x79 */
    "122 Seashore                 ", /* 0x7A */
    "123 Bird Tweet               ", /* 0x7B */
    "124 Telephone Ring           ", /* 0x7C */
    "125 Helicopter               ", /* 0x7D */
    "126 Applause                 ", /* 0x7E */
    "127 Gunshot                  ", /* 0x7F */
};

extern const char *midiControlChangeStrTbl[128] =
{
    "  0 Bank Select                                             ",
    "  1 Modulation                                              ",
    "  2 Breath Controller                                       ",
    "  3 Undefined                                               ",
    "  4 Foot Controller                                         ",
    "  5 Portamento Time                                         ",
    "  6 Data Entry Most Significant Bit(MSB)                    ",
    "  7 Volume                                                  ",
    "  8 Balance                                                 ",
    "  9 Undefined                                               ",
    " 10 Pan                                                     ",
    " 11 Expression                                              ",
    " 12 Effect Controller 1                                     ",
    " 13 Effect Controller 2                                     ",
    " 14 Undefined                                               ",
    " 15 Undefined                                               ",
    " 16 General Purpose                                         ",
    " 17 General Purpose                                         ",
    " 18 General Purpose                                         ",
    " 19 General Purpose                                         ",
    " 20 Undefined                                               ",
    " 21 Undefined                                               ",
    " 22 Undefined                                               ",
    " 23 Undefined                                               ",
    " 24 Undefined                                               ",
    " 25 Undefined                                               ",
    " 26 Undefined                                               ",
    " 27 Undefined                                               ",
    " 28 Undefined                                               ",
    " 29 Undefined                                               ",
    " 30 Undefined                                               ",
    " 31 Undefined                                               ",
    " 32 ",
    " 33 ",
    " 34 ",
    " 35 ",
    " 36 ",
    " 37 ",
    " 38 ",
    " 39 ",
    " 40 ",
    " 41 ",
    " 42 ",
    " 43 ",
    " 44 ",
    " 45 ",
    " 46 ",
    " 47 ",
    " 48 ",
    " 49 ",
    " 50 ",
    " 51 ",
    " 52 ",
    " 53 ",
    " 54 ",
    " 55 ",
    " 56 ",
    " 57 ",
    " 58 ",
    " 59 ",
    " 60 ",
    " 61 ",
    " 62 ",
    " 63 ",
    " 64 Damper Pedal /Sustain Pedal                             ",
    " 65 Portamento On/Off Switch                                ",
    " 66 Sostenuto On/Off Switch                                 ",
    " 67 Soft Pedal On/Off Switch                                ",
    " 68 Legato FootSwitch                                       ",
    " 69 Hold 2                                                  ",
    " 70 Sound Controller 1                                      ",
    " 71 Sound Controller 2                                      ",
    " 72 Sound Controller 3                                      ",
    " 73 Sound Controller 4                                      ",
    " 74 Sound Controller 5                                      ",
    " 75 Sound Controller 6                                      ",
    " 76 Sound Controller 7                                      ",
    " 77 Sound Controller 8                                      ",
    " 78 Sound Controller 9                                      ",
    " 79 Sound Controller 10                                     ",
    " 80 General Purpose MIDI CC Controller                      ",
    " 81 General Purpose MIDI CC Controller                      ",
    " 82 General Purpose MIDI CC Controller                      ",
    " 83 General Purpose MIDI CC Controller                      ",
    " 84 Portamento CC Control                                   ",
    " 85 Undefined                                               ",
    " 86 Undefined                                               ",
    " 87 Undefined                                               ",
    " 88 Undefined                                               ",
    " 89 Undefined                                               ",
    " 90 Undefined                                               ",
    " 91 Effect 1 Depth                                          ",
    " 92 Effect 2 Depth                                          ",
    " 93 Effect 3 Depth                                          ",
    " 94 Effect 4 Depth                                          ",
    " 95 Effect 5 Depth                                          ",
    " 96 (+1) Data Increment                                     ",
    " 97 (-1) Data Decrement                                     ",
    " 98 Non-Registered Parameter Number LSB (NRPN)              ",
    " 99 Non-Registered Parameter Number MSB (NRPN)              ",
    "100 Registered Parameter Number LSB (RPN)                  ",
    "101 Registered Parameter Number MSB (RPN)                  ",
    "102 Undefined                                              ",
    "103 Undefined                                              ",
    "104 Undefined                                              ",
    "105 Undefined                                              ",
    "106 Undefined                                              ",
    "107 Undefined                                              ",
    "108 Undefined                                              ",
    "109 Undefined                                              ",
    "110 Undefined                                              ",
    "111 Undefined                                              ",
    "112 Undefined                                              ",
    "113 Undefined                                              ",
    "114 Undefined                                              ",
    "115 Undefined                                              ",
    "116 Undefined                                              ",
    "117 Undefined                                              ",
    "118 Undefined                                              ",
    "119 Undefined                                              ",
    "120 All Sound Off                                          ",
    "121 Reset All Controllers                                  ",
    "122 Local On/Off Switch                                    ",
    "123 All Notes Off                                          ",
    "124 Omni Mode Off                                          ",
    "125 Omni Mode On                                           ",
    "126 Mono Mode                                              ",
    "127 Poly Mode                                              ",
};

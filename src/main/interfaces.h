

#define CHANNEL_NUM1   12

#ifndef INTERFACES_H_
#define INTERFACES_H_

struct I {
  enum State {
    GLASS,
    TEST
  };
  
  enum Note {
      NONE =  0,
      C0  =  1,
      Cs0 =   2,
      Db0 = 2,
      D0  =   3,
      Ds0 =   4,
      Eb0 = 4,
      E0  =   5,
      F0  =   6,
      Fs0 =   7,
      Gb0 = 7,
      G0  = 8,
      Gs0 = 9,
      Ab0 = 9,
      A_0 =   10,
      As0 = 11,
      Bb0 = 11,
      B_0 =   12,
      C1  =   13,
      Cs1 = 14,
      Db1 = 14,
      D1  = 15,
      Ds1 = 16, 
      Eb1 = 16,
      E1  = 17,
      F1  = 18,
      Fs1 = 19, 
      Gb1 = 19,
      G1  =   20,
      Gs1 = 21, 
      Ab1 = 21,
      A_1  =   22,
      As1 = 23, 
      Bb1 = 23,
      B_1  =  24,
      C2  = 25,
      Cs2 = 26, 
      Db2 = 26,
      D2  = 27,
      Ds2 = 28, 
      Eb2 = 28,
      E2  = 29,
      F2  = 30,
      Fs2 = 31, 
      Gb2 = 31,
      G2  =   32,
      Gs2 = 33, 
      Ab2 = 34,
      A_2  =   35,
      As2 = 36, 
      Bb2 = 36,
      B_2  =  37,
      C3  = 38,
      Cs3 = 39, 
      Db3 = 39,
      D3  = 40,
      Ds3 = 41, 
      Eb3 = 41,
      E3  = 42,
      F3  = 43,
      Fs3 =   44,
      Gb3 =   44,
      G3  =   45,
      Gs3 = 46, 
      Ab3 = 46,
      A_3  =   47,
      As3 = 48, 
      Bb3 = 48,
      B_3  =  49,
      C4  = 50,
      Cs4 = 51, 
      Db4 = 51,
      D4  = 52,
      Ds4 = 53, 
      Eb4 = 53,
      E4  = 54,
      F4  = 55,
      Fs4 = 56, 
      Gb4 = 56,
      G4  =   57,
      Gs4 = 58, 
      Ab4 = 58,
      A_4  =   59,
      As4 = 60, 
      Bb4 = 60,
      B_4  =  61,
      C5  = 62,
      Cs5 = 63, 
      Db5 = 63,
      D5  = 64,
      Ds5 = 65, 
      Eb5 = 65,
      E5  = 66,
      F5  = 67,
      Fs5 = 68, 
      Gb5 = 68,
      G5  = 69,
      Gs5 = 70, 
      Ab5 = 70,
      A_5  =   71,
      As5 = 72, 
      Bb5 = 72,
      B_5  =  73,
      C6  = 74,
      Cs6 = 75, 
      Db6 = 75,
      D6  = 76,
      Ds6 = 77, 
      Eb6 = 77,
      E6  = 78,
      F6  = 79,
      Fs6 = 80, 
      Gb6 = 80,
      G6  = 81,
      Gs6 = 82, 
      Ab6 = 82,
      A_6  =   83,
      As6 = 84, 
      Bb6 = 84,
      B_6  =  85,
      C7  =   86,
      Cs7 = 87, 
      Db7 = 87,
      D7  = 88,
      Ds7 = 89, 
      Eb7 = 89,
      E7  =   90,
      F7  = 91,
      Fs7 = 92, 
      Gb7 = 92,
      G7  = 93,
      Gs7 = 94, 
      Ab7 = 94,
      A_7  =   95,
      As7 = 96, 
      Bb7 = 96,
      B_7  =  97,
      C8  = 98,
      Cs8 = 99, 
      Db8 = 99,
      D8  = 100,
      Ds8 = 101, 
      Eb8 = 101,
      E8  = 102,
      F8  = 103,
      Fs8 = 104,
      Gb8 = 104,
      G8  = 105,
      Gs8 = 106,
      Ab8 = 106,
      A_8  =   107,
      As8 =   108,
      Bb8 = 108,
      B_8  =  109, 
  };
  
  constexpr static double Frequency[110] = {
      0,
      16.35,
      17.32,
      18.35,
      19.45,
      20.6,
      21.83,
      23.12,
      24.5,
      25.96,
      27.5,
      29.14,
      30.87,
      32.7,
      34.65,
      36.71,
      38.89,
      41.2,
      43.65,
      46.25,
      49,
      51.91,
      55,
      58.27,
      61.74,
      65.41,
      69.3,
      73.42,
      77.78,
      82.41,
      87.31,
      92.5,
      98,
      103.83,
      110,
      116.54,
      123.47,
      130.81,
      138.59,
      146.83,
      155.56,
      164.81,
      174.61,
      185,
      196,
      207.65,
      220,
      233.08,
      246.94,
      261.63,
      277.18,
      293.66,
      311.13,
      329.63,
      349.23,
      369.99,
      392,
      415.3,
      440,
      466.16,
      493.88,
      523.25,
      554.37,
      587.33,
      622.25,
      659.25,
      698.46,
      739.99,
      783.99,
      830.61,
      880,
      932.33,
      987.77,
      1046.5,
      1108.73,
      1174.66,
      1244.51,
      1318.51,
      1396.91,
      1479.98,
      1567.98,
      1661.22,
      1760,
      1864.66,
      1975.53,
      2093,
      2217.46,
      2349.32,
      2489.02,
      2637.02,
      2793.83,
      2959.96,
      3135.96,
      3322.44,
      3520,
      3729.31,
      3951.07,
      4186.01,
      4434.92,
      4698.63,
      4978.03,
      5274.04,
      5587.65,
      5919.91,
      6271.93,
      6644.88,
      7040,
      7458.62,
      7902.13 
    };
  
  
  
  
  
  // typedef enum {
  //     C0  =  16.35,
  //     Cs0 =   17.32,
  //     Db0 =  17.32,
  //     D0 =   18.35,
  //     Ds0 =   19.45,
  //     Eb0 =  19.45,
  //     E0 =   20.6,
  //     F0 =   21.83,
  //     Fs0 =    23.12,
  //     Gb0 =  23.12,
  //     G0  =  24.5,
  //     Gs0 =  25.96,
  //     Ab0 =  25.96,
  //     A0 =   27.5,
  //     As0 =  29.14,
  //     Bb0 =  29.14,
  //     B0 =   30.87,
  //     C1 =   32.7,
  //     Cs1 =  34.65,
  //     Db1 =  34.65,
  //     D1  =  36.71,
  //     Ds1 =  38.89, 
  //     Eb1 =  38.89,
  //     E1  =  41.2,
  //     F1  =  43.65,
  //     Fs1 =  46.25, 
  //     Gb1 =  46.25,
  //     G1  =  49,
  //     Gs1 =  51.91, 
  //     Ab1 =  51.91,
  //     A1  =  55,
  //     As1 =  58.27, 
  //     Bb1 =  58.27,
  //     B1  =  61.74,
  //     C2  =  65.41,
  //     Cs2 =  69.3, 
  //     Db2 =  69.3,
  //     D2  =  73.42,
  //     Ds2 =  77.78, 
  //     Eb2 =  77.78,
  //     E2  =  82.41,
  //     F2  =  87.31,
  //     Fs2 =  92.5, 
  //     Gb2 =  92.5,
  //     G2  =  98,
  //     Gs2 =  103.83, 
  //     Ab2 =  103.83,
  //     A2  =  110,
  //     As2 =  116.54, 
  //     Bb2 =  116.54,
  //     B2  =  123.47,
  //     C3  =  130.81,
  //     Cs3 =  138.59, 
  //     Db3 =  138.59,
  //     D3  =  146.83
  //     Ds3 =  155.56, 
  //     Eb3 =  155.56,
  //     E3  =  164.81,
  //     F3  =  174.61,
  //     Fs3 =  185,
  //     Gb3 =  185,
  //     G3  =  196,
  //     Gs3 =  207.65, 
  //     Ab3 =  207.65,
  //     A3  =  220,
  //     As3 =  233.08, 
  //     Bb3 =  233.08,
  //     B3  =  246.94,
  //     C4  =  261.63,
  //     Cs4 =  277.18, 
  //     Db4 =  277.18,
  //     D4  =  293.66,
  //     Ds4 =  311.13, 
  //     Eb4 =  311.13,
  //     E4  =  329.63,
  //     F4  =  349.23,
  //     Fs4 =  369.99, 
  //     Gb4 =  369.99,
  //     G4  =  392,
  //     Gs4 =  415.3, 
  //     Ab4 =  415.3,
  //     A4  =  440,
  //     As4 =  466.16, 
  //     Bb4 =  466.16,
  //     B4  =  493.88,
  //     C5  =  523.25,
  //     Cs5 =  554.37, 
  //     Db5 =  554.37,
  //     D5  =  587.33,
  //     Ds5 =  622.25, 
  //     Eb5 =  622.25,
  //     E5  =  659.25,
  //     F5  =  698.46,
  //     Fs5 =  739.99, 
  //     Gb5 =  739.99,
  //     G5  =  783.99,
  //     Gs5 =  830.61, 
  //     Ab5 =  830.61,
  //     A5  =  880,
  //     As5 =  932.33, 
  //     Bb5 =  932.33,
  //     B5  =  987.77,
  //     C6  =  1046.5,
  //     Cs6 =  1108.73, 
  //     Db6 =  1108.73,
  //     D6  =  1174.66,
  //     Ds6 =  1244.51, 
  //     Eb6 =  1244.51,
  //     E6  =  1318.51,
  //     F6  =  1396.91,
  //     Fs6 =  1479.98, 
  //     Gb6 =  1479.98,
  //     G6  =  1567.98,
  //     Gs6 =  1661.22, 
  //     Ab6 =  1661.22,
  //     A6  =  1760,
  //     As6 =  1864.66, 
  //     Bb6 =  1864.66,
  //     B6  =  1975.53,
  //     C7  =  2093,
  //     Cs7 =  2217.46, 
  //     Db7 =  2217.46,
  //     D7  =  2349.32,
  //     Ds7 =  2489.02, 
  //     Eb7 =  2489.02,
  //     E7 =   2637.02,
  //     F7  =  2793.83,
  //     Fs7 =  2959.96, 
  //     Gb7 =  2959.96,
  //     G7  =  3135.96,
  //     Gs7 =  3322.44, 
  //     Ab7 =  3322.44,
  //     A7  =  3520,
  //     As7 =  3729.31, 
  //     Bb7 =  3729.31,
  //     B7  =  3951.07,
  //     C8  =  4186.01,
  //     Cs8 =  4434.92, 
  //     Db8 =  4434.92,
  //     D8  =  4698.63,
  //     Ds8 =  4978.03, 
  //     Eb8 =  4978.03,
  //     E8  =  5274.04,
  //     F8  =  5587.65,
  //     Fs8 =  5919.91,
  //     Gb8 =  5919.91,
  //     G8  =  6271.93,
  //     Gs8 =  6644.88,
  //     Ab8 =  6644.88,
  //     A8  =  7040,
  //     As8 =    7458.62,
  //     Bb8 =  7458.62,
  //     B8  =  7902.13
  // } Note;
};


#endif

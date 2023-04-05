#define LOAD_GFXFF

#ifdef LOAD_GFXFF // Only include the fonts if LOAD_GFXFF is defined in User_Setup.h

// Use these when printing or drawing text in GLCD and high rendering speed fonts

// Use the following when calling setFont()
//
// Reserved for GLCD font  // FF0
//

#define FSS09 &FreeSans7pt7b
#define FSS9 &FreeSans9pt7b
#define FSS12 &FreeSans12pt7b
#define FSS18 &FreeSans18pt7b
#define FSS24 &FreeSans24pt7b

#define FSSB9 &FreeSansBold9pt7b
#define FSSB12 &FreeSansBold12pt7b
#define FSSB18 &FreeSansBold18pt7b
#define FSSB24 &FreeSansBold24pt7b


#define FF017 &FreeSans7pt7b
#define FF17 &FreeSans9pt7b
#define FF18 &FreeSans12pt7b
#define FF19 &FreeSans18pt7b
#define FF20 &FreeSans24pt7b

#define FF21 &FreeSansBold9pt7b
#define FF22 &FreeSansBold12pt7b
#define FF23 &FreeSansBold18pt7b
#define FF24 &FreeSansBold24pt7b


#else // LOAD_GFXFF not defined so setup defaults to prevent error messages

#define FSSB9  1
#define FSSB12 1
#define FSSB18 1
#define FSSB24 1

#define FSSO9  1
#define FSSO12 1
#define FSSO18 1
#define FSSO24 1

#define FSSBO9  1
#define FSSBO12 1
#define FSSBO18 1
#define FSSBO24 1


#endif // LOAD_GFXFF

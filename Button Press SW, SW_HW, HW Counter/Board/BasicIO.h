/*******************************************************************
* BasicIO.h - Project Header file for BasicIO.c
*
* Todd Morton 10/15/2014
* V2.1
* Todd Morton 10/31/2015
********************************************************************/
#ifndef BIO_INCL
#define BIO_INCL
/********************************************************************
* Public Function Prototypes 
********************************************************************/
/********************************************************************
* BIOOpen() - Initialization routine for BasicIO()
********************************************************************/
void BIOOpen(void);

/********************************************************************
* BIORead() - Checks for a character received
*    return: ASCII character received or 0 if no character received
********************************************************************/
INT8C BIORead(void);     /* Reads received character, 0 if none */

/********************************************************************
* BIOGetChar() - Blocks until character is received
*    return: ASCII character
********************************************************************/
INT8C BIOGetChar(void);  /* Blocks until a character is received */

/********************************************************************
* BIOGetStrg() - Inputs a string and stores it into an array.
*
* Descritpion: A routine that inputs a character string to an array
*              until a carraige return is received or strglen is exceeded.
*              Only printable characters are recognized except carriage
*              return and backspace.
*              Backspace erases displayed character and array character.
*              A NULL is always placed at the end of the string.
*              All printable characters are echoed.
* Return value: 0 -> if ended with CR
*               1 -> if strglen exceeded.
* Arguments: *strg is a pointer to the string array
*            strglen is the max string length, includes CR/NULL.
********************************************************************/
INT8U BIOGetStrg(INT8U strglen,INT8C *const strg); /*input a string */

/********************************************************************
* BIOWrite() - Sends an ASCII character
*              Blocks as much as one character time
*    parameter: c is the ASCII character to be sent
********************************************************************/
void BIOWrite(INT8C c);  /* Send an ascii character */

/********************************************************************
* BIOPutStrg() - Sends a C string
*    parameter: strg is a pointer to the string
********************************************************************/
void BIOPutStrg(const INT8C *const strg);

/********************************************************************
* BIOOutDecByte() - Outputs the decimal value of a byte.
*    Parameters: bin is the byte to be sent,
*                lz is true if leading zeros are sent
********************************************************************/
void BIOOutDecByte (INT8U bin, INT8U lz);

/********************************************************************
* BIOOutDecHWord() - Outputs a decimal value of two bytes.
*    Parameters: bin is the half word to be sent,
*                lz is true if leading zeros are sent
********************************************************************/
void BIOOutDecHWord (INT16U bin, INT8U lz);   //writes a string of decimal

/********************************************************************
* BIOOutCRLF() - Outputs a carriage return and line feed.
*
********************************************************************/
void BIOOutCRLF(void);

/************************************************************************
* BIOOutHexByte() - Output one byte in hex.
* bin is the byte to be sent
*************************************************************************/
void BIOOutHexByte(INT8U bin);

/************************************************************************
* BIOOutHexHWord() - Output 16-bit word in hex.
* bin is the word to be sent
*************************************************************************/
void BIOOutHexHWord(INT16U bin);

/************************************************************************
* BIOOutHexWord() - Output 32-bit word in hex.
* bin is the word to be sent
*************************************************************************/
void BIOOutHexWord(INT32U bin);

/********************************************************************
* BIOHexStrgtoWord() - Converts a string of hex characters to a 32-bit
*                      word until NULL is reached.
* Return value: 0 -> if no error.
*               1 -> if string is too long for word.
*               2 -> if a non-hex character is in the string.
*               3 -> No characters in string. Started with NULL.
* Arguments: *strg is a pointer to the string array
*            *bin is the word that will hold the converted string.
********************************************************************/
INT8U BIOHexStrgtoWord(INT8C *const strg,INT32U *bin);
/*******************************************************************/
#endif

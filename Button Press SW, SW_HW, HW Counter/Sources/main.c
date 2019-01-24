/******************************************************************************
*   Realtime IO Demonstration
*   Detects and services an event on PORTA bit4 (SW2 press) using:
*   1) Software only
*   2) Hardware and software
*   3) Interrupt hardware only
*
* Anthony Needles, 10/29/2017
******************************************************************************/

#include "MCUType.h"
#include "BasicIO.h"
#include "K65TWR_GPIO.h"

#define IRQC_NONE 0
#define IRQC_REDGE 9

INT16U CalcChkSum(INT8U *startaddr, INT8U *endaddr);
void SoftwareCounter(void);
void SoftwareHardwareCounter(void);
void HardwareCounter(void);
void PORTA_IRQHandler(void);

const INT8C CharError[] = "\nERROR: Invalid input. Please enter an input as described below:\r\n";
const INT8C MenuPrompt[] = "\nPlease enter an input as described below:\r\n";
const INT8C CharOption1[] = "'s' - Demonstrate the software only counter.\r\n";
const INT8C CharOption2[] = "'b' - Demonstrate hardware and software combination counter.\r\n";
const INT8C CharOption3[] = "'h' - Demonstrate the interrupt hardware only.\r\n";
const INT8C SoftwarePrompt[] = "\nSoftware counter started. Press 'q' to return to the menu.\r\n";
const INT8C SoftwareHardwarePrompt[] = "\nSoftware/Hardware counter started. Press 'q' to return to the menu.\r\n";
const INT8C HardwarePrompt[] = "\nHardware counter started. Press 'q' to return to the menu.\r\n";

volatile INT16U hardware_count = 0; // Volatile data to be changed asynchronously

void main(void){

    INT8U *start_addr;
    INT8U *end_addr;
    INT32U lower_addr = 0x00000000u;
    INT32U upper_addr = 0x001FFFFFu;
    INT16U check_sum;
    INT8C user_char;
    INT8U valid_input;

    BIOOpen();
    start_addr = (void*)lower_addr;
    end_addr = (void*)upper_addr;
    check_sum = CalcChkSum(start_addr, end_addr);
    BIOPutStrg("\r\nCS: ");
    BIOOutHexWord(lower_addr);
    BIOPutStrg(" - ");
    BIOOutHexWord(upper_addr);
    BIOPutStrg(" ");
    BIOOutHexHWord(check_sum);
    BIOPutStrg("\r\n");

    while(1){
        BIOPutStrg(MenuPrompt);
        BIOPutStrg(CharOption1);
        BIOPutStrg(CharOption2);
        BIOPutStrg(CharOption3);

        valid_input = 0;
        while(!valid_input){
            user_char = BIOGetChar();
            if((user_char == 's') || (user_char == 'b') || (user_char == 'h')){
                valid_input = 1;
            } else {
                BIOPutStrg(CharError);
                BIOPutStrg(CharOption1);
                BIOPutStrg(CharOption2);
                BIOPutStrg(CharOption3);
            }
        }

        switch(user_char){
            case('s'):
                SoftwareCounter();
                break;
            case('b'):
                SoftwareHardwareCounter();
                break;
            case('h'):
                HardwareCounter();
                break;
            default:
                break;
        }
    }
}
/********************************************************************
* CalcChkSum - Performs checksum between to give addresses.
*
* Description:  A routine that will take two addresses and sums the 1 byte
*               contents in each address and stores into "check_sum."
*               A check for rollover after final address prevents terminal
*               bug  where the lower address is never actually equal to the
*               upper address
*
* Return value: INT16U Checksum value
*
* Arguments:    *startaddr is a pointer to the desired lower address
*               *endaddr is a pointer to the desired higher address
********************************************************************/
INT16U CalcChkSum(INT8U *startaddr, INT8U *endaddr){
    INT8U *low_addr = startaddr;
    INT8U *high_addr = endaddr;
    INT16U check_sum = 0;
    INT8U rollover_flag = 0;
    while((low_addr <= high_addr) && (!rollover_flag)){             // In order to combat terminal count bug when
        check_sum = check_sum + *low_addr;                          // upper address is 0xFFFFFFFF an additional
                                                                    // check is used for rollover
        if(low_addr != 0xFFFFFFFFu){
            low_addr++;
        } else {
            rollover_flag = 1;
        }
    }
    return check_sum;
}
/********************************************************************
* SoftwareCounter() - Counts SW2 presses
*
* Description:  A routine that watches for a posedge change on the
*               state of SW2, specified with the K65TWR GPIO support package
*               definition "SW2_INPUT", and counts the amount of edges.
*
* Return value: None
*
* Arguments:    None
********************************************************************/
void SoftwareCounter(void){
    BIOPutStrg(SoftwarePrompt);
    GpioSw2Init(IRQC_NONE); // Disables interrupts for this counter
    INT16U count = 0;
    INT8U last_sig = 1;
    while(1){                               // This loop catches positive edge changes on
        INT8U cur_sig = SW2_INPUT;          // the switch signal, else counter will increment
        if((!cur_sig) &&  (last_sig)){      // several times per press
            count++;
            BIOPutStrg("\rCount: ");
            BIOOutDecHWord(count,0);
        } else if(BIORead() == 'q'){
            BIOPutStrg("\r\n");
            return;
        } else {
        }
        last_sig = cur_sig;
    }
}
/********************************************************************
* SoftwareHardwareCounter() - Counts SW2 presses
*
* Description:  A routine that watches for the SW2 interrupt service
*               flag to be set, clears it, and counts up. Must enable interrupts
*               on PORTA, specifically uses rising edge interrupts.
*
* Return value: None
*
* Arguments:    None
********************************************************************/
void SoftwareHardwareCounter(void){
    BIOPutStrg(SoftwareHardwarePrompt);
    GpioSw2Init(IRQC_REDGE);    // Enables rising edge interrupts
    INT16U count = 0;
    SW2_CLR_ISF();
    while(1){                   // Counter will increment each time it sees the
        if(SW2_ISF){            // interrupt flag is set, and clears it to prevent
            SW2_CLR_ISF();      // non stop counts (due to flag remaining set)
            count++;
            BIOPutStrg("\rCount: ");
            BIOOutDecHWord(count,0);
        } else if(BIORead() == 'q'){
            BIOPutStrg("\r\n");
            return;
        } else {
        }
    }
}
/********************************************************************
* HardwareCounter() - Counts SW2 presses
*
* Description:  A routine that utilizes the Cortex M4's NVIC registers,
*               by first clearing the pending requests then enabling the requests
*               to be sent. The background of this process simply checks for the
*               menu return condition, while "PORTA_IRQHandler" is the foreground
*
* Return value: None
*
* Arguments:    None
********************************************************************/
void HardwareCounter(void){
    BIOPutStrg(HardwarePrompt);
    GpioSw2Init(IRQC_REDGE);    // Enables rising edge interrupts
    SW2_CLR_ISF();
    NVIC_ClearPendingIRQ(PORTA_IRQn);   // Interrupt request queue must be
    NVIC_EnableIRQ(PORTA_IRQn);         // cleared for PORTA
    INT16U last_count = 0;
    hardware_count = 0;
    while(1){                   // Background loop
        INT16U cur_count = hardware_count;
        if(BIORead() == 'q'){
            BIOPutStrg("\r\n");
            NVIC_DisableIRQ(PORTA_IRQn);
            return;
        } else if(cur_count != last_count){
            BIOPutStrg("\rCount: ");
            BIOOutDecHWord(hardware_count,0);
        } else{
        }
        last_count = cur_count;
    }
}
/********************************************************************
* PORTA_IRQHandler() - Handles PORTA's interrupt requests
*
* Description:  This routine counts the IRQ's that will be sent by a SW2
*               press (effectively counts each SW press).
*
* Return value: None
*
* Arguments:    None
********************************************************************/
void PORTA_IRQHandler(void){
    SW2_CLR_ISF();
    hardware_count++;   // Foreground loop triggered upon IRQ
}


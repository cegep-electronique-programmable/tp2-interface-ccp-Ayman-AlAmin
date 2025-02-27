//
//              Ayman Daboun
//
//            243-421-MA;gr.01   
//        MICROCONTROLEURS ET INTERFACES
//                  TP2
//              17/01/2025
//
#include "mcc_generated_files/mcc.h"

uint16_t trouver_CPPR (double); //Fonction pour trouver la valeur CPPR selon le duty cycle

int state = 0; //Etat poru determiner l'option choisi dans le menu

void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    PWM2_LoadDutyValue(trouver_CPPR(7.5)); //Mettre le moteur a la position neutre
    while (1)
    {
        switch(state){ //switchcase pour le menu
            case 0:
                printf("Choisir: Barrer ou débarrer \n \r( ) BARRER -- ( ) DEBARRER \n \r"); //Etat Neutre
                break;
            case 1:
                printf("Choisir: Barrer ou débarrer \n \r(X) BARRER -- ( ) DEBARRER \n \r"); //Etat Barrer
                break;
            case 2:
                printf("Choisir: Barrer ou débarrer \n \r( ) BARRER -- (X) DEBARRER \n \r"); //Etat Debarrer
                break; 
            default: 
                break;
        }
        while(!EUSART1_is_rx_ready()){}; 
        if (EUSART1_Read() == 'U'){ //Si U est appuye
            PWM2_LoadDutyValue(trouver_CPPR(4.5)); //Mettre le moteur a -90 deg
            state = 2; //Mettre etat menu a debarrer
        } else if (EUSART1_Read() == 'L'){
            PWM2_LoadDutyValue(trouver_CPPR(10.5)); //Mettre le moteur a +90 deg
            state = 1; //Mettre etat menu a barrer        
        } else if (state = 0) //En cas d'un bug ou le programme ne rend pas le moteur au neutre
        {
            PWM2_LoadDutyValue(trouver_CPPR(7.5)); //rendre neutre
        }
            
            
        }
    }

uint16_t trouver_CPPR (double CCPRinput) 
{
    uint16_t CCPRval; 
    double rappCycl; 
    rappCycl = CCPRinput / 100; //division du input par 100
    CCPRval = ((rappCycl * 0.019968) / 0.032768) * 1023; //introduction de rappCycl dans la formule de conversion CCPR
    return CCPRval; //retour de CCPR
    
}
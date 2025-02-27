//
//              Ayman Daboun
//
//            243-421-MA;gr.01   
//        MICROCONTROLEURS ET INTERFACES
//                  TP2.2
//              17/01/2025
//
#include "mcc_generated_files/mcc.h"


int t1 = 0;//variable utilisee pour le front montant
int t2 = 0; //variable utilisee pour le front descendant
int t3 = 0; //variable utilisee pour le 2e front montant
int step = 0; //variable utilisee pour les etapes
bool check = 0; //variable utilisee pour savoir quand mettre les donnees dans l'ecran

void capture(uint16_t);



void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    CCP2_SetCallBack(capture); //utliser la fonction capture comme routine d'interruption pour chaque front montant/descendant
    
    while (1)
    {
        if (check == 1)
        {
            float temps1 = t2 - t1; //calcul du temps haut
            float periode = t3 - t1; //calcul de la periode
            float dutyc = (temps1 / periode) * 100.0; //calcul du duty cycle + polarite
            
            if(dutyc > 50) //si le duty cycle est plus haut que 50%
            {
            printf("Pulse HauteL %f us\nPeriod: %f us\nDensite: %0.2f\nPolarite:Sud\n", temps1,periode,dutyc); 
            }
            else if (dutyc < 50) //si leduty cycle est plus bas que 50%
            {
            printf("Pulse HauteL %f us\nPeriod: %f us\nDensite: %0.2f\nPolarite:Nord\n", temps1,periode,dutyc);    
            }
            else //sinon
            {
                printf("Pulse HauteL %f us\nPeriod: %f us\nDensite: %0.2f\nPolarite:Aucune\n", temps1,periode,dutyc);
            }
            check = 0;
        }
        
    }
}


void capture(uint16_t captured) //fonction qui store les donnees capturees dans t1,t2,t3
{
    if (step == 0)
    {
        t1 = captured; //mettre la valeur capture sur t1
        CCP2CON = 0x04; //mettre falling edge
        step++; //passer a la prochain etape
    }
    else if (step == 1) 
    {
        t2 = captured;//mettre la valeur capture sur t2
        CCP2CON = 0x05; //mettre rising edge
        step++; //passer a la prochain etape
    }
    else if (step == 2)
    {
        t3 = captured;//mettre la valeur capture sur t3
        step = 0; //revenir a la premiere etape
        check = 1; //activer l'inscription des donnees sur l'ecran
        
    }
    
}

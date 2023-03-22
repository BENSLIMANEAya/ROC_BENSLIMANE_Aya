# include  < xc.h >  // librairie xc.h inclut tous les uC
# inclure  " IO.h "
# inclure  " PWM.h "
# inclure  " Robot.h "
# inclure  " ToolBox.h "
# inclure  " main.h "

# définir  PWMPER  40.0
 accélération de caractères non signés = 20 ;

void  InitPWM ( void ) {
    PTCON2bits. PCLKDIV = 0b000 ; // Diviser par 1
    PTPER = 100 * PWMPER ; // Période en pourcentage

    // Réglage PWM moteur 1 sur hacheur 1
    IOCON1bits. POLH = 1 ; // Haut = 1 et actif sur bas = 0
    IOCON1bits. SONDAGE = 1 ; // Élevé = 1
    IOCON1bits. PMOD = 0b01 ; // Définir le mode PWM sur Redondant
    FCLCON1 = 0x0003 ; // Désactive la gestion des fautes

    // Reglage PWM moteur 2 sur hacheur 6
    IOCON6bits. POLH = 1 ; // Élevé = 1
    IOCON6bits. SONDAGE = 1 ; // Élevé = 1
    IOCON6bits. PMOD = 0b01 ; // Définir le mode PWM sur Redondant
    FCLCON6 = 0x0003 ; // Désactive la gestion des fautes

    /* Activer le module PWM */
    PTCONbits. PTEN = 1 ;
}

/*
void PWMSetSpeed(float vitesseEnPourcents,int m)
{
    interrupteur (m){
        cas MOTEUR_GAUCHE :
                    robotState.vitesseGaucheCommandeCourante = vitesseEnPourcents;
                    si (robotState.vitesseGaucheCommandeCourante < 0)
                    {
                        MOTEUR_GAUCHE_L_PWM_ENABLE = 1 ; //Pilotage de la pin en mode pwm
                        MOTEUR_GAUCHE_H_PWM_ENABLE = 0 ; //Pilotage de la pin en mode IO
                        MOTEUR_GAUCHE_H_IO_OUTPUT = 1 ; //Mise à 1 de la broche
                    }
                    si (robotState.vitesseGaucheCommandeCourante >= 0)
                    {
                        MOTEUR_GAUCHE_H_PWM_ENABLE = 1 ; //Pilotage de la broche en mode PWM
                        MOTEUR_GAUCHE_L_PWM_ENABLE = 0 ; //Pilotage de la broche en mode PWM
                        MOTEUR_GAUCHE_L_IO_OUTPUT = 1 ; //Mise à 1 de la broche
                    }
                    MOTEUR_GAUCHE_DUTY_CYCLE = Abs(robotState.vitesseGaucheCommandeCourante*PWMPER);
                    casser;
        
        cas MOTEUR_DROIT :
                    robotState.vitesseDroiteCommandeCourante = vitesseEnPourcents;
                    si (robotState.vitesseDroiteCommandeCourante < 0)
                    {
                        MOTEUR_DROIT_L_PWM_ENABLE = 1 ; //Pilotage de la broche en mode PWM
                        MOTEUR_DROIT_H_PWM_ENABLE = 0 ; //Pilotage de la pin en mode IO
                        MOTEUR_DROIT_H_IO_OUTPUT = 1 ; //Mise à 1 de la broche
                    }
                    si (robotState.vitesseDroiteCommandeCourante >= 0)
                    {
                        MOTEUR_DROIT_H_PWM_ENABLE = 1 ; //Pilotage de la broche en mode PWM
                        MOTEUR_DROIT_L_PWM_ENABLE = 0 ; //Pilotage de la pin en mode IO
                        MOTEUR_DROIT_L_IO_OUTPUT = 1 ; //Mise à 1 de la broche
                    }
                    MOTEUR_DROIT_DUTY_CYCLE = Abs(robotState.vitesseDroiteCommandeCourante*PWMPER);
                    casser;
    }
}
 */

void  PWMUpdateSpeed ​​() {
    // Cette fonction est appelée sur timer et permet de suivre des rampes d'accélération
    if (robotState. vitesseDroiteCommandeCourante < robotState. vitesseDroiteConsigne )
        robotState. vitesseDroiteCommandeCourante = Min (robotState. vitesseDroiteCommandeCourante + accélération, robotState. vitesseDroiteConsigne );
    if (robotState. vitesseDroiteCommandeCourante > robotState. vitesseDroiteConsigne )
        robotState. vitesseDroiteCommandeCourante = Max (robotState. vitesseDroiteCommandeCourante - accélération, robotState. vitesseDroiteConsigne );

    if (robotState. vitesseDroiteCommandeCourante > 0 ) {
        MOTEUR_DROIT_L_PWM_ENABLE = 0 ; // pilotage de la broche en mode IO
        MOTEUR_DROIT_L_IO_OUTPUT = 1 ; // Mise à 1 de la broche
        MOTEUR_DROIT_H_PWM_ENABLE = 1 ; // Pilotage de la broche en mode PWM
    } sinon {
        MOTEUR_DROIT_H_PWM_ENABLE = 0 ; // pilotage de la broche en mode IO
        MOTEUR_DROIT_H_IO_OUTPUT = 1 ; // Mise à 1 de la broche
        MOTEUR_DROIT_L_PWM_ENABLE = 1 ; // Pilotage de la broche en mode PWM
    }

    MOTEUR_DROIT_DUTY_CYCLE = Abs (robotState. vitesseDroiteCommandeCourante * PWMPER);

    if (robotState. vitesseGaucheCommandeCourante < robotState. vitesseGaucheConsigne )
        robotState. vitesseGaucheCommandeCourante = Min (robotState. vitesseGaucheCommandeCourante + accélération, robotState. vitesseGaucheConsigne );
    if (robotState. vitesseGaucheCommandeCourante > robotState. vitesseGaucheConsigne )
        robotState. vitesseGaucheCommandeCourante = Max (robotState. vitesseGaucheCommandeCourante - accélération, robotState. vitesseGaucheConsigne );

    if (robotState. vitesseGaucheCommandeCourante > 0 ) {
        MOTEUR_GAUCHE_L_PWM_ENABLE = 0 ; // pilotage de la broche en mode IO
        MOTEUR_GAUCHE_L_IO_OUTPUT = 1 ; // Mise à 1 de la broche
        MOTEUR_GAUCHE_H_PWM_ENABLE = 1 ; // Pilotage de la broche en mode PWM
    } sinon {
        MOTEUR_GAUCHE_H_PWM_ENABLE = 0 ; // pilotage de la broche en mode IO
        MOTEUR_GAUCHE_H_IO_OUTPUT = 1 ; // Mise à 1 de la broche
        MOTEUR_GAUCHE_L_PWM_ENABLE = 1 ; // Pilotage de la broche en mode PWM
    }
    MOTEUR_GAUCHE_DUTY_CYCLE = Abs (robotState. vitesseGaucheCommandeCourante * PWMPER);
}

void  PWMSetSpeedConsigne ( float vitesseEnPourcents, char moteur) {
    interrupteur (moteur) {
        cas MOTEUR_GAUCHE :
            robotState. vitesseGaucheConsigne = vitesseEnPourcents;
            casser ;
        cas MOTEUR_DROIT :
            robotState. vitesseDroiteConsigne = -vitesseEnPourcents;
            casser ;
    }
}

      

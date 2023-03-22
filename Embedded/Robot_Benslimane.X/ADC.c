# inclure  < xc.h >
# inclure  " ADC.h "
# inclure  " main.h "


 caractère non signé ADCResultIndex = 0 ;
 ADCResult int non signé  statique [ 5 ] ;
 caractère non signé ADCConversionFinishedFlag ;

/* ************************************************ ****************************************************** */
// Configuration ADC
/* ************************************************ ****************************************************** */
annuler  InitADC1 ( annuler )
{
// cf. Manuel de référence ADC page 47

// Configuration en mode 12 bits mono canal ADC avec conversions successives sur 4 entrées
/* ************************************************ ********** */
// AD1CON1
/* ************************************************ ********** */
AD1CON1bits. ADON = 0 ; // Module ADC OFF ? pendentif la config
AD1CON1bits. AD12B = 1 ; // 0 : 10bits ? 1 : 12bits
AD1CON1bits. FORME = 0b00 ; // 00 = Entier (DOUT = 0000 dddd dddd dddd)
AD1CON1bits. ASAM = 0 ; // 0 = L'échantillonnage commence lorsque le bit SAMP est défini
AD1CON1bits. SSRC = 0b111 ; // 111 = Le compteur interne termine l'échantillonnage et démarre la conversion (conversion automatique)

/* ************************************************ ********** */
// AD1CON2
/* ************************************************ ********** */
AD1CON2bits. VCFG = 0b000 ; // 000 : Référence Tension = AVDD AVss
AD1CON2bits. CSCNA = 1 ; // 1 : Activer le balayage des chaînes
AD1CON2bits. CHPS = 0b00 ; // Convertit CH0 uniquement
AD1CON2bits. SMPI = 4 ; // n+1 conversions successives avant interruption
AD1CON2bits. ALTS = 0 ;
AD1CON2bits. BUFM = 0 ;
/* ************************************************ ********** */
// AD1CON3
/* ************************************************ ********** */
AD1CON3bits. ADRC = 0 ; // L'horloge ADC est dérivée de l'horloge système
AD1CON3bits. ADCS = 15 ; // Horloge de conversion ADC TAD = TCY * (ADCS + 1)
AD1CON3bits. SAMC = 15 ; // Temps d'échantillonnage automatique

/* ************************************************ ********** */
// AD1CON4
/* ************************************************ ********** */
AD1CON4bits. ADDMAEN = 0 ; // DMA n'est pas utilisé

/* ************************************************ ********** */
// Configuration des ports
/* ************************************************ ********** */
// CAN utilisé : 16(G9)-11(C11)-6(C0)
ANSELCbits. ANSC0 = 1 ;
ANSELCbits. ANSC11 = 1 ;
ANSELGbits. ANSG9 = 1 ;
ANSELEbits. ANSE15 = 1 ;
ANSELBbits. ANSB1 = 1 ;

Bits AD1CSSL. CSS6 = 1 ; // Activer AN6 pour l'analyse
Bits AD1CSSL. CSS11 = 1 ; // Activer AN11 pour l'analyse
AD1CSSHbits. CSS16 = 1 ; // Activer AN16 pour l'analyse
Bits AD1CSSL. CSS15 = 1 ; // 
Bits AD1CSSL. CSS3 = 1 ; // 

/* Attribuer les entrées MUXA */
AD1CHS0bits. CH0SA = 0 ; // Bits CH0SA ignorés pour la sélection d'entrée CH0 +ve
AD1CHS0bits. CH0NA = 0 ; // Sélectionnez VREF- pour l'entrée CH0 -ve

IFS0bits. AD1IF = 0 ; // Efface le bit d'indicateur d'interruption A/D
IEC0bits. AD1IE = 1 ; // Activer l'interruption A/D
AD1CON1bits. ADON = 1 ; // Activer le convertisseur A/N
}

/* C'est la routine d'interruption ADC */
void  __attribute__ ((interruption, no_auto_psv)) _AD1Interrupt( void )
{
IFS0bits. AD1IF = 0 ;
ADCResult[ 0 ] = ADC1BUF0 ; // Lit le résultat de la conversion de l'entrée AN-scan 1
ADCResult[ 1 ] = ADC1BUF1 ; // Lire le résultat de la conversion AN3
ADCResult[ 2 ] = ADC1BUF2 ; // Lire le résultat de la conversion AN5
ADCResult[ 3 ] = ADC1BUF3 ; // Lire le résultat de la conversion AN3
ADCResult[ 4 ] = ADC1BUF4 ; // Lire le résultat de la conversion AN5
ADCConversionFinishedFlag = 1 ;
}

annuler  ADC1StartConversionSequence ()
{
AD1CON1bits. SAMP = 1 ; // Lance une acquisition ADC
}

 entier non signé * ADCGetResult ( void )
{
renvoie ADCResult ;
}

 caractère  non signé ADCIsConversionFinished ( void )
{
renvoie ADCConversionFinishedFlag ;
}

annuler  ADCClearConversionFinishedFlag ( annuler )
{
ADCConversionFinishedFlag = 0 ;
}





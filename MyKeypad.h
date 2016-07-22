/* CR�DITS
 * MyKeypad
 * Cr�� par Jacques Bellavance, le 25 juin 2016
 * Ce code est du domaine public
 */

/* MONTAGE
 * MyKeypad permet d'utiliser jusqu'� 16 interrupteurs
 * qui peuvent �tre lus sur une broche d'entr�e analogue d'un Arduino.
 * +5V-----Rpullup-----+------+-------+--- ... ---+-----A10
 *                    1nF    SW0     SW1   ...   SWn
 *                     |     R0      R1    ...   Rn
 * GND-----------------+------+-------+--- ... ---+
 */

/* INTRODUCTION
 * La plage des valeurs possibles pour une broche analogue de l'Arduino est de 0 � 1023.
 * Pour un montage avec n interrupteurs, la plage 0..1024 est divis�e en n segments.
 * Le centre de chaque segment est la cible vers laquelle la r�sistance choisie doit tendre.
 * Les r�sistances choisies font partie de la s�rie E12 et sont suppos�es � +- 5%
 * (voir :http://www.positron-libre.com/cours/electronique/resistances/serie-resistance.php)
 *
 * NOTE :
 * La librairie accepte des montages avec jusqu'� 16 interrupteurs.
 * Au-del�, il faut utiliser des r�sistances de la s�rie E48 avec des pr�cisions de +- 2%
 * ou de la s�rie E96 avec des pr�cisions de +- 1%
 * Pour les personnes int�ress�es � changer le code pour ces montages :
 * - modifier � nearestResistor() � dans MyKeypad.cpp.
 * - modifier � MYresistors[XX] � ici.
 */

#ifndef MyKeypad_h
#define MyKeypad_h

#include "Arduino.h"

class MyKeypad {
  public:
    MyKeypad(int inputPin, int butonCount);         //CONSTRUCTEUR
	bool keyPressed();                              //Indique si un interrupteur est pr�sentement ferm�
	int getKey();                                   //Retourne le num�ro (0..n) de l'interrupteur
	int getKey(int debounceLimit);                  //Retourne le num�ro (0..n) de l'interrupteur avec valeur de d�lai de rebond
	int getKeyAndWaitForRelease();                  //Retourne le num�ro (0..n) de l'interrupteur et attend qu'il soit rel�ch�
	void calculateResistorsValues();                //Calcule les r�sistances optimales pour le montage avec une r�sistance de rappel de 10 KOhms
	void calculateResistorsValues(double pullup);   //Calcule les r�sistances optimales pour le montage avec une r�sistance de rappel sp�cifique
	double getResistorValue(int i);                 //Retourne la valeur de la r�sistance Ri
	double getRealPullup();                         //Retourne la vraie valeur de la r�sistance de rappel utilis�e pour les calculs
  private:
	double nearestResistor(double target);          //Retourne la valeur de la r�sistance de la s�rie E12 la plus rapproch�e de la valeur cible
    int MYinputPin;                                 //
	int MYbuttonCount;
    float MYbinSize;
	int MYanswer;
	int MYdebounceLimit = 50;
	double MYresistors[16];
	double MYpullup = 10000.0;
};

#endif

#ifndef WEAPON_H
#define WEAPON_H

/**
* @class Weapon
* @brief Holds the weapon information
*
* @author Bryce
* @version 01
* @date May 2021
*
*
**/
class TNAH_API Weapon {
public:

        /**
        * @brief default constructor
        */
    Weapon(){}

    bool firingWeapon = false;
    bool canFireWeapon = true;
    bool isEnemy = false;
    float lastFireTime = 0;

};


#endif //WEAPON_H

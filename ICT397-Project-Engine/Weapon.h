#ifndef WEAPON_H
#define WEAPON_H


class Weapon {
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

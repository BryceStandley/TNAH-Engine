#pragma once
#include "Dog.h"
#include "TNAH/Scene/Components/AI/StateMachine.h"
#include "TNAH/Core/Singleton.h"

namespace tnah
{
    /**
     * @class  GlobalDog
     *
     * @brief  A class that represents the Global state of the Dog character. Inherits from the State class
     *
     * @author Christopher Logan
     * @date   2/11/2021
     */
    class GlobalDog : public State<Dog>
    {
    public:

        /**
         * @fn  Enter
         *
         * @brief virtual function that represents the enter point of the state
         *
         * @author Christopher Logan
         * @date   2/11/2021
         *
         * @param owner - pointer to the entity class
         */
        virtual void Enter(Dog* owner) override;

        /**
         * @fn  Execute
         *
         * @brief virtual function that represents the execute stage of the state
         *
         * @author Christopher Logan
         * @date   2/11/2021
         *
         * @param owner - pointer to the entity class
         */
        virtual void Execute(Dog* owner) override;

        /**
        * @fn  Exit
        *
        * @brief virtual function that represents the execute stage of the state
        *
        * @author Christopher Logan
        * @date   2/11/2021
        *
        * @param owner - pointer to the entity class
        */
        virtual void Exit(Dog* owner) override;
    };

    /**
     * @class  PosArousalPosValenceDog
     *
     * @brief  A class that represents the PosArousalPosValenceDog state of the Dog character. Inherits from the State class
     *
     * @author Christopher Logan
     * @date   2/11/2021
     */
    class PosArousalPosValenceDog : public State<Dog>
    {
    public:

        /**
         * @fn  Enter
         *
         * @brief virtual function that represents the enter point of the state
         *
         * @author Christopher Logan
         * @date   2/11/2021
         *
         * @param owner - pointer to the entity class
         */
        virtual void Enter(Dog* owner) override;

        /**
         * @fn  Execute
         *
         * @brief virtual function that represents the execute stage of the state
         *
         * @author Christopher Logan
         * @date   2/11/2021
         *
         * @param owner - pointer to the entity class
         */
        virtual void Execute(Dog* owner) override;

        /**
        * @fn  Exit
        *
        * @brief virtual function that represents the execute stage of the state
        *
        * @author Christopher Logan
        * @date   2/11/2021
        *
        * @param owner - pointer to the entity class
        */
        virtual void Exit(Dog* owner) override;
    };

    /**
     * @class  NegArousalPosValenceDog
     *
     * @brief  A class that represents the NegArousalPosValenceDog state of the Dog character. Inherits from the State class
     *
     * @author Christopher Logan
     * @date   2/11/2021
     */
    class NegArousalPosValenceDog : public State<Dog>
    {
    public:

        /**
         * @fn  Enter
         *
         * @brief virtual function that represents the enter point of the state
         *
         * @author Christopher Logan
         * @date   2/11/2021
         *
         * @param owner - pointer to the entity class
         */
        virtual void Enter(Dog* owner) override;

        /**
         * @fn  Execute
         *
         * @brief virtual function that represents the execute stage of the state
         *
         * @author Christopher Logan
         * @date   2/11/2021
         *
         * @param owner - pointer to the entity class
         */
        virtual void Execute(Dog* owner) override;

        /**
        * @fn  Exit
        *
        * @brief virtual function that represents the execute stage of the state
        *
        * @author Christopher Logan
        * @date   2/11/2021
        *
        * @param owner - pointer to the entity class
        */
        virtual void Exit(Dog* owner) override;
    };


    /**
     * @class  NegArousalNegValenceDog
     *
     * @brief  A class that represents the NegArousalNegValenceDog state of the Dog character. Inherits from the State class
     *
     * @author Christopher Logan
     * @date   2/11/2021
     */
    class NegArousalNegValenceDog : public State<Dog>
    {
    public:

        /**
         * @fn  Enter
         *
         * @brief virtual function that represents the enter point of the state
         *
         * @author Christopher Logan
         * @date   2/11/2021
         *
         * @param owner - pointer to the entity class
         */
        virtual void Enter(Dog* owner) override;

        /**
         * @fn  Execute
         *
         * @brief virtual function that represents the execute stage of the state
         *
         * @author Christopher Logan
         * @date   2/11/2021
         *
         * @param owner - pointer to the entity class
         */
        virtual void Execute(Dog* owner) override;

        /**
        * @fn  Exit
        *
        * @brief virtual function that represents the execute stage of the state
        *
        * @author Christopher Logan
        * @date   2/11/2021
        *
        * @param owner - pointer to the entity class
        */
        virtual void Exit(Dog* owner) override;
    };

    /**
     * @class  PosArousalNegValenceDog
     *
     * @brief  A class that represents the PosArousalNegValenceDog state of the Dog character. Inherits from the State class
     *
     * @author Christopher Logan
     * @date   2/11/2021
     */
    class PosArousalNegValenceDog : public State<Dog>
    {
    public:

        /**
         * @fn  Enter
         * 
         * @brief virtual function that represents the enter point of the state  
         * 
         * @author Christopher Logan
         * @date   2/11/2021
         * 
         * @param owner - pointer to the entity class
         */
        virtual void Enter(Dog* owner) override;

        /**
         * @fn  Execute
         * 
         * @brief virtual function that represents the execute stage of the state  
         * 
         * @author Christopher Logan
         * @date   2/11/2021
         * 
         * @param owner - pointer to the entity class
         */
        virtual void Execute(Dog* owner) override;

        /**
        * @fn  Exit
        * 
        * @brief virtual function that represents the execute stage of the state 
        * 
        * @author Christopher Logan
        * @date   2/11/2021
        * 
        * @param owner - pointer to the entity class
        */
        virtual void Exit(Dog* owner) override;
    };

    typedef  singleton<NegArousalNegValenceDog> SadStateDog;
    typedef  singleton<NegArousalPosValenceDog> ChillStateDog;
    typedef  singleton<PosArousalNegValenceDog> AngryStateDog;
    typedef  singleton<PosArousalPosValenceDog> HappyStateDog;
    typedef  singleton<GlobalDog> GlobalStateDog;
}


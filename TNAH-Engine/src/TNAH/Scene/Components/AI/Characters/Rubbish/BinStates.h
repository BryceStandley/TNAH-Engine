#pragma once
#include "Bin.h"
#include "TNAH/Scene/Components/AI/Character.h"
#include "TNAH/Core/Singleton.h"

namespace tnah
{
    /**
     * @class  GlobalBin
     *
     * @brief  A class that represents the Global state of the Bin character. Inherits from the State class
     *
     * @author Dylan Blereau
     * @date   2/11/2021
     */
    class GlobalBin : public State<Bin>
    {
    public:

        /**
          * @fn  Enter
          *
          * @brief virtual function that represents the enter point of the state
          *
          * @author Dylan Blereau
          * @date   2/11/2021
          *
          * @param owner - pointer to the entity class
          */
        virtual void Enter(Bin* owner) override;

        /**
         * @fn  Execute
         *
         * @brief virtual function that represents the execute stage of the state
         *
         * @author Dylan Blereau
         * @date   2/11/2021
         *
         * @param owner - pointer to the entity class
         */
        virtual void Execute(Bin* owner) override;

        /**
        * @fn  Exit
        *
        * @brief virtual function that represents the execute stage of the state
        *
        * @author Dylan Blereau
        * @date   2/11/2021
        *
        * @param owner - pointer to the entity class
        */
        virtual void Exit(Bin* owner) override;
    };


    /**
    * @class  PosArousalPosValenceBin
    *
    * @brief  A class that represents the PosArousalPosValenceBin state of the Bin character. Inherits from the State class
    *
    * @author Dylan Blereau
    * @date   2/11/2021
    */
    class PosArousalPosValenceBin : public State<Bin>
    {
    public:

        /**
         * @fn  Enter
         *
         * @brief virtual function that represents the enter point of the state
         *
         * @author Dylan Blereau
         * @date   2/11/2021
         *
         * @param owner - pointer to the entity class
         */
        virtual void Enter(Bin* owner) override;

        /**
         * @fn  Execute
         *
         * @brief virtual function that represents the execute stage of the state
         *
         * @author Dylan Blereau
         * @date   2/11/2021
         *
         * @param owner - pointer to the entity class
         */
        virtual void Execute(Bin* owner) override;

        /**
        * @fn  Exit
        *
        * @brief virtual function that represents the execute stage of the state
        *
        * @author Dylan Blereau
        * @date   2/11/2021
        *
        * @param owner - pointer to the entity class
        */
        virtual void Exit(Bin* owner) override;
    };

    /**
   * @class  NegArousalPosValenceBin
   *
   * @brief  A class that represents the NegArousalPosValenceBin state of the Bin character. Inherits from the State class
   *
   * @author Dylan Blereau
   * @date   2/11/2021
   */
    class NegArousalPosValenceBin : public State<Bin>
    {
    public:

        /**
          * @fn  Enter
          *
          * @brief virtual function that represents the enter point of the state
          *
          * @author Dylan Blereau
          * @date   2/11/2021
          *
          * @param owner - pointer to the entity class
          */
        virtual void Enter(Bin* owner) override;

        /**
         * @fn  Execute
         *
         * @brief virtual function that represents the execute stage of the state
         *
         * @author Dylan Blereau
         * @date   2/11/2021
         *
         * @param owner - pointer to the entity class
         */
        virtual void Execute(Bin* owner) override;

        /**
        * @fn  Exit
        *
        * @brief virtual function that represents the execute stage of the state
        *
        * @author Dylan Blereau
        * @date   2/11/2021
        *
        * @param owner - pointer to the entity class
        */
        virtual void Exit(Bin* owner) override;
    };

    /**
   * @class  NegArousalNegValenceBin
   *
   * @brief  A class that represents the NegArousalNegValenceBin state of the Bin character. Inherits from the State class
   *
   * @author Dylan Blereau
   * @date   2/11/2021
   */
    class NegArousalNegValenceBin : public State<Bin>
    {
    public:

        /**
         * @fn  Enter
         *
         * @brief virtual function that represents the enter point of the state
         *
         * @author Dylan Blereau
         * @date   2/11/2021
         *
         * @param owner - pointer to the entity class
         */
        virtual void Enter(Bin* owner) override;

        /**
         * @fn  Execute
         *
         * @brief virtual function that represents the execute stage of the state
         *
         * @author Dylan Blereau
         * @date   2/11/2021
         *
         * @param owner - pointer to the entity class
         */
        virtual void Execute(Bin* owner) override;

        /**
        * @fn  Exit
        *
        * @brief virtual function that represents the execute stage of the state
        *
        * @author Dylan Blereau
        * @date   2/11/2021
        *
        * @param owner - pointer to the entity class
        */
        virtual void Exit(Bin* owner) override;
    };

    /**
   * @class  PosArousalNegValenceBin
   *
   * @brief  A class that represents the PosArousalNegValenceBin state of the Bin character. Inherits from the State class
   *
   * @author Dylan Blereau
   * @date   2/11/2021
   */
    class PosArousalNegValenceBin : public State<Bin>
    {
    public:

        /**
         * @fn  Enter
         *
         * @brief virtual function that represents the enter point of the state
         *
         * @author Dylan Blereau
         * @date   2/11/2021
         *
         * @param owner - pointer to the entity class
         */
        virtual void Enter(Bin* owner) override;

        /**
         * @fn  Execute
         *
         * @brief virtual function that represents the execute stage of the state
         *
         * @author Dylan Blereau
         * @date   2/11/2021
         *
         * @param owner - pointer to the entity class
         */
        virtual void Execute(Bin* owner) override;

        /**
        * @fn  Exit
        *
        * @brief virtual function that represents the execute stage of the state
        *
        * @author Dylan Blereau
        * @date   2/11/2021
        *
        * @param owner - pointer to the entity class
        */
        virtual void Exit(Bin* owner) override;
    };
    
    typedef  singleton<NegArousalNegValenceBin> SadStateBin;
    typedef  singleton<NegArousalPosValenceBin> ChillStateBin;
    typedef  singleton<PosArousalNegValenceBin> AngryStateBin;
    typedef  singleton<PosArousalPosValenceBin> HappyStateBin;
    typedef  singleton<GlobalBin> GlobalStateBin;
}

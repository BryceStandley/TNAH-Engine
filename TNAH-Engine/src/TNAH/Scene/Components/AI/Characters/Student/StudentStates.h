#pragma once
#include "Student.h"
#include "TNAH/Core/Singleton.h"

namespace tnah
{
    /**
     * @class  GlobalStudent
     *
     * @brief  A class that represents the Global state of the Student character. Inherits from the State class
     *
     * @author Dylan Blereau
     * @date   2/11/2021
     */
    class GlobalStudent : public State<Student>
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
        virtual void Enter(Student* owner) override;

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
        virtual void Execute(Student* owner) override;

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
        virtual void Exit(Student* owner) override;
    };



    /**
    * @class  PosArousalPosValenceStudent
    *
    * @brief  A class that represents the PosArousalPosValenceStudent state of the Student character. Inherits from the State class
    *
    * @author Dylan Blereau
    * @date   2/11/2021
    */
    class PosArousalPosValenceStudent : public State<Student>
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
        virtual void Enter(Student* owner) override;

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
        virtual void Execute(Student* owner) override;

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
        virtual void Exit(Student* owner) override;
    };


    /**
    * @class  NegArousalPosValenceStudent
    *
    * @brief  A class that represents the NegArousalPosValenceStudent state of the Student character. Inherits from the State class
    *
    * @author Dylan Blereau
    * @date   2/11/2021
    */
    class NegArousalPosValenceStudent : public State<Student>
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
        virtual void Enter(Student* owner) override;

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
        virtual void Execute(Student* owner) override;

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
        virtual void Exit(Student* owner) override;
    };


    /**
    * @class  NegArousalNegValenceStudent
    *
    * @brief  A class that represents the NegArousalNegValenceStudent state of the Student character. Inherits from the State class
    *
    * @author Dylan Blereau
    * @date   2/11/2021
    */
    class NegArousalNegValenceStudent : public State<Student>
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
        virtual void Enter(Student* owner) override;

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
        virtual void Execute(Student* owner) override;

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
        virtual void Exit(Student* owner) override;
    };


    /**
    * @class  PosArousalNegValenceStudent
    *
    * @brief  A class that represents the PosArousalNegValenceStudent state of the Student character. Inherits from the State class
    *
    * @author Dylan Blereau
    * @date   2/11/2021
    */
    class PosArousalNegValenceStudent : public State<Student>
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
        virtual void Enter(Student* owner) override;

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
        virtual void Execute(Student* owner) override;

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
        virtual void Exit(Student* owner) override;
    };

    typedef  singleton<NegArousalNegValenceStudent> SadStateStudent;
    typedef  singleton<NegArousalPosValenceStudent> ChillStateStudent;
    typedef  singleton<PosArousalNegValenceStudent> PissedOffStateStudent;
    typedef  singleton<PosArousalPosValenceStudent> HappyStateStudent;
    typedef  singleton<GlobalStudent> GlobalStateStudent;
}
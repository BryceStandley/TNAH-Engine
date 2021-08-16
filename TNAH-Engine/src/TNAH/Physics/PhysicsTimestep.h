#pragma once

namespace tnah
{
    class PhysicsTimestep
    {
    public:
        PhysicsTimestep(float framerate)
            : m_TotalTime(0), m_SimSpeed(1.0f/framerate), m_Accumulator(0)
        {
        }

        inline void AddFrameTime(const float frameTime) { m_Accumulator += frameTime; }

        inline bool FixedUpdateCheck() const { return m_Accumulator >= m_SimSpeed; }

        inline void Update() { m_TotalTime += m_SimSpeed; m_Accumulator -= m_SimSpeed; }

        float GetAplha() const { return m_Accumulator / m_SimSpeed; }

        void SetAccumulator(const float a) { m_Accumulator = a; }
        float GetAccumulator() const { return m_Accumulator; }

        void SetTotalTime(const float time) { m_TotalTime = time; }
        float GetTotalTime() const { return m_TotalTime; }

        void SetSimulationSpeed(const float speed) { m_SimSpeed = speed; }
        void SetSimulationFrameRate(float frames) { m_SimSpeed = 1.0f / frames; }
        float GetSimulationSpeed() const { return m_SimSpeed; }

    private:
        float m_TotalTime;
        float m_SimSpeed;
        float m_Accumulator;
    };
}


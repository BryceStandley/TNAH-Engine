#pragma once
#include "TNAH/Core/Core.h"
#include "TNAH/Scene/Components/AudioComponents.h"
#include "Platform/IrrKlang/Klang.h"

namespace tnah
{
    class Audio
    {
    public:
        static bool Init();
        static void Shutdown();
        static bool SetListener(TransformComponent &transforms);
        static bool Add3DAudioSource(AudioSource3D &sound);
        static bool UpdateAudioSource(AudioSource3D &sound);
        static bool PlayAudioSource(AudioSource3D& sound, TransformComponent &transforms);
        static void Update();
        static void UpdateSound(AudioSource3D& sound, TransformComponent &transforms);
        static bool Active();
    private:
        static AudioAPI * m_AudioEngine;
    };
};
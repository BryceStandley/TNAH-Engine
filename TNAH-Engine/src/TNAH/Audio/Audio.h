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
        static bool AddAudioSource(AudioSource &sound);
        static bool UpdateAudioSource(AudioSource &sound);
        //static bool PlayAudioSource(AudioSource3D& sound, TransformComponent &transforms);
        static void OnUpdate();
        static void UpdateSound(AudioSource& sound, TransformComponent &transforms);
        static bool Active();
        static void Clear();
    private:
        static AudioAPI * m_AudioEngine;
    };
};
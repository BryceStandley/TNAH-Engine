#include "tnahpch.h"
#include "Audio.h"

namespace tnah
{
    AudioAPI * Audio::m_AudioEngine = new Klang();

    void Audio::Shutdown()
    {
        printf("This is called");
        delete m_AudioEngine;
        m_AudioEngine = nullptr;
    }

    bool Audio::Init()
    {
        if(m_AudioEngine)
            return true;
        else
            return false;
    }
    
    bool Audio::SetListener(TransformComponent &transform)
    {
        return m_AudioEngine->SetListener(transform);
    }
    bool Audio::Add3DAudioSource(AudioSource3D &sound)
    {
        return m_AudioEngine->Add3DAudioSource(sound);
    }
    bool Audio::UpdateAudioSource(AudioSource3D &sound)
    {
        return m_AudioEngine->UpdateAudioSource(sound);
    }
    bool Audio::PlayAudioSource(AudioSource3D& sound, TransformComponent &transform)
    {
        return m_AudioEngine->PlayAudioSource(sound, transform);
    }
    void Audio::Update()
    {
        m_AudioEngine->Update();
    }
    
    void Audio::UpdateSound(AudioSource3D& sound, TransformComponent &transform)
    {
        m_AudioEngine->UpdateSound(sound, transform);
    }
    
    bool Audio::Active()
    {
        return m_AudioEngine->Active();
    }
}
#pragma once
#include "TNAH/Audio/AudioAPI.h"
#pragma warning(push, 0)
#include <IrrKlang/irrKlang.h>
#include <vector>
#include <unordered_map>
#include <string>
#pragma warning(pop)

typedef std::pair<u_int, irrklang::ISoundSource*> AudioSourcePair;
typedef std::unordered_map<std::string, irrklang::ISoundSource*> AudioSources;
typedef std::vector<irrklang::ISound*> AudioPlaying;
typedef std::vector<std::string> AudioKeys;

namespace  tnah
{
    class Klang final : public AudioAPI
    {
    public:
        Klang();
        virtual ~Klang();

        bool SetListener(TransformComponent &transform) const override;//Updated to take trasnform, look = foward
        bool AddAudioSource(AudioSourceComponent&sound) override;
        bool UpdateAudioSource(AudioSourceComponent&sound) override;
        void OnUpdate() override;
        void UpdateSound(AudioSourceComponent& sound, TransformComponent &transform) override;
        bool Active() const override {return m_Engine;}
        void Clear() override;
        
    private:
        bool PlayAudioSource(AudioSourceComponent& sound, TransformComponent &transform);
        AudioSources m_Source;
        AudioPlaying m_Playing;
        AudioKeys m_Keys;
        irrklang::ISoundEngine* m_Engine;
    };    
};


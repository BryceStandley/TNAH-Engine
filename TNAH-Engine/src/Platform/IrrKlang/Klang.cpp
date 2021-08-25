﻿#include "tnahpch.h"
#include "Klang.h"
#include "TNAH/Core/Math.h"

namespace tnah
{
    Klang::Klang() : m_Engine(irrklang::createIrrKlangDevice())
    {
        
    }
    
    Klang::~Klang()
    {
        m_Playing.erase(m_Playing.begin(), m_Playing.end());
        m_Source.erase(m_Source.begin(), m_Source.end());

        //Make sure it is gonzo
        delete m_Engine;
        m_Engine = nullptr;
    }

    bool Klang::SetListener(TransformComponent &transform) const
    {
        if(m_Engine)
        {
            m_Engine->setListenerPosition(Math::ConvertVec3ToVec3df(transform.Position),
                Math::ConvertVec3ToVec3df(transform.Forward), irrklang::vec3df(0, 0, 0),
                Math::ConvertVec3ToVec3df(transform.Up));
            
            return true;
        }
        else
            return false;
    }
    
    bool Klang::Add3DAudioSource(AudioSource3D& sound)
    {
        irrklang::ISoundSource* source(m_Engine ->addSoundSourceFromFile(sound.m_File.RelativeDirectory.c_str()));
        
        if(source)
        {
            m_Source.push_back(source);
            source->setDefaultVolume(sound.m_Volume);
            source->setDefaultMinDistance(sound.m_MinDistance);
            sound.m_SourceReference = m_Source.size()-1;
            return true;
        }
        else
            return false;
    }

    bool Klang::UpdateAudioSource(AudioSource3D& sound)
    {
        auto & source = m_Source[sound.m_SourceReference];
        if(source)
        {
            source->setDefaultVolume(sound.m_Volume);
            source->setDefaultMinDistance(sound.m_MinDistance);
            return true;
        }
        else
            return false;
    }

    void Klang::Update()
    {
        m_Engine->update();
    }

    bool Klang::PlayAudioSource(AudioSource3D& sound, TransformComponent &transform)
    {
        auto & source = m_Source[sound.m_SourceReference];
        if(source)
        {
            if(!sound.m_Playing)
            {
                irrklang::ISound * play = m_Engine->play3D(source, Math::ConvertVec3ToVec3df(transform.Position), sound.m_Loop, false, true);
                if(play)
                {
                    
                    m_Playing.push_back(play);
                    sound.m_PlayReference = m_Playing.size()-1;
                    sound.m_Playing = true;
                    return true;
                }   
            }
        }
        
        return false;
    }

    void Klang::UpdateSound(AudioSource3D& sound, TransformComponent &transform)
    {
        if(m_Playing.size() > 0)
        {
            auto& play = m_Playing[sound.m_PlayReference];
            if(play)
            {
                if(play->isFinished())
                {
                    AudioPlaying::iterator itr;

                    itr = remove(m_Playing.begin(), m_Playing.end(), play);
                    m_Playing.erase(itr);
                    sound.m_Playing = false;
                    sound.m_PlayReference = NULL;
                }
                else
                {
                    play->setPosition(Math::ConvertVec3ToVec3df(transform.Position));
                }
            }
        }
    }
}
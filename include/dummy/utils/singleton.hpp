#pragma once

template <typename T> class Singleton
{
public:
    static T& instance() { return m_instance; }

private:
    static T m_instance;
};

template <class T> T Singleton<T>::m_instance = T();

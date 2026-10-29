
#ifndef SORTIEAUDIO_HPP
#define SORTIEAUDIO_HPP

#include <iostream>
#include <string>

using namespace std;

class SortieAudio {
public:
    virtual void ouvrir() = 0;
    virtual void jouer(const string& son) = 0;
    virtual void fermer() = 0;

    virtual ~SortieAudio() {}
};

class HautParleur : public SortieAudio {
public:
    void ouvrir() override;
    void jouer(const string& son) override;
    void fermer() override;
};

class CasqueBT : public SortieAudio {
public:
    void ouvrir() override;
    void jouer(const string& son) override;
    void fermer() override;
};

class SortieHDMI : public SortieAudio {
public:
    void ouvrir() override;
    void jouer(const string& son) override;
    void fermer() override;
};

#endif


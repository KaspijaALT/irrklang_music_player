#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <stdlib.h>
#include <irrKlang.h>

using namespace std;
using namespace irrklang;

int main()
{
    ISoundEngine* engine = createIrrKlangDevice();
    if (!engine)
    {
        cout << "kautkas pa kreisi aizgaja" << endl;
        return 0;
    }

    vector<string> songs = { "media/a.wav", "media/b.wav", "media/Outkast-Jazzy-Belle-_Official-HD-Video_.wav" };
    vector<ISoundSource*> sources;

    for (auto& song : songs)
    {
        sources.push_back(engine->addSoundSourceFromFile(song.c_str()));
    }

    vector<ISound*> playingSounds;
    int currentSongIndex = 0;
    bool playing = false;

    while (true)
    {
        system("cls"); // Clear the console screen
        cout << "Press 1 to play " << songs[0] << endl;
        cout << "Press 2 to play " << songs[1] << endl;
        cout << "Press 3 to play " << songs[2] << endl;
        cout << "P to pause; R to resume; S to stop; Q to quit; N for next" << endl;

        char choice = _getch();

        switch (choice)
        {
        case '1':
            currentSongIndex = 0;
            break;
        case '2':
            currentSongIndex = 1;
            break;
        case '3':
            currentSongIndex = 2;
            break;
        case 'p':
        case 'P':
            if (playing)
            {
                playing = false;
                for (auto& sound : playingSounds)
                {
                    sound->setIsPaused(true);
                }
            }
            break;
        case 'r':
        case 'R':
            if (!playing)
            {
                playing = true;
                for (auto& sound : playingSounds)
                {
                    sound->setIsPaused(false);
                }
            }
            break;
        case 's':
        case 'S':
            playing = false;
            for (auto& sound : playingSounds)
            {
                sound->stop();
            }
            playingSounds.clear();
            break;
        case 'q':
        case 'Q':
            playing = false;
            for (auto& sound : playingSounds)
            {
                sound->stop();
            }
            playingSounds.clear();
            engine->drop();
            return 0;
        case 'n':
        case 'N':
            playing = false;
            for (auto& sound : playingSounds)
            {
                sound->stop();
            }
            playingSounds.clear();

            currentSongIndex = (currentSongIndex + 1) % songs.size();

            ISound* sound = engine->play2D(sources[currentSongIndex], true, false, true);
            if (sound)
            {
                playing = true;
                playingSounds.push_back(sound);
            }
            else
            {
                cout << "Could not play sound " << songs[currentSongIndex] << endl;
            }

            break;

        }

        if (choice >= '1' && choice <= '3')
        {
            ISound* sound = engine->play2D(sources[currentSongIndex], true, false, true);
            if (sound)
            {
                playing = true;
                playingSounds.push_back(sound);
            }
            else
            {
                cout << "Could not play sound " << songs[currentSongIndex] << endl;
            }
        }
    }
}

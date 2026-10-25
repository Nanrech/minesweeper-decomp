#include "winmine.h"

char stopAllSounds(void) {
  BOOL BVar1;

  // Nan:
  // PlaySoundW plays .wav sound from a resource. Deprecated nowadays
  // pszSound: LPCWSTR = string, sound to play. if NULL all sounds are stopped
  // hmod:     HMODULE = handle to exe that contains the resource
  // fdwSound: DWORD   = flags. SND_PURGE stops _non_ .wav sounds
  //
  // returns TRUE on success and FALSE on fail
  BVar1 = PlaySoundW((LPCWSTR)NULL, (HMODULE)NULL, SND_PURGE);
  return (BVar1 != 0) + '\x02';
}

void stopAllSoundsButWeird(void) {
  if (g_state_sound == 3) {
    PlaySoundW((LPCWSTR)NULL, (HMODULE)NULL, SND_PURGE);
  }
  return;
}

void playSound(int sound_to_play) {
  LPCWSTR pszSound;

  if (g_state_sound == 3) {
    if (sound_to_play == 1) {
      // DAT_000001b0 --> 0x1b0
      pszSound = MAKEINTRESOURCEW(0x1b0);
    } else if (sound_to_play == 2) {
      // DAT_000001b1 --> 0x1b1
      pszSound = MAKEINTRESOURCEW(0x1b1);
    } else {
      if (sound_to_play != 3) {
        return;
      }
      // DAT_000001b2 --> 0x1b2
      pszSound = MAKEINTRESOURCEW(0x1b2);
    }
    PlaySoundW(pszSound, hModule, SND_RESOURCE_OR_SND_ASYNC);
  }
  return;
}

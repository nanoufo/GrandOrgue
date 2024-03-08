/*
 * Copyright 2006 Milan Digital Audio LLC
 * Copyright 2009-2024 GrandOrgue contributors (see AUTHORS)
 * License GPL-2.0 or later
 * (https://www.gnu.org/licenses/old-licenses/gpl-2.0.html).
 */

#include "GOSoundStateHandler.h"

void GOSoundStateHandler::PreparePlaybackExt(GOSoundEngine *pSoundEngine) {
  SetSoundEngine(pSoundEngine);
  PreparePlayback();
}

void GOSoundStateHandler::AbortPlaybackExt() {
  AbortPlayback();
  SetSoundEngine(nullptr);
}

make -j$(nproc) && mgba-qt pokefirered.gba && ./flips-linux -c build/clean10.gba pokefirered.gba build/cfr.bps && zip build/release.zip build/cfr.bps changelog/*

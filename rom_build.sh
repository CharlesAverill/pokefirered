make -j$(nproc)
zip build/pokefirered.zip pokefirered.gba changelog/*
mgba-qt pokefirered.gba

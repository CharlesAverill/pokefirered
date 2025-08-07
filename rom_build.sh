echo "===MAKE===" &&
make -j$(nproc) &&
echo "===PATCH===" &&
./flips-linux -c build/clean11.gba pokefirered.gba build/cfr.bps  &&
echo "===ZIP===" &&
zip build/release.zip build/cfr.bps changelog/*

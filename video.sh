# ./make.sh
cd output
ffmpeg -framerate 10 -pattern_type glob -i "MODEL_*.ppm" MODEL_SPIN.mp4
cd ..
docker exec dd bash -c "mkdir build"
docker exec dd bash -c "cd build && cmake -D CMAKE_BUILD_TYPE=$BUILD_TYPE -D BUILD_DEBIAN=ON .."
docker exec dd bash -c "cd build && make -j$(nproc)"

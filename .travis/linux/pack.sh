docker exec dd bash -c "cd build; cpack"
docker exec dd bash -c "cd build; mv *.deb  BornAgain-dev-xenial.deb"
docker exec dd bash -c 'cp $(find ./ -iname "BornAgain*.deb" | head -1) ./'

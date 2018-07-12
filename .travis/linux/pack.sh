docker exec dd bash -c "cd build; cpack"
docker exec dd bash -c "cd build; mv *.deb  bornagain-dev-xenial.deb"
docker exec dd bash -c "cp *.deb  ../"

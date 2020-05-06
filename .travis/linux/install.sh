docker build -t bornagain/focal -f `dirname $0`/Dockerfile .
docker run -d --name dd -it bornagain/focal
docker ps -a

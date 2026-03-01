all: up

IMAGE_NAME=test
CONTAINER_NAME=cont

up:
	docker build -t $(IMAGE_NAME) .

run:
	docker run -it --name $(CONTAINER_NAME) $(IMAGE_NAME)

start: 
	docker start -ai $(CONTAINER_NAME)

stop: 
	docker stop $(CONTAINER_NAME)

status: 
	docker ps -a
	docker images
clean:
	docker rm -f  $(CONTAINER_NAME)
	docker rmi $(IMAGE_NAME)
re: clean up
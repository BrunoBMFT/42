all: up

data:
	@if [ ! -d "/home/brfernan/data/mariadb" ] && [ ! -d "/home/brfernan/data/wordpress;" ]; then \
    	mkdir -p /home/brfernan/data/mariadb && mkdir -p /home/brfernan/data/wordpress; fi

up: data
	@docker-compose -f ./srcs/docker-compose.yml up -d

down: 
	@docker-compose -f ./srcs/docker-compose.yml down

stop: 
	@docker-compose -f ./srcs/docker-compose.yml stop

start: 
	@docker-compose -f ./srcs/docker-compose.yml start

status: 
	@docker ps
clean:
	@docker-compose -f ./srcs/docker-compose.yml down --volumes --remove-orphans
	@docker system prune -af
	@docker volume prune -f
re: clean up

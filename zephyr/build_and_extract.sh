#!/bin/sh

docker-compose build
mkdir -p artefacts
for a in $(grep container_name docker-compose.yml | awk '{print $2}')
do
	docker-compose up --no-start $a
	docker cp $a:/zephyr.elf artefacts/$a.elf
done
docker-compose down

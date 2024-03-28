FROM ubuntu:noble-20240225

WORKDIR /app

RUN apt-get -y update && \
    apt-get -y install gcc make xorg libxext-dev zlib1g-dev libbsd-dev

COPY . .

RUN make -C minilibx/minilibx-linux

RUN make

CMD ["./so_long"]

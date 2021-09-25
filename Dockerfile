FROM alpine

RUN	apk -U upgrade && apk add \
	gcc \
	make \
	musl-dev \
	valgrind \
	readline-dev \
	readline-static

WORKDIR home/

COPY project .

RUN chmod +x install.sh

CMD ["./install.sh"]

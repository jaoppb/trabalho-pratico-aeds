FROM ubuntu

ENV TZ="America/Sao_Paulo"
RUN apt-get update -y && \
	apt-get install -y build-essential cmake catch2
RUN mkdir /app
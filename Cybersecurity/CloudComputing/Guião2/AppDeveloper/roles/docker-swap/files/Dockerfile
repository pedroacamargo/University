FROM ubuntu:24.04

# Set the timezone and noninteractive mode
ARG TZ=US DEBIAN_FRONTEND=noninteractive

# Define default values for the Enviroment Variables
ENV SEED=false

RUN apt-get update && \
    apt-get install -y software-properties-common

# Install app packages
RUN add-apt-repository ppa:ondrej/php && apt-get update && apt-get install -y \
   php7.4 \
   php7.4-fpm \
   php7.4-zip \
   php7.4-mbstring \
   php7.4-tokenizer \
   php7.4-mysql \
   php7.4-gd \
   php7.4-xml \
   php7.4-bcmath \
   php7.4-intl \
   php7.4-curl \
   nodejs \
   npm \
   curl

# Install Composer v1
RUN curl -sS https://getcomposer.org/installer | php -- --1 && \
    mv composer.phar /usr/bin/composer


# Clone Swap repository
RUN git clone https://github.com/Hackathonners/swap.git
WORKDIR /swap

# Create Swap configuration file
RUN cp .env.example .env

# Install Swap composer
RUN composer install

# Install Swap npm
RUN npm install

# Generate key Swap
RUN php artisan key:generate

# Copy start script
COPY ./script.sh .

# Add execution permission to start script
RUN chmod +x script.sh

# Expose port 8000
EXPOSE 8000

# Start Swap server
CMD [ "./script.sh" ]
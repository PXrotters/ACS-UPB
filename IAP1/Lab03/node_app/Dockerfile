FROM node:15.11.0-stretch
WORKDIR /usr/src/app
COPY package.json ./
RUN npm install
COPY server.js /usr/src/app/
EXPOSE 8080
CMD [ "node", "/usr/src/app/server.js" ]
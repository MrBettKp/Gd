# Backend Dockerfile
FROM python:3.9-slim

WORKDIR /app
COPY ./WebBackend/requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

COPY ./WebBackend .

CMD ["uvicorn", "main:app", "--host", "0.0.0.0", "--port", "8000"]

# Frontend Dockerfile (separate)
FROM node:16 as build
WORKDIR /app
COPY ./Frontend/package*.json ./
RUN npm install
COPY ./Frontend .
RUN npm run build

FROM nginx:alpine
COPY --from=build /app/build /usr/share/nginx/html
EXPOSE 80
CMD ["nginx", "-g", "daemon off;"]
